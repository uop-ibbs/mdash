//  $Id: amber_trajectory_reader.cpp 113 2017-08-18 14:59:42Z dw $
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

#include "dash/amber_trajectory_reader.h"
#include "dash/external.h"

#include <boost/algorithm/string.hpp>

#include <cstdlib>
#include <fstream>
#include <string>
#include <sstream>
#include <system_error>

bool
AmberTrajectoryReader::read(const AmberOptions& opt, std::string& msg)
{
    cpptraj_in_ = write_cpptraj_in(opt);
    return external::cpptraj(cpptraj_in_, cpptraj_out_, cpptraj_err_, msg);
}

std::string
AmberTrajectoryReader::write_cpptraj_in(const AmberOptions& opt)
{
    std::ostringstream oss;

    oss << "parm " << opt.top_file << '\n';

    std::string trj_file(opt.trj_file); // circumvent constness
    std::vector<std::string> files;
    std::string sep = " ,:;";

    boost::trim_if(trj_file, boost::is_any_of(sep));
    boost::split(files, trj_file, boost::is_any_of(sep), boost::token_compress_on);

    for (auto f : files) {
        oss << "trajin " << f << '\n';
    }

    oss << "multidihedral "
        << (opt.phi?"phi ":"")
        << (opt.psi?"psi ":"")
        << (opt.chi?"chip ":"")
        << (opt.omega?"omega ":"");

    if (!opt.residues.empty()) {
        oss << " resrange " << opt.residues;
    }

    oss << " out "
        << opt.dash_input_file
        << "\nnoprogress\ngo\nquit\ny\n";

    return oss.str();
}
