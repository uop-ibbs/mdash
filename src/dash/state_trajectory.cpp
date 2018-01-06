//  $Id: state_trajectory.cpp 102 2017-03-14 14:27:19Z dw $
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

#include "dash/state_trajectory.h"
#include "dash/dash_exception.h"
#include "dash/circular.h"

#include <iostream>
#include <iomanip>
#include <limits>
#include <map>
#include <vector>

#include <boost/math/constants/constants.hpp>

using boost::math::double_constants::pi;

void
StateTrajectory::index(const state_set& torsion_states)
{
    for (state_set_const_iter i=torsion_states.begin(); i!=torsion_states.end(); ++i) {
        states[i].index = distance(torsion_states.begin(), i) + 1;
    }
}

void
StateTrajectory::calc(const Eigen::Map<dMatrix>& angle_map)
{
    calc_transitions();
    calc_freq();
    calc_bouts();
    calc_stats(angle_map);
    calc_frames(angle_map);
    calc_circular_similarity();
    calc_cosine_similarity();
}

void
StateTrajectory::calc_transitions() {
    transitions = 0;

    for (size_t i=1; i<seq.size(); ++i) {
        if (seq[i] != seq[i-1]) ++transitions;
    }
}

void
StateTrajectory::calc_freq()
{
    for (size_t i=0; i<seq.size(); ++i) {
        states[seq[i]].freq++;
    }
}

void
StateTrajectory::calc_bouts()
{
    state current_state = *seq[0];
    int boutlen = 1;

    for (size_t i=1; i<seq.size(); ++i) {
        if (*seq[i] == current_state) {
            ++boutlen;
        } else {
            states[seq[i-1]].bouts.push_back(boutlen);
            current_state = *seq[i];
            boutlen = 1;
        }
    }

    states[seq[seq.size()-1]].bouts.push_back(boutlen);
}

void
StateTrajectory::calc_stats(const Eigen::Map<dMatrix>& angle_map)
{
    const double deg2rad = pi/180.0;

    int T = angle_map.cols();
    int N = angle_map.rows();

    std::map<state, std::vector<double> > cos_sum;
    std::map<state, std::vector<double> > sin_sum;

    for (state_map::const_iterator s=states.begin(); s!=states.end(); ++s) {
        cos_sum[*s->first] = std::vector<double>(T);
        sin_sum[*s->first] = std::vector<double>(T);
    }

    for (int n=0; n<N; n++) {
        for (int t=0; t<T; t++) {
            cos_sum[*seq[n]][t] += cos(angle_map(n,t)*deg2rad);
            sin_sum[*seq[n]][t] += sin(angle_map(n,t)*deg2rad);
        }
    }

    for (state_map::const_iterator i=states.begin(); i!=states.end(); ++i) {
        states[i->first].mean = std::vector<double> (T);
        states[i->first].sdev = std::vector<double> (T);

        for (int t=0; t<T; t++) {
            states[i->first].mean[t] = atan2(sin_sum[*i->first][t], cos_sum[*i->first][t])/deg2rad;
            double R = sqrt((sin_sum[*i->first][t]*sin_sum[*i->first][t])+(cos_sum[*i->first][t]*cos_sum[*i->first][t]))/states[i->first].freq;
            states[i->first].sdev[t] = pow(-2.0*log(R), 0.5)/deg2rad;
        }
    }
}

void
StateTrajectory::calc_frames(const Eigen::Map<dMatrix>& angle_map)
{
    const int nangles = angle_map.cols();
    const int nframes = angle_map.rows();

    for (state_map::iterator i=states.begin(); i!=states.end(); ++i) {
        double sumsqmin = std::numeric_limits<double>::max();
        int minframe = 0;
        StateData& state_data = i->second;

        for (int n=0; n<nframes; n++) {
            double sumsq = 0;

            for (int t=0; t<nangles; t++) {
                double diff = std::abs(angle_map(n,t) - state_data.mean[t]);

                if (diff > 180.0) {
                    diff = 360.0 - diff;
                }

                sumsq += diff*diff;
            }

            if (sumsq < sumsqmin) {
                sumsqmin = sumsq;
                minframe = n;
            }
        }

        state_data.frame = minframe+1;
        state_data.rmsd = sqrt(sumsqmin/nangles);
    }
}

