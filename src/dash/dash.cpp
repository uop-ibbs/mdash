//  $Id: dash.cpp 131 2017-11-29 08:52:35Z dw $
//
//  Copyright (C) 2014 Centre for Molecular Design, University of Portsmouth.
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program. If not, see <http://www.gnu.org/licenses/>.

#include "dash/dash.h"
#include "dash/dash_exception.h"
#include "dash/external.h"
#include "dash/circular.h"

#include <Eigen/Core>

#include <boost/algorithm/string.hpp>

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <map>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

Dash::Dash(const Trajectory& t, const DashOptions& o) : trj(t), opt(o)
{
    state dummy_state(10, -1);
    dummy_state_set.insert(dummy_state);
    StateData dummy_state_data;
    dummy_state_data.index = 0;
    dummy_state_data.freq = 0;
    dummy_state_data.frame = 0;
    dummy_state_data.rmsd = 0;
    RepexState dummy_repex_state(dummy_state_set.begin(), dummy_state_data);
    dummy_repex_state_set.push_back(&dummy_repex_state);

    combined_trj.timestep = smoothed_combined_trj.timestep = smoothed_trj.timestep = dash_trj.timestep = opt.timestep;
    pca_ = nullptr;
}

Dash::~Dash()
{
    for (size_t i=0; i<torsion_data.size(); ++i) {
        if (torsion_data[i] != nullptr) delete torsion_data[i];
    }

    if (opt.pca) delete pca_;
}

void
Dash::run()
{
    clock_start_input = clock();

    if (opt.circular) {
        for (double d: trj.data) {
            DASH_PRECONDITION(std::abs(d) <= 180);
        }
    }

    Eigen::Map<dMatrix> traj(const_cast<double*>(trj.data.data()), trj.frames, trj.vars);

    for (int i=0; i<trj.vars; i++) {
        torsion_data.push_back(new TorsionData(i+1, traj.col(i), opt));
    }

    clock_start_dash = clock();

    if (opt.repex) {
        calc_combined_trj(traj);
        calc_repex_trj(traj);
        calc_repex_circular_similarity();
        calc_repex_cosine_similarity();
    } else {
        calc_combined_trj(traj);
        calc_smoothed_combined_trj(opt.smooth);
        calc_smoothed_trj(traj);
        calc_dash_trj(traj, opt.rough);
    }

    if (opt.pca) {
        pca_ = new cmdlib::PCA(traj, opt.pca_autoscale);
    }

    clock_end = clock();
}

void
Dash::calc_repex_trj(const Eigen::Map<dMatrix>& traj)
{
    repex_trj.tag = "REPLICA_EXCHANGE";
    repex_trj.seq.resize(trj.frames);
    repex_states.insert(*dummy_state_set.begin());

    const double repex_min_freq = opt.repex_fraction * frames();

    for (state_set_const_iter i=combined_states.begin(); i!=combined_states.end(); ++i) {
        const StateData& sdata = combined_trj.states[i];
        if (sdata.freq > repex_min_freq) {
            repex_states.insert(*i);
        }
    }

    repex_trj.seq.resize(trj.frames);

    // assign the states to the output sequence
    for (size_t n=0; n<combined_trj.seq.size(); n++) {
        state_set_const_iter pos = repex_states.find(*combined_trj.seq[n]);

        if (pos != repex_states.end()) {
            repex_trj.seq[n] = pos;
        } else {
            repex_trj.seq[n] = dummy_state_set.begin();
        }
    }

    repex_trj.index(repex_states);
    repex_trj.calc(traj);

    // copy repex states to new format
    for (state_set_const_iter i=repex_states.begin(); i!=repex_states.end(); ++i) {
        if (*i != *dummy_state_set.begin()) {
            new_repex_states.push_back(new RepexState(i, repex_trj.states[i]));
        }
    }

    std::sort(new_repex_states.begin(), new_repex_states.end(), RepexFreqComparison());

    // copy state seq to new format
    for (size_t n=0; n<repex_trj.seq.size(); n++) {
        if (repex_trj.seq[n] == dummy_state_set.begin()) {
            repex_state_sequence.push_back(*dummy_repex_state_set.begin());
        } else {
            for (repex_state_set_const_iter i=new_repex_states.begin(); i!=new_repex_states.end(); ++i) {
                if ((*i)->state == repex_trj.seq[n]) {
                    repex_state_sequence.push_back(*i);
                }
            }
        }
    }
}

