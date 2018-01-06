//  $Id: torsion_data.h 129 2017-11-28 14:41:16Z dw $
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

#ifndef DASH_TORSION_DATA_H
#define DASH_TORSION_DATA_H

#include "dash/dash_options.h"
#include "dash/eigen.h"

#include <memory>
#include <vector>

class TorsionData {
 public:
    TorsionData(int index, const dVector& data, const DashOptions& opt);

    int frames() const { return frames_; }
    double bin_min(int bin) const { return data_min_ + bin*binsize_; }
    double bin_mid(int bin) const { return data_min_ + bin*binsize_ + binsize_/2; }
    int state(int i) const { return states_[i]; }
    const dVector& data() const { return moving_avg_; }
    const std::vector<double>& maxima() const { return maxima_; }
    const std::vector<double>& cuts() const { return cuts_; }
    const std::vector<int>& freq() const { return freq_; }
    const std::vector<int>& codes() const { return codes_; }
    int reassigned() const { return reassigned_; }
    void write(std::ostream& os) const;
    void write_histogram(std::ostream& os) const;
    bool circular() const { return circular_; }

 private:
    struct Maximum;

    int index_;
    int frames_;
    int bins_;
    bool circular_;
    bool repex_;
    bool debug_;
    bool rev85_;
    double binsize_;
    double data_min_;
    double data_max_;
    dVector moving_avg_;
    std::vector<double> maxima_;
    std::vector<double> cuts_;
    std::vector<int> freq_;
    std::vector<int> codes_;
    std::vector<int> states_;
    int transitions_;
    int reassigned_;
    std::vector<std::shared_ptr<Maximum> > allmax_;
    std::vector<int> slope_;

    dVector linear_moving_avg(const dVector& data, int window);
    void calc_freq_dist(const dVector& data);
    void smooth_freq_dist();
    void find_circular_cuts();
    void find_linear_cuts();
    void find_states(int boutlen);
    int find_state(double angle);

    void find_local_maxima();
    void find_runs();
    void calc_slopes();
    void find_valid_maxima(int runlen, float fmax);
    void validate_maxima(int runlen, float fmax);
    bool maximum_found();
    void find_maxima();
    void merge_maxima(float smin);
    void write_local_maxima();
    void write_cuts();
    double find_min_cut(double c);
};

struct TorsionData::Maximum {
    int bin;
    int value;
    int pos;
    int neg;
    int flat;
    int nonpos;
    int nonneg;
    bool valid;

    Maximum(int b, int v, int f) {
        bin = b;
        value = v;
        flat = f;
        pos = neg = nonpos = nonneg = 0;
        valid = false;
    }
};

#endif // DASH_TORSION_DATA_H
