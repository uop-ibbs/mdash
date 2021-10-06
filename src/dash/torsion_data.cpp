//  $Id: torsion_data.cpp 129 2017-11-28 14:41:16Z dw $
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

#include "dash/torsion_data.h"
#include "dash/circular.h"
#include "dash/dash_exception.h"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <numeric>
#include <vector>

#include <boost/math/special_functions/sign.hpp>

using boost::math::sign;

TorsionData::TorsionData(int idx, const dVector& data, const DashOptions& opt) {
    index_ = idx;
    frames_ = data.size();
    binsize_ = opt.binsize;
    circular_ = opt.circular;
    repex_ = opt.repex;
    debug_ = opt.debug;
    rev85_ = opt.rev85;
    reassigned_ = 0;

    if (circular_) {
        data_min_ = -180;
        data_max_ = 180;
        bins_ = static_cast<int>(trunc(360.0/binsize_));
    } else {
        data_min_ = floor(data.minCoeff());
        data_max_ = ceil(data.maxCoeff());
        bins_ = static_cast<int>(trunc((data_max_ - data_min_)/binsize_));
    }

    if (!repex_) {
        if (circular_) {
            moving_avg_ = circular::moving_average(data, opt.window);
            calc_freq_dist(moving_avg_);
        } else {
            moving_avg_ = linear_moving_avg(data, opt.window);
            calc_freq_dist(moving_avg_);
            smooth_freq_dist();
        }
    } else {
        calc_freq_dist(data);
    }

    calc_slopes();
    find_local_maxima();
    find_runs();
    find_valid_maxima(opt.runlen, opt.fmax);

    if (opt.debug) {
        std::cerr << "angle: " << idx << '\n';
        write_local_maxima();
    }

    merge_maxima(opt.smin);
    (circular_) ? find_circular_cuts() : find_linear_cuts();

    if (opt.debug) {
        write_cuts();
    }

    if (!repex_) {
        find_states(opt.boutlen);
    } else {
        states_.resize(frames_);

        for (int i=0; i<frames_; ++i) {
            states_[i] = find_state(data[i]);
        }
    }
}

dVector
TorsionData::linear_moving_avg(const dVector& data, int window)
{
    DASH_PRECONDITION(window%2 != 0);
    DASH_PRECONDITION(data.size() > window);

    const int offset = (window-1)/2;
    const int npts = data.size();
    dVector avg(npts);

    for (int i=0; i<npts-window+1; ++i) {
        double sum = 0;

        for (int j=0; j<window; j++) {
            sum += data[i+j];
        }

        avg[i+offset] = sum/window;
    }

    // use original values at start and end of trajectory
    for (int i=0; i<offset; i++) {
        avg[i] = data[i];
        avg[npts-i-1] = data[npts-i-1];
    }

    return avg;
}

void
TorsionData::calc_freq_dist(const dVector& angles)
{
    std::vector<double> boundary(bins_+1);
    freq_.resize(bins_);
    boundary[0] = data_min_;

    for (int i=1; i<=bins_; i++) {
        boundary[i] = boundary[i-1] + binsize_;
        freq_[i-1] = 0;
    }

    // accumulate frequency distribution
    for (int i=0; i<angles.size(); i++) {

        // treat first bin separately to catch minimum value (e.g. -180)
        if (angles[i] >= boundary[0] && angles[i] <= boundary[1]) {
            ++freq_[0];
        }

        for (int j=1; j<bins_; j++) {
            if (angles[i] > boundary[j] && angles[i] <= boundary[j+1]) {
                ++freq_[j];
            }
        }
    }

    DASH_POSTCONDITION(std::accumulate(freq_.begin(), freq_.end(), 0) == static_cast<int>(angles.size()));
}

void
TorsionData::smooth_freq_dist()
{
    const int window = 3;
    const int offset = (window - 1)/2;
    std::vector<int> smooth_freq(bins_);

    for (int i=0; i<bins_-window+1; i++) {
        double sum = 0;

        for (int j=0; j<window; j++) {
            sum += freq_[i+j];
        }

        smooth_freq[i+offset] = static_cast<int>(trunc(sum/window));
    }

    // use original angles at start and end of trajectory
    for (int i=0; i<offset; i++) {
        smooth_freq[i] = freq_[i];
        smooth_freq[bins_-i-1] = freq_[bins_-i-1];
    }

    freq_ = smooth_freq;
}

void
TorsionData::calc_slopes()
{
    slope_.resize(bins_);

    for (int i=0; i<bins_; i++) {
        slope_[i] = sign(freq_[(i+1)%bins_] - freq_[i]);
    }
}