void
Dash::calc_combined_trj(const Eigen::Map<dMatrix>& traj)
{
    state tmpstate(trj.vars);
    combined_trj.tag = "COMBINED";
    combined_trj.seq.resize(trj.frames);

    // collect the combined states
    for (int n = 0; n<trj.frames; n++) {
        for (int t = 0; t<trj.vars; t++) {
            tmpstate[t] = torsion_data[t]->state(n);
        }

        combined_states.insert(tmpstate);
    }

    // assign the states to the sequence
    for (int n = 0; n<trj.frames; n++) {
        for (int t = 0; t<trj.vars; t++) {
            tmpstate[t] = torsion_data[t]->state(n);
        }

        combined_trj.seq[n] = combined_states.find(tmpstate);
    }

    combined_trj.index(combined_states);
    combined_trj.calc(traj);
    combined_trj.reassigned = 0;
}

void
Dash::calc_smoothed_combined_trj(int smooth)
{
    state_set_iter prev;
    state_set_iter curr;
    state_set_iter next;

    smoothed_combined_trj.tag = "SMOOTHED_COMBINED";
    smoothed_combined_trj.seq.resize(trj.frames);
    smoothed_combined_trj.seq[0] = prev = curr = next = combined_trj.seq[0];

    if  (smooth <= 1) {
        for (int i = 1; i<trj.frames; i++) {
            smoothed_combined_trj.seq[i] = combined_trj.seq[i];
        }
    } else {
        int transient = 0;
        int nextlen = 0;
        int state_num = 0;
        int first_state = 0;

        for (int i = 1; i<trj.frames; i++) {
            smoothed_combined_trj.seq[i] = prev;
            curr = combined_trj.seq[i];

            if (state_num == 0 && curr == prev) {
                first_state++;
                if (first_state >= smooth) {
                    state_num++;
                    for (int k = 0; k <= first_state; k++) {
                        smoothed_combined_trj.seq[k] = curr;
                    }
                }
            } else if (transient == 0 && curr == prev) {
                // remain in previous state
                smoothed_combined_trj.seq[i] = curr;
            } else if (transient == 0 && curr != prev) {
                // started a new transient
                transient = 1;
                nextlen = 1;
                next = curr;
            } else if (transient < smooth && curr == prev) {
                // a short transition is over
                // assign current state to transient
                for (int j = (i - transient); j<=i; j++) {
                    smoothed_combined_trj.seq[j] = curr;
                }
                // reset counters
                transient = 0;
                nextlen = 0;
            } else {
                // in mid transient
                transient++;
                if (curr == next) {
                    // remain in a possible next state
                    nextlen++;
                    if (nextlen >= smooth) {
                        state_num++;
                        if (state_num == 1) {
                            // first state, assign this state to whole sequence so far
                            for (int j=0; j<=i; j++) {
                                smoothed_combined_trj.seq[j] = curr;
                            }
                        } else {
                            // transition to next state
                            // assign next state to backlog
                            for (int j = (i - nextlen + 1); j<=i; j++) {
                                smoothed_combined_trj.seq[j] = curr;
                            }
                            // deal with transient
                            // assign first half to previous state
                            // assign second half to next state
                            if (transient > nextlen) {
                                int s1 = i - transient + 1; // index of 1st transition state
                                int s2 = i - nextlen;       // index of previous transition state
                                int gap = s2 - s1 + 1;      // length of transient
                                // length to assign to previous state
                                int gap1 = static_cast<int>(ceil(gap/2.0));
                                // and next state
                                int gap2 = gap - gap1;

                                for (int j = 0; j<gap1; j++) {
                                    smoothed_combined_trj.seq[s1+j] = prev;
                                }

                                for (int j = 0; j<gap2; j++) {
                                    smoothed_combined_trj.seq[s2-j] = curr;
                                }
                            }
                        }

                        // reset counters
                        transient = 0;
                        prev = curr;
                        nextlen = 0;
                    }
                } else { // current != next - a new possible transition
                    next = curr;
                    nextlen = 1;
                }
            }
        }
    }

    smoothed_combined_trj.index(combined_states);
    smoothed_combined_trj.reassigned = calc_reassigned(combined_trj.seq, smoothed_combined_trj.seq);
}

