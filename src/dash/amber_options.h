//  $Id: amber_options.h 111 2017-08-08 16:08:52Z dw $
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

#ifndef DASH_AMBER_OPTIONS_H
#define DASH_AMBER_OPTIONS_H

#include <string>

struct AmberOptions
{
    std::string top_file;
    std::string trj_file;
    std::string residues;
    bool phi;
    bool psi;
    bool chi;
    bool omega;
    bool save_dash_input;
    bool save_cpptraj_input;
    bool save_cpptraj_output;
    std::string dash_input_file = "amberdash.in";

    AmberOptions();
};

#endif // DASH_AMBER_OPTIONS_H