void
TorsionData::find_local_maxima()
{
    for (int i=0; i<bins_; i++) {
        if (slope_[i] == 1) {
            int ii = (i+1)%bins_;

            if (slope_[ii] == -1) {
                // simple maximum
                allmax_.push_back(std::make_shared<Maximum>(ii, freq_[ii], 0));
            } else if (slope_[ii] == 0) {
                // reached a plateau
                int flat = 1;
                int j = ii;

                // level ground
                while (slope_[++j%bins_] == 0) {
                    ++flat;
                }

                if (slope_[j%bins_] == -1) {
                    // plateau maximum
                    allmax_.push_back(std::make_shared<Maximum>(ii, freq_[ii], flat));
                }
            }
        }
    }
}

void
TorsionData::find_runs()
{
    for (std::vector<std::shared_ptr<Maximum>>::iterator i=allmax_.begin(); i!=allmax_.end(); ++i) {
        std::shared_ptr<Maximum> max = *i;
        int bin = (bins_ + max->bin - 1) % bins_; // preceding bin

        DASH_PRECONDITION(slope_[bin] == 1 && slope_[max->bin] != 1);

        // find preceding uphill sequence
        while (slope_[bin] != -1) {
            max->nonneg++;
            max->pos += slope_[bin];
            bin = (bins_ + bin - 1) % bins_;
        }

        // start of downhill sequence
        bin = (max->bin + max->flat) % bins_;

        // find following downhill sequence
        while (slope_[bin] != 1) {
            max->nonpos++;
            max->neg -= slope_[bin];
            bin = (bin + 1) % bins_;
        }
    }
}

void
TorsionData::write_local_maxima()
{
    std::cerr << "local maxima\n";

    for (std::vector<std::shared_ptr<Maximum>>::iterator i=allmax_.begin(); i!=allmax_.end(); ++i) {
        std::cerr << "bin = " <<  (*i)->bin
                  << ", angle = " << bin_mid((*i)->bin)
                  << ", value = " << (*i)->value
                  << ", valid = " << (*i)->valid
                  << ", nonneg = " << (*i)->nonneg
                  << ", pos = " << (*i)->pos
                  << ", flat = " << (*i)->flat
                  << ", nonpos = " << (*i)->nonpos
                  << ", neg = " << (*i)->neg << '\n';
    }
}

bool
TorsionData::maximum_found()
{
    for (std::vector<std::shared_ptr<Maximum>>::iterator i=allmax_.begin(); i!=allmax_.end(); ++i) {
        if ((*i)->valid) return true;
    }

    return false;
}

void
TorsionData::validate_maxima(int runlen, float fmax)
{
    for (std::vector<std::shared_ptr<Maximum>>::iterator i=allmax_.begin(); i!=allmax_.end(); ++i) {
        std::shared_ptr<Maximum> max = *i;

        max->valid = (max->value >= frames()/10) ||
            (max->value >= fmax*frames()/100 && (max->pos >= runlen || max->neg >= runlen));
        //(max->value >= fmax*frames()/100 && max->pos >= runlen && max->neg >= runlen);
    }
}

void
TorsionData::find_valid_maxima(int runlen, float fmax)
{
    validate_maxima(runlen, fmax);
    if (maximum_found()) return;

    while (--runlen > 1) {
        std::cerr << "WARNING: no local maximum found for angle " << index_ << '\n';
        std::cerr << "WARNING: runlen reduced to " << runlen << '\n';
        validate_maxima(runlen, fmax);
        if (maximum_found()) return;
    }

    std::ostringstream msg;
    msg << "no local maximum found for angle " << index_;
    DASH_RUNTIME_ERROR(msg.str());
}

void
TorsionData::merge_maxima(float smin)
{
    std::vector<double> maxtmp;

    for (std::vector<std::shared_ptr<Maximum>>::iterator i=allmax_.begin(); i!=allmax_.end(); ++i) {
        if ((*i)->valid) maxtmp.push_back(bin_mid((*i)->bin));
    }

    maxima_.push_back(maxtmp[0]);

    for (size_t i=1; i<maxtmp.size(); ++i) {
        size_t nmax = maxima_.size();
        double d = std::abs(maxima_[nmax-1] - maxtmp[i]);

        if (circular_ && d>180) {
            d = 360-d;
        }

        if (d > smin) {
            maxima_.push_back(maxtmp[i]);
        } else {
            maxima_[nmax-1] = circular::mean(maxima_[nmax-1], maxtmp[i]);
        }
    }

    std::sort(maxima_.begin(), maxima_.end());
}