void
Dash::calc_smoothed_trj(const Eigen::Map<dMatrix>& traj)
{
    // collect the states used in the input sequence
    for (size_t n=0; n<smoothed_combined_trj.seq.size(); n++) {
        dash_states.insert(*smoothed_combined_trj.seq[n]);
    }

    smoothed_trj.seq.resize(trj.frames);

    // assign the states to the output sequence
    for (size_t n=0; n<smoothed_combined_trj.seq.size(); n++) {
        smoothed_trj.seq[n] = dash_states.find(*smoothed_combined_trj.seq[n]);
    }

    smoothed_trj.tag = "SMOOTHED";
    smoothed_trj.index(dash_states);
    smoothed_trj.calc(traj);
    smoothed_trj.reassigned = smoothed_combined_trj.reassigned;
}

void
Dash::calc_dash_trj(const Eigen::Map<dMatrix>& traj, int rough)
{
    int transient = 0;
    int nextlen = 0;
    int state_num = 0;
    int first_state = 0;
    bool final_state;

    state_set_iter prev;
    state_set_iter curr;
    state_set_iter next;

    dash_trj.tag = "DASH";
    dash_trj.seq.resize(trj.frames);
    dash_trj.seq[0] = prev = curr = next = combined_trj.seq[0];

    for (int i = 1; i<trj.frames; i++) {
        dash_trj.seq[i] = prev;
        curr = combined_trj.seq[i];

        if (state_num == 0 && curr == prev) {
            first_state++;
            if (first_state >= rough) {
                final_state = false;

                for (state_set_iter k = dash_states.begin(); k != dash_states.end(); ++k) {
                    if (*curr == *k) {
                        final_state = true;
                        state_num++;
                        break;
                    }
                }

                if (final_state) {
                    for (int k = 0; k <= first_state; k++) {
                        dash_trj.seq[k] = curr;
                    }
                }
            }
        } else if (transient == 0 && curr == prev) {
            // remain in previous state
            dash_trj.seq[i] = curr;
        } else if (transient == 0 && curr != prev) {
            // started a new transient
            transient = 1;
            nextlen = 1;
            next = curr;
        } else if (transient < rough && curr == prev) {
            // a short transition is over
            // assign current state to transient
            for (int j = (i - transient); j<=i; j++) {
                dash_trj.seq[j] = curr;
            }
            // reset counters
            transient = 0;
            nextlen = 0;
        } else {
            // in mid transient
            transient++;
            if (curr == next) {
                // remain in a possible next state
                nextlen++;
                if (nextlen >= rough) {
                    // check next state is a final state
                    final_state = false;

                    for (state_set_iter k = dash_states.begin(); k != dash_states.end(); ++k) {
                        if (*curr == *k) {
                            final_state = true;
                            state_num++;
                            break;
                        }
                    }

                    if (final_state) {
                        if (state_num == 1) {
                            // first state, assign this state to whole sequence so far
                            for (int j=0; j<=i; j++) {
                                dash_trj.seq[j] = curr;
                            }
                        } else {
                            // transition to next state
                            // assign next state to backlog
                            for (int j = (i - nextlen + 1); j<=i; j++) {
                                dash_trj.seq[j] = curr;
                            }
                            // deal with transient - assign first half to last
                            // state, second half to next state
                            if (transient > nextlen) {
                                int s1 = i - transient + 1; // index of 1st transition state
                                int s2 = i - nextlen;       // index of previous transition state
                                int gap = s2 - s1 + 1;      // length of transient
                                // length to assign to previous state
                                int gap1 = static_cast<int>(ceil(gap/2.0));
                                // and next state
                                int gap2 = gap - gap1;

                                for (int j = 0; j<gap1; j++) {
                                    dash_trj.seq[s1+j] = prev;
                                }

                                for (int j = 0; j<gap2; j++) {
                                    dash_trj.seq[s2-j] = curr;
                                }
                            }
                        }
                        // reset counters
                        transient = 0;
                        prev = curr;
                        nextlen = 0;
                    }
                }
            } else { // current != next - a new possible transition
                next = curr;
                nextlen = 1;
            }
        }
    }

    // convert combined states to final states
    for (size_t n=0; n<dash_trj.seq.size(); n++) {
        dash_trj.seq[n] = dash_states.find(*dash_trj.seq[n]);
    }

    dash_trj.index(dash_states);
    dash_trj.calc(traj);
    dash_trj.reassigned = calc_reassigned(combined_trj.seq, dash_trj.seq);
}

