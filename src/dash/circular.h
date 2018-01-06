//  $Id: circular.h 116 2017-09-21 16:19:22Z dw $
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

#ifndef DASH_CIRCULAR_H
#define DASH_CIRCULAR_H

#include "dash/eigen.h"
#include <vector>

namespace circular
{
    double mean(double x, double y);
    double mean(const dVector& x);
    void moment(const dVector& x, double& mean, double& sdev);
    dVector moving_average(const dVector& angles, int window);
    double distance(const std::vector<double>& x, const std::vector<double>& y);
    double similarity(const std::vector<double>& x, const std::vector<double>& y);
    double cosine_similarity(const std::vector<double>& x, const std::vector<double>& y);
} // namespace circular

#endif // DASH_CIRCULAR_H
