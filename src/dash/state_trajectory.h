//  $Id: state_trajectory.h 131 2017-11-29 08:52:35Z dw $
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

#ifndef DASH_STATE_TRAJECTORY_H
#define DASH_STATE_TRAJECTORY_H

#include "dash/eigen.h"
#include "dash/state.h"

#include <map>
#include <ostream>
#include <set>
#include <string>
#include <vector>

struct StateTrajectory {
    std::string tag;
    state_map states;
    state_sequence seq;
    int transitions;
    int reassigned;
    int timestep;
    dMatrix circular_sim;
    dMatrix cosine_sim;

    void index(const state_set& states);
    void calc(const Eigen::Map<dMatrix>& angle_map);
    void calc_transitions();
    void calc_freq();
    void calc_bouts();
    void calc_stats(const Eigen::Map<dMatrix>& angle_map);
    void calc_frames(const Eigen::Map<dMatrix>& angle_map);
    void calc_circular_similarity();
    void calc_cosine_similarity();

    void write(std::ostream& os) const;
    void write_state_info(std::ostream& os) const;
    void write_trajectory_info(std::ostream& os) const;
    void write_states(std::ostream& os) const;
    void write_state_dist(std::ostream& os) const;
    void write_state_sequence(std::ostream& os) const;
    void write_trajectory(std::ostream& os) const;
    void write_transitions(std::ostream& os) const;
    void write_reassigned(std::ostream& os) const;
    void write_bouts(std::ostream& os) const;
    void write_bout_times(std::ostream& os) const;
    void write_stats(std::ostream& os) const;
    void write_circular_similarity(std::ostream& os) const;
    void write_cosine_similarity(std::ostream& os) const;
    void write_vector(const std::vector<int>& v, std::ostream& os, const char sep) const;
    void write_vector(const std::vector<double>& v, std::ostream& os, int width, int prec) const;
};

#endif // DASH_STATE_TRAJECTORY_H