int
Dash::calc_reassigned(const state_sequence& input_seq, state_sequence& output_seq)
{
    DASH_PRECONDITION(input_seq.size() == output_seq.size());

    int reassigned = 0;

    for (size_t i = 0; i < input_seq.size(); i++) {
        if (*input_seq[i] != *output_seq[i]) {
            ++reassigned;
        }
    }

    return reassigned;
}

void
Dash::write(std::ostream& os) const
{
    trj.write(os);
    opt.write(os);
    write_torsion_data(os);

    if (!opt.repex) {
        write_summary(os);
    }

    if (opt.write_combined) {
        combined_trj.write_state_info(os);
        if (!opt.repex) combined_trj.write_trajectory_info(os);
        if (opt.write_sequence) combined_trj.write_state_sequence(os);
    }

    if (opt.write_smoothed) {
        smoothed_trj.write(os);
        if (opt.write_sequence) smoothed_trj.write_state_sequence(os);
    }

    if (opt.write_dash) {
        dash_trj.write(os);
        if (opt.write_sequence) dash_trj.write_state_sequence(os);
    }

    if (opt.repex) {
        write_repex_states(os);
        write_repex_circular_similarity(os);
        write_repex_cosine_similarity(os);
        write_repex_trj(os);
    }

    if (opt.pca) {
        write_pca(os);
    }

    write_times(os);
}

std::string
Dash::summary() const
{
    std::ostringstream os;
    trj.write(os);
    opt.write(os);
    if (!opt.repex) write_summary(os);
    if (opt.pca) write_pca_summary(os);
    return os.str();
}

void
Dash::write_summary(std::ostream& os) const
{
    os << "[SUMMARY]\n"
       << "combined states : " << combined_states.size() << '\n'
       << "final states    : " << dash_states.size() << '\n'
       << "transitions     : " << dash_trj.transitions << '\n'
       << std::fixed << std::setprecision(2)
       << "reassignments   : " << dash_trj.reassigned
       << " (" << (100.0*dash_trj.reassigned)/trj.frames << "%)\n\n";
}

void
Dash::write_torsion_data(std::ostream& os) const
{
    for (int i=0; i<vars(); i++) {
        torsion_data[i]->write(os);
        os << '\n';

        if (opt.write_histogram) {
            torsion_data[i]->write_histogram(os);
            os << '\n';
        }
    }
}

void
Dash::write_times(std::ostream& os) const {
    os << "[CPU_TIME]\n"
       << "Input : " << input_time() << '\n'
       << "Dash  : " << dash_time()  << '\n'
       << "Total : " << total_time() << '\n';
}

std::string
Dash::input_time() const {
    return elapsed_time(clock_start_input, clock_start_dash);
}

std::string
Dash::dash_time() const {
    return elapsed_time(clock_start_dash, clock_end);
}

std::string
Dash::total_time() const {
    return elapsed_time(clock_start_input, clock_end);
}

