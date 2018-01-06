//  $Id: cmdlib.h 52 2015-07-20 14:16:45Z dw $
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

#ifndef CMDLIB_H
#define CMDLIB_H

#include "cmdlib/eigen_assert.h"
#undef Success  // to avoid definition of Success in X.h; yuck
#include <Eigen/Core>
#include <string>

/// \defgroup CppLib C++ Library

/// All CMDLIB classes and functions are contained in the \em cmdlib namespace.
namespace cmdlib
{
    const std::string VERSION("1.0.0");

    /// Eigen double, dynamically sized matrices.
    typedef Eigen::MatrixXd Matrix;

    /// Eigen double, dynamically sized vectors.
    typedef Eigen::VectorXd Vector;
} // namespace cmdlib

#endif // CMDLIB_H
