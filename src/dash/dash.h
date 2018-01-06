//  $Id: dash.h 131 2017-11-29 08:52:35Z dw $
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

#ifndef DASH_DASH_H
#define DASH_DASH_H

#include "dash/dash_options.h"
#include "dash/eigen.h"
#include "dash/state_trajectory.h"
#include "dash/torsion_data.h"
#include "dash/trajectory.h"

#include "cmdlib/pca.h"

#include <ctime>
#include <ostream>
#include <set>
#include <string>
#include <vector>

class Dash {
 public:
    Dash(const Trajectory& trj, const DashOptions& opt);
    ~Dash();

    void run();
    std::string trajectory_input_file() const { return trj.input_file; }
    int vars() const { return trj.vars; }
    int frames() const { return trj.frames; }
    std::string input_time() const;
    std::string dash_time() const;
    std::string total_time() const;
    std::string summary() const;
    const StateTrajectory dash_trajectory() const { return dash_trj; }
    const StateTrajectory repex_trajectory() const { return repex_trj; }
    const state_map& dash_state_map() const { return dash_trj.states; }
    const repex_state_set& new_repex_states_ref() const { return new_repex_states; }
    const std::vector<TorsionData*>& torsion_data_ptr() const { return torsion_data; }
    const cmdlib::PCA* pca() const { return pca_; }
    bool time_series() const { return !opt.repex; }
    int timestep() const { return opt.timestep; }
    void write(std::ostream& os) const;
    void write_labelled_data_file(std::string filename) const;
    bool circular() const { return opt.circular; }
#ifndef NOAMBER
    bool write_snapshots(std::string& msg) const;
    std::string top_file() const { return trj.top_file; }
    std::string trj_file() const { return trj.trj_file; }
#endif

 private:
    const Trajectory trj;
    const DashOptions opt;

    clock_t clock_start_input;
    clock_t clock_start_dash;
    clock_t clock_end;

    std::vector<TorsionData*> torsion_data;
    state_set combined_states, dash_states, repex_states;
    StateTrajectory combined_trj, smoothed_combined_trj, smoothed_trj, dash_trj, repex_trj;
    repex_state_set new_repex_states;
    repex_state_set repex_state_sequence;

    cmdlib::PCA *pca_;

    void calc_combined_trj(const Eigen::Map<dMatrix>& angle_map);
    void calc_smoothed_combined_trj(int smooth);
    void calc_smoothed_trj(const Eigen::Map<dMatrix>& angle_map);
    void calc_dash_trj(const Eigen::Map<dMatrix>& angle_map, int rough);
    void calc_repex_trj(const Eigen::Map<dMatrix>& angle_map);
    int  calc_reassigned(const state_sequence& input_seq, state_sequence& output_seq);
    void calc_repex_circular_similarity();
    void calc_repex_cosine_similarity();

    void write_summary(std::ostream& os) const;
    void write_torsion_data(std::ostream& os) const;
    void write_state_set(const state_set& set, const std::string& tag, std::ostream& os) const;
    void write_state_sequence(const state_set& set, const state_sequence& seq, const std::string& tag, std::ostream& os) const;
    void write_state_dist(const state_set& set, const std::string& tag, const state_sequence& seq, std::ostream& os) const;
    void write_trajectory(const state_set& set, const state_sequence& seq, const std::string& tag, std::ostream& os) const;
    void write_bouts(const state_set& set, const state_sequence& seq, const std::string& tag, std::ostream& os) const;
    void write_times(std::ostream& os) const;
    void write_repex_states(std::ostream& os) const;
    void write_repex_trj(std::ostream& os) const;
    void write_repex_circular_similarity(std::ostream& os) const;
    void write_repex_cosine_similarity(std::ostream& os) const;
    void write_pca(std::ostream& os) const;
    void write_pca_summary(std::ostream& os) const;
    void write_pca_coefficients(std::ostream& os) const;
    void write_pca_weights(std::ostream& os) const;
    void write_pca_scaling(std::ostream& os) const;
    std::string elapsed_time(clock_t start, clock_t stop) const;

    state_set dummy_state_set;
    repex_state_set dummy_repex_state_set;
};

#endif // DASH_DASH_H