std::string
Dash::elapsed_time(clock_t start, clock_t stop) const {
    float elapsed = static_cast<float>((stop-start)/CLOCKS_PER_SEC);
    int hours = static_cast<int>(trunc(elapsed/3600));
    int mins = static_cast<int>(trunc((elapsed - hours*3600)/60));
    float secs = elapsed - hours*3600 - mins*60;
    std::ostringstream os;

    if (hours > 0) {
        os << hours << "h " << mins << "m " << std::fixed << std::setprecision(0) << secs << "s";
    } else if (mins > 0) {
        os << mins << "m " << std::fixed << std::setprecision(0) << secs << "s";
    } else {
        os << std::fixed << std::setprecision(1) << secs << "s";
    }

    return os.str();
}

void
write_vector(const std::vector<int>& v, std::ostream& os, char sep) {
    for (size_t i=0; i<v.size(); ++i) {
        os << v[i] << sep;
    }
}

void
write_vector(const std::vector<double>& v, std::ostream& os, int width, int prec) {
    os << std::fixed << std::setprecision(prec);

    for (size_t i=0; i<v.size(); ++i) {
        os << std::setw(width) << v[i];
    }
}

void
Dash::write_repex_states(std::ostream& os) const
{
    os << '[' + repex_trj.tag + "_STATES]\n";

    int s = 1;

    for (std::vector<RepexState*>::const_iterator i=new_repex_states.begin(); i!=new_repex_states.end(); ++i, ++s){
        state_set_const_iter state = (*i)->state;
        os << s << '\t';

        for (size_t j=0; j<state->size()-1; ++j){
            os << (*state)[j] << ' ';
        }

        os << (*state)[state->size()-1] << '\n';
    }

    os << '\n';

    os << '[' + repex_trj.tag + "_STATE_DISTRIBUTION]\n"
       << "State\t"
       << std::setw(8) << "Frames"
       << std::setw(10) << "%Frames"
       << std::setw(12) << "Rep.Frame"
       << std::setw(10) << "RMSD" << '\n';

    s = 1;

    for (std::vector<RepexState*>::const_iterator i=new_repex_states.begin(); i!=new_repex_states.end(); ++i,++s) {
        os << std::fixed << std::setprecision(2)
           << s << '\t'
           << std::setw(8) << (*i)->freq
           << std::setw(10) << (100.0*(*i)->freq)/frames()
           << std::setw(12) << (*i)->frame
           << std::setw(10) << (*i)->rmsd << '\n';
    }

    os << '\n';

    os << '[' + repex_trj.tag + "_STATE_MEAN_ANGLES]\n";
    int j = 1;

    for (std::vector<RepexState*>::const_iterator i=new_repex_states.begin(); i!=new_repex_states.end(); ++i,++j) {
        os << j << '\t';
        write_vector((*i)->mean, os, 8, 2);
        os << '\n';
    }

    os << '\n';
    os << '[' + repex_trj.tag + "_STATE_STANDARD_DEVIATIONS]\n";

    j = 0;

    for (std::vector<RepexState*>::const_iterator i=new_repex_states.begin(); i!=new_repex_states.end(); ++i,++j) {
        os << j+1 << '\t';
        write_vector((*i)->sdev, os, 8, 2);
        os << '\n';
    }

    os << '\n';
}

void
Dash::write_repex_trj(std::ostream& os) const
{
    const std::string tag = "REPLICA_EXCHANGE";
    int count = 1;
    int total = 1;
    int index = 0;

    for (size_t i=0; i<new_repex_states.size(); ++i) {
        if (new_repex_states[i] == repex_state_sequence[0]) {
            index = i+1;
            break;
        }
    }

    os << '[' + tag + "_STATE_TRAJECTORY]\n"
       << "State\t"
       << std::setw(6) << "Frames"
       << std::setw(12) << "Cumulative" << '\n'
       << index << '\t';

    for (size_t n=1; n<repex_state_sequence.size(); n++) {
        RepexState* current = repex_state_sequence[n];
        RepexState* last = repex_state_sequence[n-1];

        if (current == last) {
            ++count;
            ++total;
        } else {
            os << std::setw(6) << count
               << std::setw(12) << total << '\n';

            index = 0;

            for (size_t i=0; i<new_repex_states.size(); ++i) {
                if (new_repex_states[i] == current) {
                    index = i+1;
                    break;
                }
            }

            os << index << '\t';
            count = 1;
            ++total;
        }
    }

    os << std::setw(6) << count
       << std::setw(12) << total << "\n\n";
}