void
StateTrajectory::calc_circular_similarity()
{
    circular_sim.resize(states.size(), states.size());
    int s = 0;

    for (state_map::const_iterator i=states.begin(); i!=states.end(); ++i, ++s) {
        int t = 0;

        for (state_map::const_iterator j=states.begin(); j!=states.end(); ++j, ++t) {
            circular_sim(s,t) = circular::similarity(i->second.mean, j->second.mean);
        }
    }
}

void
StateTrajectory::calc_cosine_similarity()
{
    cosine_sim.resize(states.size(), states.size());
    int s = 0;

    for (state_map::const_iterator i=states.begin(); i!=states.end(); ++i, ++s) {
        int t = 0;

        for (state_map::const_iterator j=states.begin(); j!=states.end(); ++j, ++t) {
            cosine_sim(s,t) = circular::cosine_similarity(i->second.mean, j->second.mean);
        }
    }
}

void
StateTrajectory::write(std::ostream& os) const
{
    write_state_info(os);
    write_trajectory_info(os);
}

void
StateTrajectory::write_state_info(std::ostream& os) const
{
    write_states(os);
    write_state_dist(os);
    write_stats(os);
}

void
StateTrajectory::write_trajectory_info(std::ostream& os) const
{
    write_trajectory(os);
    write_transitions(os);
    write_reassigned(os);
    write_bouts(os);
    if (timestep > 1) write_bout_times(os);
    write_circular_similarity(os);
    write_cosine_similarity(os);
}

void
StateTrajectory::write_states(std::ostream& os) const
{
    os << '[' + tag + "_STATES]\n";

    int s = 1;

    for (state_map::const_iterator i=states.begin(); i!=states.end(); ++i, ++s){
        state_set_const_iter state = i->first;
        os << s << '\t';

        for (size_t j=0; j<state->size()-1; ++j) {
            os << (*state)[j] << ' ';
        }

        os << (*state)[state->size()-1] << '\n';
    }

    os << '\n';
}

void
StateTrajectory::write_state_dist(std::ostream& os) const
{
    os << '[' + tag + "_STATE_DISTRIBUTION]\n"
       << "State\t"
       << std::setw(8) << "Frames"
       << std::setw(10) << "%Frames";

    if (timestep > 1) {
        os << std::setw(12) << "Time(ps)";
    }

    os << std::setw(12) << "Rep.Frame"
       << std::setw(10) << "RMSD" << '\n';

    int s = 1;

    for (state_map::const_iterator i=states.begin(); i!=states.end(); ++i,++s) {
        const StateData& sdata = i->second;

        os << std::fixed << std::setprecision(2)
           << s << '\t'
           << std::setw(8) << sdata.freq
           << std::setw(10) << (100.0*sdata.freq)/seq.size();

        if (timestep > 1) {
            os << std::setw(12) << sdata.freq*timestep;
        }

        os << std::setw(12) << sdata.frame
           << std::setw(10) << sdata.rmsd << '\n';
    }

    os << '\n';
}

void
StateTrajectory::write_state_sequence(std::ostream& os) const
{
    os << '[' + tag + "_STATE_SEQUENCE]\n";

    for (size_t n=0; n<seq.size(); n++) {
        state_map::const_iterator pos = states.find(seq[n]);

        if (pos == states.end()) {
            DASH_RUNTIME_ERROR("find state failed");
        }

        os << n+1 << '\t' << pos->second.index << '\n';
    }

    os << '\n';
}

void
StateTrajectory::write_trajectory(std::ostream& os) const
{
    state_set_const_iter current;
    state_set_const_iter last;
    int count = 1;
    int total = 1;
    state_map::const_iterator pos = states.find(seq[0]);

    if (pos == states.end()) {
        DASH_RUNTIME_ERROR("find state failed");
    }

    os << '[' + tag + "_STATE_TRAJECTORY]\n"
       << "State\t"
       << std::setw(6) << "Frames"
       << std::setw(12) << "Cumulative";

    if (timestep > 1) {
        os << std::setw(12) << "Time(ps)"
           << std::setw(12) << "Cumulative";
    }

    os << '\n'<< pos->second.index << '\t';

    for (size_t n=1; n<seq.size(); n++) {
        current = seq[n];
        last = seq[n-1];

        if (current == last) {
            ++count;
            ++total;
        } else {
            os << std::setw(6) << count
               << std::setw(12) << total;

            if (timestep > 1) {
                os << std::setw(12) << count*timestep
                   << std::setw(12) << total*timestep;
            }

            os << '\n';

            pos = states.find(current);

            if (pos == states.end()) {
                DASH_RUNTIME_ERROR("find state failed");
            }

            os << pos->second.index << '\t';
            count = 1;
            ++total;
        }
    }

    os << std::setw(6) << count
       << std::setw(12) << total;

    if (timestep > 1) {
        os << std::setw(12) << count*timestep
           << std::setw(12) << total*timestep;
    }

    os << "\n\n";
}