double
TorsionData::find_min_cut(double c) {
    DASH_PRECONDITION(c >= -180 && c <= 180);

    if (rev85_) return c;

    int bin = static_cast<int>(trunc((c+180)/binsize_));
    double rtnval;

    if (slope_[bin] > 0) {
        do {
            bin = ((bin - 1) % bins_ + bins_) % bins_; // ensure positive modulo
        } while (slope_[bin] > 0);

        if (slope_[bin] < 0) {
            bin = (bin + 1) % bins_;
            rtnval = bin*binsize_ - 180;
        } else {
            rtnval = bin_mid(bin);
        }
    } else if (slope_[bin] < 0) {
        do {
            bin = (bin + 1) % bins_;
        } while (slope_[bin] < 0);

        if (slope_[bin] > 0) {
            rtnval = bin*binsize_ - 180;
        } else {
            rtnval = bin_mid(bin);
        }
    } else {
        // slope 0
        return c;
    }

    return rtnval;
}

void
TorsionData::find_circular_cuts()
{
    const int nmax = maxima_.size();
    cuts_.reserve(nmax + 2);
    codes_.reserve(nmax + 1);

    if (nmax == 1) { // special case for single states
        cuts_.push_back(-180);
        cuts_.push_back(180);
        codes_.push_back(1);
    } else { // more than one state
        // cut zero is always -pi
        cuts_.push_back(-180);
        codes_.push_back(1);

        // check position of first cut
        double midpt = (maxima_[0] + maxima_[nmax-1])/2.0;
        double cut0 = (midpt<0) ? midpt+180 : midpt-180;
        cut0 = find_min_cut(cut0);

        if ((cut0 < maxima_[0]) && (cut0 > -180)) {
            cuts_.push_back(cut0);
            codes_.push_back(1);
        }

        // deal with interior cuts
        for (int i=1; i<nmax; i++) {
            double c = (maxima_[i] + maxima_[i-1])/2.0;
            cuts_.push_back(find_min_cut(c));
            codes_.push_back(codes_[codes_.size() - 1] + 1);
        }

        // check position of last cut
        if (cut0 > maxima_[nmax-1]) {
            if (cut0 < 180) {
                cuts_.push_back(cut0);
                codes_.push_back(1);
            }
        } else if (cut0 != -180) {
            codes_[0] = codes_[codes_.size() - 1];
        }

        cuts_.push_back(180);
    }
}

void
TorsionData::find_linear_cuts()
{
    const int nmax = maxima_.size();
    cuts_.reserve(nmax + 2);
    codes_.reserve(nmax + 1);

    if (nmax == 1) { // special case for single states
        cuts_.push_back(data_min_);
        cuts_.push_back(data_max_);
        codes_.push_back(1);
    } else { // more than one state
        cuts_.push_back(data_min_);
        codes_.push_back(1);

        // deal with interior cuts
        for (int i=1; i<nmax; i++) {
            cuts_.push_back((maxima_[i] + maxima_[i-1])/2.0);
            codes_.push_back(codes_[codes_.size() - 1] + 1);
        }

        cuts_.push_back(data_max_);
    }
}

void
TorsionData::write_cuts()
{
    std::cerr << "cuts: ";

    for (auto c : cuts_) {
        std::cerr << c << " ";
    }

    std::cerr << '\n';
}