void
Dash::calc_repex_circular_similarity()
{
    repex_trj.circular_sim.resize(new_repex_states.size(), new_repex_states.size());
    int s = 0;

    for (std::vector<RepexState*>::const_iterator i=new_repex_states.begin(); i!=new_repex_states.end(); ++i, ++s) {
        int t = 0;

        for (std::vector<RepexState*>::const_iterator j=new_repex_states.begin(); j!=new_repex_states.end(); ++j, ++t) {
            repex_trj.circular_sim(s,t) = circular::similarity((*i)->mean, (*j)->mean);
        }
    }
 }

void
Dash::write_repex_circular_similarity(std::ostream& os) const
{
    os << "[REPLICA_EXCHANGE_STATE_CIRCULAR_SIMILARITY]\n\t";

    for (size_t s=1; s<=new_repex_states.size(); s++) {
        os << std::setw(6) << s;
    }

    os << '\n';

    for (size_t s=0; s<new_repex_states.size(); s++) {
        os << s+1 << '\t';

        for (size_t t=0; t<new_repex_states.size(); t++) {
            os << std::setw(6) << repex_trj.circular_sim(s,t);
        }

        os << '\n';
    }

    os << '\n';
}

void
Dash::calc_repex_cosine_similarity()
{
    repex_trj.cosine_sim.resize(new_repex_states.size(), new_repex_states.size());
    int s = 0;

    for (std::vector<RepexState*>::const_iterator i=new_repex_states.begin(); i!=new_repex_states.end(); ++i, ++s) {
        int t = 0;

        for (std::vector<RepexState*>::const_iterator j=new_repex_states.begin(); j!=new_repex_states.end(); ++j, ++t) {
            repex_trj.cosine_sim(s,t) = circular::cosine_similarity((*i)->mean, (*j)->mean);
        }
    }
}

void
Dash::write_repex_cosine_similarity(std::ostream& os) const
{
    os << "[REPLICA_EXCHANGE_STATE_COSINE_SIMILARITY]\n\t";

    for (size_t s=1; s<=new_repex_states.size(); s++) {
        os << std::setw(6) << s;
    }

    os << '\n';

    for (size_t s=0; s<new_repex_states.size(); s++) {
        os << s+1 << '\t';

        for (size_t t=0; t<new_repex_states.size(); t++) {
            os << std::setw(6) << repex_trj.cosine_sim(s,t);
        }

        os << '\n';
    }

    os << '\n';
}

void
Dash::write_pca(std::ostream& os) const
{
    write_pca_summary(os);
    write_pca_coefficients(os);
    write_pca_weights(os);
    write_pca_scaling(os);
}

void
Dash::write_pca_summary(std::ostream& os) const
{
    os << std::fixed
       << std::setprecision(4)
       << "[PCA_SUMMARY]\n"
       << std::setw(22) << "PC1";

    for (int i=2; i<=pca_->p(); ++i) {
        os << std::setw((i<10)?11:10) << "PC" << i;
    }

    os << "\nVariance  ";

    for (int i=0; i<pca_->p(); ++i) {
        os << std::setw(12) << pca_->var(i);
    }

    os << "\nExplained ";

    for (int i=0; i<pca_->p(); ++i) {
        os << std::setw(12) << pca_->explained(i);
    }

    os << "\nCumulative";

    for (int i=0; i<pca_->p(); ++i) {
        os << std::setw(12) << pca_->cumulative(i);
    }

    os << "\n\n";
}

