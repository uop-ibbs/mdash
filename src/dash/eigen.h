//  $Id: eigen.h 81 2016-02-12 17:12:47Z dw $
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

#ifndef DASH_EIGEN_H
#define DASH_EIGEN_H

#include "cmdlib/eigen_assert.h"
#undef Success  // to avoid definition of Success in X.h; yuck
#include <Eigen/Core>

// use row-major storage for double matrices to simplify mapping onto dash input data
typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> dMatrix;
typedef Eigen::MatrixXi iMatrix;
typedef Eigen::VectorXd dVector;

#endif // DASH_EIGEN_H
