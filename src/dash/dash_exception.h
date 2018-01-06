//  $Id: dash_exception.h 116 2017-09-21 16:19:22Z dw $
//
//  Copyright (C) 2015 Centre for Molecular Design, University of Portsmouth.
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

#ifndef DASH_DASH_EXCEPTION_H
#define DASH_DASH_EXCEPTION_H

#include <iosfwd>
#include <sstream>
#include <stdexcept>
#include <string>

#define DASH_PRECONDITION(expr)                 \
    if ( !(expr) ) {                            \
        std::ostringstream os;                  \
        os << __FUNCTION__                      \
           << ": precondition [" << #expr       \
           << "] failed in file " << __FILE__   \
           << " at line " << __LINE__;          \
        throw DashException(os.str());          \
    }

#define DASH_POSTCONDITION(expr)                \
    if ( !(expr) ) {                            \
        std::ostringstream os;                  \
        os << __FUNCTION__                      \
           << ": postcondition [" << #expr      \
           << "] failed in file " << __FILE__   \
           << " at line " << __LINE__;          \
        throw DashException(os.str());          \
    }

#define DASH_RUNTIME_ERROR(what)                \
    {                                           \
        std::ostringstream os;                  \
        os << __FUNCTION__                      \
           << ": runtime error [" << what       \
           << "] in file " << __FILE__          \
           << " at line " << __LINE__;          \
        throw DashException(os.str());          \
    }

class DashException : public std::runtime_error
{
 public:
    explicit DashException(const std::string& what) : std::runtime_error(what) {}
    ~DashException() throw() {}
};

std::ostream& operator<< (std::ostream& os, const DashException& e);

#endif // DASH_DASH_EXCEPTION_H
