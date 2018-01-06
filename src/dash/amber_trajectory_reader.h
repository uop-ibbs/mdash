//  $Id: amber_trajectory_reader.h 113 2017-08-18 14:59:42Z dw $
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

#ifndef DASH_AMBER_TRAJECTORY_READER_H
#define DASH_AMBER_TRAJECTORY_READER_H

#include "dash/amber_options.h"

#include <string>
#include <vector>

class AmberTrajectoryReader {
 public:
    const std::string cpptraj_in() const { return cpptraj_in_; };
    const std::string cpptraj_out() const { return cpptraj_out_; };
    const std::string cpptraj_err() const { return cpptraj_err_; };

    bool read(const AmberOptions& opt, std::string& msg);

 private:
    std::string cpptraj_in_;
    std::string cpptraj_out_;
    std::string cpptraj_err_;

    std::string write_cpptraj_in(const AmberOptions& opt);
};

#endif // DASH_AMBER_TRAJECTORY_READER_H