void
Dash::write_pca_coefficients(std::ostream& os) const
{
    os << std::fixed
       << std::setprecision(4)
       << "[PCA_COEFFICIENTS]\n";

    for (int i=1; i<=pca_->p(); ++i) {
        os << std::setw((i<10)?11:10) << "PC" << i;
    }

    os << '\n';

    for (int i=0; i<pca_->p(); ++i) {
        for (int j=0; j<pca_->p(); ++j) {
            os << std::setw(12) << pca_->coefficients()(i,j);
        }

        os << '\n';
    }

    os << '\n';
}

// convenience function for Elke
// writes squares of PCA coefficients
void
Dash::write_pca_weights(std::ostream& os) const
{
    os << std::fixed
       << std::setprecision(4)
       << "[PCA_WEIGHTS]\n";

    for (int i=1; i<=pca_->p(); ++i) {
        os << std::setw((i<10)?11:10) << "PC" << i;
    }

    os << '\n';

    for (int i=0; i<pca_->p(); ++i) {
        for (int j=0; j<pca_->p(); ++j) {
            double v = pca_->coefficients()(i,j);
            os << std::setw(12) << v*v;
        }

        os << '\n';
    }

    os << '\n';
}

void
Dash::write_pca_scaling(std::ostream& os) const
{
    os << "[PCA_CENTROID]\n";

    for (int i=1; i<=pca_->p(); ++i) {
        os << std::setw((i<10)?11:10) << "ANGLE" << i;
    }

    os << '\n'
       << std::fixed
       << std::setprecision(4);

    for (int i=0; i<pca_->p(); ++i) {
        os << std::setw(12) << pca_->centre()(i);
    }

    os  << "\n\n";
}

void
Dash::write_labelled_data_file(std::string file) const
{
    std::ifstream ifs(trj.input_file.c_str());

    if (!ifs) {
        DASH_RUNTIME_ERROR("Failed to open trajectory file " + trj.input_file);
    }

    std::ofstream ofs(file.c_str());

    if (!ofs) {
        DASH_RUNTIME_ERROR("Failed to open output file " + file);
    }

    std::string line;
    int i = 0;

    while (getline(ifs, line)) {
        // remove trailing whitespace (including DOS line endings)
        boost::trim_right_if(line, boost::is_any_of(" \t\r"));

        state_map::const_iterator pos = dash_trj.states.find(dash_trj.seq[i++]);

        if (pos == dash_trj.states.end()) {
            DASH_RUNTIME_ERROR("find state failed");
        }

        ofs << line << " " << pos->second.index << '\n';
    }
}

#ifndef NOAMBER
bool
Dash::write_snapshots(std::string& msg) const
{
    std::vector<double> frames;

    for (auto state : dash_trj.states) {
        frames.push_back(state.second.frame);
    }

    int statenum = 0;

    for (auto f : frames) {
        std::ostringstream oss;

        oss << "parm " << trj.top_file << '\n'
            << "trajin " << trj.trj_file << " " << f << " " << f << '\n'
            << "trajout state_" << ++statenum << ".pdb pdb\n"
            << "noprogress\ngo\nquit\ny\n";

        std::string in = oss.str();
        std::string out;
        std::string err;

        bool rtn = external::cpptraj(in, out, err, msg);

        if (opt.keep_cpptraj) {
            std::string infile = "state_" + std::to_string(statenum) + "_cpptraj.in";

            if (!external::save(in, infile)) {
                std::string warn = "Warning: failed to save " + infile + '\n';
                msg += warn;
                rtn = false;
            }

            std::string outfile = "state_" + std::to_string(statenum) + "_cpptraj.out";

            if (!external::save(out, outfile)) {
                std::string warn = "Warning: failed to save " + outfile + '\n';
                msg += warn;
                rtn = false;
            }

            std::string errfile = "state_" + std::to_string(statenum) + "_cpptraj.err";

            if (!external::save(err, errfile)) {
                std::string warn = "Warning: failed to save " + errfile + '\n';
                msg += warn;
                rtn = false;
            }
        }

        if (!(rtn && msg.empty())) return false;
    }

    return true;
}
#endif // NOAMBER
