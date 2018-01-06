//  $Id: dash_options.h 113 2017-08-18 14:59:42Z dw $
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

#ifndef DASH_DASH_OPTIONS_H
#define DASH_DASH_OPTIONS_H

#include <ostream>
#include <string>

const bool quiet_default = false;
const int window_default = 11;
const float binsize_circular_default = 4.0f;
const float binsize_distance_default = 0.2f;
const int runlen_default = 3;
const float fmax_default = 2.4f;
const std::string fmax_default_string = "2.4";
const float smin_circular_default = 48.0f;
const float smin_distance_default = 1.0f;
const int boutlen_default = 20;
const int smooth_default = 40;
const int rough_default = 20;
const int timestep_default = 1;
const bool circular_default = true;
const bool distances_default = false;
const bool pca_default = false;
const bool pca_autoscale_default = true;
const bool repex_default = false;
const float repex_fraction_default = 0.01f;
const std::string repex_fraction_default_string = "0.01";
const bool write_dash_default = true;
const bool write_histogram_default = false;
const bool write_combined_default = false;
const bool write_smoothed_default = false;
const bool write_sequence_default = false;
const std::string labelled_data_file_default = "";
const bool debug_default = false;
const bool rev85_default = false;
const bool snap_default = false;
const bool keep_dash_in_default = false;
const bool keep_cpptraj_default = false;

struct DashOptions
{
    std::string infile;
    std::string outfile;
    std::string labelled_data_file;
    bool quiet;
    int window;
    float binsize;
    int runlen;
    float fmax;
    float smin;
    int boutlen;
    int smooth;
    int rough;
    int timestep;
    bool circular;
    bool distances;
    bool pca;
    bool pca_autoscale;
    bool repex;
    float repex_fraction;
    bool write_dash;
    bool write_histogram;
    bool write_combined;
    bool write_smoothed;
    bool write_sequence;
    bool debug;
    bool rev85;
    bool snap;

#ifndef NOAMBER
    std::string amber_parm;
    std::string amber_traj;
    std::string amber_residues;
    std::string amber_dihedrals;
    bool keep_dash_in;
    bool keep_cpptraj;
#endif

    DashOptions();
    void write(std::ostream& os) const;
};

#endif // DASH_DASH_OPTIONS_H