void
TorsionData::find_states(int boutlen)
{
    int last;
    int current;
    int next;
    int transient = 0;
    int nextlen = 0;
    int first_state = 0;

    std::vector<int> raw_state(frames_);
    states_.resize(frames_);

    raw_state[0] = states_[0] = last = current = next = find_state(moving_avg_[0]);
    transitions_ = 0;
    transient = 0;
    nextlen = 0;

    for (int i=1; i<frames_; i++) {
        // initially assign "last" to each state
        // to avoid leaving a transient of unassigned
        // states at the end of the sequence
        states_[i] = last;

        // now process the new state
        current = raw_state[i] = find_state(moving_avg_[i]);

        if (transitions_ == 0 && current == last) {
            first_state++;
            if (first_state >= boutlen) {
                ++transitions_;
                for (int k=0; k<=first_state; k++) {
                    states_[k] = current;
                }
            }
        } else if (transient == 0 && current == last) {
            // remained in last state
            states_[i] = current;
        } else if (transient == 0 && current != last) {
            // started a new transient
            transient = 1;
            nextlen = 1;
            next = current;
        } else if (transient < boutlen && current == last) {
            // a short transient is over
            // assign current state to transient
            for (int j=(i-transient); j<=i; j++) {
                states_[j] = current;
            }

            // reset counters
            transient = 0;
            nextlen = 0;
        } else {
            // in mid-transient
            ++transient;

            if (current == next) { // remained in a possible next state
                ++nextlen;
                if (nextlen >= boutlen) { // transition to next state
                    ++transitions_;
                    if (transitions_ == 1) {
                        // first state, assign this state to whole sequence so far
                        for (int j=0; j<=i; j++) {
                            states_[j] = current;
                        }
                    }
                    // assign next state to backlog
                    for (int j=(i-nextlen+1); j<=i; j++) {
                        states_[j] = current;
                    }

                    // deal with transient
                    // assign first half to last state, second half to next state
                    if (transient > nextlen) {
                        int t1 = i-transient+1; // index of first transient state
                        int t2 = i-nextlen;     // index of last transient state
                        int gap = t2-t1+1;      // length of transient

                        // length of transient to assign to last state
                        int gap1 = static_cast<int>(ceil(gap/2.0));

                        // length of transient to assign to next state
                        int gap2 = gap-gap1;

                        for (int j=0; j<gap1; j++) {
                            states_[t1+j] = last;
                        }

                        for (int j=0; j<gap2; j++){
                            states_[t2-j] = current;
                        }
                    }

                    // reset counters
                    transient = 0;
                    last = current;
                    nextlen = 0;
                }
            } else { // current != next - a new possible transition
                next = current;
                nextlen = 1;
            }
        }
    } //i-loop

    // calculate number of states reassigned by smoothing
    for (int i=0; i<frames_; i++) {
        if (raw_state[i] != states_[i]) {
            ++reassigned_;
        }
    }


    if (debug_) {
        const int N = moving_avg_.size();

        std::cerr << "\ntime    moving    raw  final\n"
                  <<   "step    average  state state\n"
                  << std::fixed << std::setprecision(2);

        for (int i=0; i<N; i++) {
            std::cerr << std::setw(6) << std::left << i+1 << std::right
                      << " " << std::setw(8) << moving_avg_[i]
                      << " " << std::setw(5) << raw_state[i]
                      << " " << std::setw(5) << states_[i]
                      << std::endl;
        }

        std::cerr.unsetf(std::ios::fixed);
    }
}

int
TorsionData::find_state(double angle)
{
    int i;
    bool state_found = false;
    int ncuts = cuts_.size();

    for (i=0; i<ncuts-1; i++) {
        if (cuts_[i] <= angle && angle < cuts_[i+1]) {
            state_found = true;
            break;
        }
    }

    // special case for angle = 180: treat it as -180
    if (angle == cuts_[ncuts-1]) {
        state_found = true;
        i = 0;
    }

    DASH_POSTCONDITION(state_found);
    return codes_[i];
}

void
TorsionData::write(std::ostream& os) const
{
    os << "[ANGLE_" << index_ << "]\n"
       << "maxima      : ";

    if (circular_) {
        os  << std::fixed << std::setprecision(0) << std::noshowpoint;
    } else {
        os  << std::fixed << std::setprecision(2);
    }

    for (std::vector<double>::size_type i=0; i<maxima_.size()-1; i++) {
        os << maxima_[i] << ", ";
    }

    os << maxima_[maxima_.size()-1] << '\n';

    os << "states      : ";

    for (std::vector<double>::size_type i=0; i<cuts_.size()-2; i++) {
        os << codes_[i] << " = [" << cuts_[i] << ", " << cuts_[i+1] << "), ";
    }

    os << codes_[cuts_.size()-2] << " = [" << cuts_[cuts_.size()-2] << ", " << cuts_[cuts_.size()-1] << ")\n";

    if (!repex_) {
        os << "transitions : " << transitions_ << '\n'
           << "reassigned  : " << reassigned_ << " ("
           << std::showpoint << std::setprecision(2)
           << (100.0*reassigned_)/frames_ << "%)\n";
    }
}

void
TorsionData::write_histogram(std::ostream& os) const
{
    os << "[ANGLE_" << index_ << "_HISTOGRAM]\n"
       << "Bin     Count\n";

    os << std::setprecision(0) << std::noshowpoint;

    for (int i=0; i<static_cast<int>(freq_.size()); i++) {
        os << std::setw(4) << std::right << -180 + 4*i
           << std::setw(4) << ' '
           << std::setw(10) << std::left << freq_[i] << '\n';
    }

    os << std::right;
}
