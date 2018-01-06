//  $Id: external.h 113 2017-08-18 14:59:42Z dw $
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

#ifndef DASH_EXTERNAL_H
#define DASH_EXTERNAL_H

#include <string>
#include <system_error>
#include <vector>

namespace external
{
    int execute(std::string path, std::vector<std::string> args,
                std::string std_in, std::string& std_out, std::string& std_err,
                std::error_code& ec);
    bool save(std::string s, std::string filename);
    bool cpptraj(std::string in, std::string& out, std::string& err, std::string& msg);
} // namespace external

#endif // DASH_EXTERNAL_H
