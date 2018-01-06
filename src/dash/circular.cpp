//  $Id: circular.cpp 124 2017-10-23 13:55:21Z dw $
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

#include "dash/circular.h"
#include "dash/dash_exception.h"
#include <cmath>
#include <boost/math/constants/constants.hpp>
#include <Eigen/Dense>

using boost::math::double_constants::pi;

namespace circular
{
const double deg2rad = pi/180;

double
mean(double x, double y)
{
    x *= deg2rad;
    y *= deg2rad;
    double s = sin(x) + sin(y);
    double c = cos(x) + cos(y);
    return atan2(s,c)/deg2rad;
}

double
mean(const dVector& x)
{
    double sumsin = 0;
    double sumcos = 0;

    for (int i = 0; i < x.size(); ++i) {
        double theta = x(i)*deg2rad;
        sumsin += sin(theta);
        sumcos += cos(theta);
    }

    return atan2(sumsin, sumcos)/deg2rad;
}

void
moment(const dVector& x, double& mean, double& sdev)
{
    double sumsin = 0;
    double sumcos = 0;

    for (int i = 0; i < x.size(); ++i) {
        double theta = x(i)*deg2rad;
        sumsin += sin(theta);
        sumcos += cos(theta);
    }

    mean = atan2(sumsin, sumcos)/deg2rad;
    double R = sqrt(sumsin*sumsin + sumcos*sumcos)/x.size();
    sdev = pow(-2.0*log(R), 0.5)/deg2rad;
}

dVector
moving_average(const dVector& angles, int window)
{
    DASH_PRECONDITION(window%2 != 0);
    DASH_PRECONDITION(angles.size() > window);

    const int offset = (window-1)/2;
    const int npts = angles.size();
    dVector avg(npts);

    // calculate circular means
    for (int i = 0; i < npts-window+1; ++i) {
        avg(i+offset) = mean(angles.segment(i, window));
    }

    // use original angles at start and end of sequence
    for (int i = 0; i < offset; ++i) {
        avg(i) = angles(i);
        avg(npts-i-1) = angles(npts-i-1);
    }

    return avg;
}

double
distance(const std::vector<double>& x, const std::vector<double>& y)
{
    DASH_PRECONDITION(x.size() == y.size());

    double dist = 0;

    for (size_t i=0; i<x.size(); ++i) {
        double d = std::abs(x[i]-y[i]);
        double cd = (d<=180) ? d : 360-d;
        dist += cd*cd;
    }

    return sqrt(dist);
}

// circular similarity between 0 and 1
double
similarity(const std::vector<double>& x, const std::vector<double>& y)
{
    return 1.0 - distance(x,y)/sqrt(x.size())/180;
}

// cosine similarity between -1 and 1
double
cosine_similarity(const std::vector<double>& x, const std::vector<double>& y)
{
    DASH_PRECONDITION(x.size() == y.size());

    double xdoty = 0;
    double xnorm = 0;
    double ynorm = 0;

    for (size_t i=0; i<x.size(); i++) {
        xdoty += x[i]*y[i];
        xnorm += x[i]*x[i];
        ynorm += y[i]*y[i];
    }

    return xdoty/sqrt(xnorm)/sqrt(ynorm);
}

} // namespace circular
