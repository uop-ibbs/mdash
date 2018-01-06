//  $Id: viewer_options.h 130 2017-11-28 14:41:54Z dw $
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

#ifndef DASH_VIEWER_OPTIONS_H
#define DASH_VIEWER_OPTIONS_H

// torsion histogram panel
const int thp_rows_default = 2;
const int thp_cols_default = 2;

// principal components analysis
const int pca_dim_default = 3;
const int pca_pcx_default = 0;
const int pca_pcy_default = 1;
const int pca_pcz_default = 2;

struct ViewerOptions
{
    int thp_rows;
    int thp_cols;

    int pca_dim;
    int pca_pcx;
    int pca_pcy;
    int pca_pcz;

    ViewerOptions();
};

#endif // DASH_VIEWER_OPTIONS_H
