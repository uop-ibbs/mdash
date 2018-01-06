//  $Id: dash_sim.h 116 2017-09-21 16:19:22Z dw $
//
//  Copyright (C) 2017 School of Pharmacy and Biomedical Sciences, University of Portsmouth.
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

#ifndef DASH_DASH_SIM_H
#define DASH_DASH_SIM_H

#include <istream>
#include <string>
#include <vector>
#include <map>

namespace dashsim
{
    typedef std::vector<std::vector<double>> matrix2d;
    typedef std::map<std::string, matrix2d> state_angle_map;

    void dash_sim(const std::string& file1, const std::string& file2);
    void read_dash_output_file(std::string file, state_angle_map& angles);
    void read_state_mean_angles(std::istream& is, state_angle_map& angles, const std::string& state_type, int num_angles);
    void write_similarity_matrix(const matrix2d& sim, const std::string& type, const std::string& file1, const std::string& file2);
} //dashsim

#endif // DASH_DASH_SIM_H