void
StateTrajectory::write_transitions(std::ostream& os) const
{
    os << '[' + tag + "_STATE_TRANSITIONS]\n"
       << transitions << "\n\n";
}

void
StateTrajectory::write_reassigned(std::ostream& os) const
{
    if (tag == "COMBINED") return;

    os << '[' + tag + "_STATE_REASSIGNMENTS]\n"
       << reassigned << " (" << (100.0*reassigned)/seq.size() << "%)\n\n";
}

void
StateTrajectory::write_bouts(std::ostream& os) const
{
    os << '[' + tag + "_STATE_BOUTS_(FRAMES)]\n";
    int j=1;

    for (state_map::const_iterator i=states.begin(); i!=states.end(); ++i,++j) {
        os << j << '\t';
        write_vector(i->second.bouts, os, ' ');
        os << '\n';
    }

    os << '\n';
}

void
StateTrajectory::write_bout_times(std::ostream& os) const
{
    os << '[' + tag + "_STATE_BOUTS_(PS)]\n";
    int j=1;

    for (state_map::const_iterator i=states.begin(); i!=states.end(); ++i,++j) {
        std::vector<int> times(i->second.bouts);
        std::transform(times.begin(), times.end(), times.begin(), std::bind1st(std::multiplies<int>(), timestep));
        os << j << '\t';
        write_vector(times, os, ' ');
        os << '\n';
    }

    os << '\n';
}

void
StateTrajectory::write_stats(std::ostream& os) const
{
    os << '[' + tag + "_STATE_MEANS]\n";
    int j = 1;

    for (state_map::const_iterator i=states.begin(); i!=states.end(); ++i,++j) {
        os << j << '\t';
        write_vector(i->second.mean, os, 8, 2);
        os << '\n';
    }

    os << '\n';
    os << '[' + tag + "_STATE_STANDARD_DEVIATIONS]\n";

    j = 0;

    for (state_map::const_iterator i=states.begin(); i!=states.end(); ++i,++j) {
        os << j+1 << '\t';
        write_vector(i->second.sdev, os, 8, 2);
        os << '\n';
    }

    os << '\n';
}

void
StateTrajectory::write_circular_similarity(std::ostream& os) const
{
    os << '[' + tag + "_STATE_CIRCULAR_SIMILARITY]\n\t";

    for (size_t s=1; s<=states.size(); s++) {
        os << std::setw(6) << s;
    }

    os << '\n';

    for (size_t s=0; s<states.size(); s++) {
        os << s+1 << '\t';

        for (size_t t=0; t<states.size(); t++) {
            os << std::setw(6) << circular_sim(s,t);
        }

        os << '\n';
    }

    os << '\n';
}

void
StateTrajectory::write_cosine_similarity(std::ostream& os) const
{
    os << '[' + tag + "_STATE_COSINE_SIMILARITY]\n\t";

    for (size_t s=1; s<=states.size(); s++) {
        os << std::setw(6) << s;
    }

    os << '\n';

    for (size_t s=0; s<states.size(); s++) {
        os << s+1 << '\t';

        for (size_t t=0; t<states.size(); t++) {
            os << std::setw(6) << cosine_sim(s,t);
        }

        os << '\n';
    }

    os << '\n';
}

void
StateTrajectory::write_vector(const std::vector<int>& v, std::ostream& os, char sep) const
{
    for (size_t i=0; i<v.size(); ++i) {
        os << v[i] << sep;
    }
}

void
StateTrajectory::write_vector(const std::vector<double>& v, std::ostream& os, int width, int prec) const
{
    os << std::fixed << std::setprecision(prec);

    for (size_t i=0; i<v.size(); ++i) {
        os << std::setw(width) << v[i];
    }
}
