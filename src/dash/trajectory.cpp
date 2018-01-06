//  $Id: trajectory.cpp 131 2017-11-29 08:52:35Z dw $
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

#include "dash/trajectory.h"

#include <boost/algorithm/string.hpp>
#include <boost/iostreams/filter/bzip2.hpp>
#include <boost/iostreams/filter/gzip.hpp>
#include <boost/iostreams/filtering_streambuf.hpp>

#include <fstream>
#include <istream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

using boost::trim_left;
using boost::trim_right_if;
using boost::is_any_of;
using boost::token_compress_on;
using boost::split;

bool
Trajectory::read(std::string dash_input_file, std::string& msg, std::string ambtop_file, std::string ambtrj_file)
{
    input_file = dash_input_file;
    top_file = ambtop_file;
    trj_file = ambtrj_file;
    bool amber_trj;

    return read_dims(dash_input_file, amber_trj, msg) && read_data(dash_input_file, amber_trj, msg);
}

bool
Trajectory::read_dims(std::string file, bool& amber_trj, std::string& msg)
{
    std::ifstream ifs(file, std::ios_base::in | std::ios_base::binary);

    if (!ifs) {
        msg = "Failed to open file " + file;
        return false;
    }

    boost::iostreams::filtering_streambuf<boost::iostreams::input> isb;

    if (boost::ends_with(file, ".gz")) {
        isb.push(boost::iostreams::gzip_decompressor());
    } else if (boost::ends_with(file, ".bz2")) {
        isb.push(boost::iostreams::bzip2_decompressor());
    }

    isb.push(ifs);
    std::istream is(&isb);

    int rows = 0;
    int cols = 0;

    // find number of variables on first line
    std::string line;
    std::vector<std::string> tokens;

    if (getline(is, line)) {
        ++rows;
        trim_left(line); // remove leading spaces
        trim_right_if(line, is_any_of(" \t\r")); // remove trailing whitespace
        split(tokens, line, is_any_of(" \t"), token_compress_on);
        cols = tokens.size();
        amber_trj = (tokens[0] == "#Frame");

        if (line.length() == 0 || cols == 0) {
            std::ostringstream os;
            os << "No angles found in first line of file " << input_file;
            msg = os.str();
            return false;
        }
    } else {
        std::ostringstream os;
        os << "No frames found in file " << input_file;
        msg = os.str();
        return false;
    }

    // count frames, checking number of variables on each line
    while (getline(is, line)) {
        ++rows;
        trim_left(line);
        trim_right_if(line, is_any_of(" \t\r"));
        split(tokens, line, is_any_of(" \t"), token_compress_on);

        if (static_cast<int>(tokens.size()) != cols) {
            std::ostringstream os;

            os << "Failed to read file " << input_file
               << "\nInconsistent variables at line " << rows
               << ": expecting " << cols
               << ", found " << tokens.size();

            msg = os.str();
            return false;
        }
    }

    if (amber_trj) {
        frames = rows-1;
        vars = cols-1;
    } else {
        frames = rows;
        vars = cols;
    }

    return true;
}

bool
Trajectory::read_data(std::string file, bool amber_trj, std::string& msg)
{
    std::ifstream ifs(file, std::ios_base::in | std::ios_base::binary);

    if (!ifs) {
        msg = "Failed to open file " + file;
        return false;
    }

    boost::iostreams::filtering_streambuf<boost::iostreams::input> isb;

    if (boost::ends_with(file, ".gz")) {
        isb.push(boost::iostreams::gzip_decompressor());
    } else if (boost::ends_with(file, ".bz2")) {
        isb.push(boost::iostreams::bzip2_decompressor());
    }

    isb.push(ifs);
    std::istream is(&isb);

    if (!data.empty()) data.clear(); // gui may read more than one trajectory

    if (amber_trj) {
        std::string line;

        // cpptraj adds a header line and frame numbers
        getline(is, line); // ignore the header line
        int framenum;

        while (getline(is, line)) {
            std::istringstream is(line);
            is >> framenum; // ignore the frame number
            copy(std::istream_iterator<double>(is), std::istream_iterator<double>(), std::back_inserter(data));
        }
    } else {
        copy(std::istream_iterator<double>(is), std::istream_iterator<double>(), std::back_inserter(data));
    }

    return true;
}

void
Trajectory::write(std::ostream& os) const {
    os << "[TRAJECTORY]\n"
       << "file      : " << input_file << '\n'
       << "variables : " << vars << '\n'
       << "frames    : " << frames << "\n\n";
}
