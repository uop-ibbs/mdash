//  $Id: trajectory.h 123 2017-10-16 13:29:54Z dw $
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

#ifndef DASH_TRAJECTORY_H
#define DASH_TRAJECTORY_H

#include <ostream>
#include <string>
#include <vector>

struct Trajectory {
    std::string input_file;
    std::string top_file;
    std::string trj_file;
    int vars;
    int frames;
    std::vector<double> data;

    bool read(std::string input_file, std::string& msg, std::string top_file = "", std::string trj_file = "");
    bool read_dims(std::string input_file, bool& amber_trj, std::string& msg);
    bool read_data(std::string input_file, bool amber_trj, std::string& msg);
    void write(std::ostream& os) const;
};

#endif // DASH_TRAJECTORY_H
