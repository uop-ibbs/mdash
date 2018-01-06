//  $Id: dash_options.cpp 132 2017-12-19 15:01:25Z dw $
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

#include "dash/dash_options.h"

DashOptions::DashOptions()
{
    quiet = quiet_default;
    window = window_default;
    binsize = binsize_circular_default;
    runlen = runlen_default;
    fmax = fmax_default;
    smin = smin_circular_default;
    boutlen = boutlen_default;
    smooth = smooth_default;
    rough = rough_default;

    circular = circular_default;
    distances = distances_default;
    pca = pca_default;
    pca_autoscale = pca_autoscale_default;
    repex = repex_default;
    repex_fraction = repex_fraction_default;
    timestep = timestep_default;

    write_histogram = write_histogram_default;
    write_combined = write_combined_default;
    write_smoothed = write_smoothed_default;
    write_dash = write_dash_default;
    write_sequence = write_sequence_default;

    labelled_data_file = labelled_data_file_default;

    debug = debug_default;
    rev85 = rev85_default;

#ifndef NOAMBER
    snap = snap_default;
    keep_dash_in = keep_dash_in_default;
    keep_cpptraj = keep_cpptraj_default;
#endif
}

void
DashOptions::write(std::ostream& os) const {
    os << "[OPTIONS]\n"
       << "data     : "   << (circular?"angles":"distances")
       << "\ntimestep : " << timestep << " ps"
       << "\nwindow   : " << window
       << "\nbinsize  : " << binsize
       << "\nrunlen   : " << runlen
       << "\nfmax     : " << fmax
       << "\nsmin     : " << smin
       << "\nboutlen  : " << boutlen
       << "\nsmooth   : " << smooth
       << "\nrough    : " << rough;

    if (repex) {
       os << "\nrepex_fraction : " << repex_fraction;
    }

    os << "\n\n";
}
