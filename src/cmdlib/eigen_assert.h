//  $Id: eigen_assert.h 116 2017-09-21 16:19:22Z dw $
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

// THIS FILE MUST BE INCLUDED BEFORE ANY EIGEN HEADERS

// The Eigen library aborts on failed assertions.
// This overrides the definition of eigen_assert
// in Eigen/src/Core/util/Macros.h and converts
// failed assertions to CmdLibExceptions,
// which can then be caught.

#ifndef CMDLIB_EIGEN_ASSERT_H
#define CMDLIB_EIGEN_ASSERT_H

#include "cmdlib/exception.h"

#define eigen_assert(expr)                          \
    if ( !(expr) ) {                                \
        std::ostringstream os;                      \
        os << ": eigen assertion [" << #expr        \
            << "] failed in file " << __FILE__      \
            << " at line " << __LINE__;             \
        throw cmdlib::CmdLibException(os.str());    \
    }

#endif // CMDLIB_EIGEN_ASSERT_H
