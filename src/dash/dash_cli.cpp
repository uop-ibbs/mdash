//  $Id: dash_cli.cpp 130 2017-11-28 14:41:54Z dw $
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

#include "dash/dash_cli.h"
#include "dash/amber_trajectory_reader.h"
#include "dash/dash.h"
#include "dash/dash_exception.h"
#include "dash/external.h"
#include "dash/dash_options.h"
#include "dash/dash_sim.h"
#include "dash/trajectory.h"
#include "dash/version.h"

#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>

#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>

namespace po = boost::program_options;
namespace fs = boost::filesystem;

const std::string usage =
#ifndef NOGUI
    "Usage:\n"
    "  mdash\n"
    "      Launch the graphical interface\n\n"
    "  mdash [options] -i <input_file>  -o <output_file>\n"
    "      Run mdash from the command line with the specified options\n\n"
#else
    "Usage:\n"
    "  mdash [options] -i <input_file>  -o <output_file>\n"
    "      Run mdash from the command line with the specified options\n\n"
#endif
#ifndef NOAMBER
    "  mdash [options] -P <parameter_file> -T <trajectory_file> -o <output_file>\n"
    "      Run mdash from the command line on an Amber trajectory\n\n"
#endif
    "  mdash -S|--similarity <file1> <file2>\n"
    "      Calculate similarities between states in two mdash output files\n";

int
dash_cli(int argc, argv_t **argv)
{
    DashOptions opt;
    po::options_description visible("Options", 90);

    visible.add_options()
        ("help,h", "print help message")
        ("version,v", "print version number")
        ("quiet,q",  po::bool_switch(&opt.quiet), "run quietly with no progress messages")
        ("debug,d", po::bool_switch(&opt.debug), "write internal details to stderr")
        ("input,i", po::value<std::string>(&opt.infile), "input file")
        ("output,o", po::value<std::string>(&opt.outfile)->required(), "output file")
        ("window,w", po::value<int>(&opt.window)->default_value(window_default), "moving average window size (an odd integer)")
        ("binsize,b", po::value<float>(&opt.binsize)->default_value(binsize_circular_default), "bin size for single-variable histograms")
        ("runlen,u", po::value<int>(&opt.runlen)->default_value(runlen_default), "run length for single-variable maxima")
        ("fmax,f", po::value<float>(&opt.fmax)->default_value(fmax_default, fmax_default_string), "minimum value for single-variable maxima")
        ("smin,m", po::value<float>(&opt.smin)->default_value(smin_circular_default), "minimum distance between single-variable maxima")
        ("boutlen,l", po::value<int>(&opt.boutlen)->default_value(boutlen_default), "minimum bout length for single-variable state")
        ("smooth,s", po::value<int>(&opt.smooth)->default_value(smooth_default), "smoothing level")
        ("rough,r", po::value<int>(&opt.rough)->default_value(rough_default), "roughening level")
        ("timestep,t", po::value<int>(&opt.timestep)->default_value(timestep_default), "inter-frame timestep in picoseconds")
        ("distances", po::bool_switch(&opt.distances)->default_value(distances_default), "process distance data")
        ("pca,p", po::bool_switch(&opt.pca), "calculate principal components")
        ("pca-autoscale,a", po::value<bool>(&opt.pca_autoscale)->implicit_value("true"), "use autoscaled variables for pca")
        ("repex,x", po::bool_switch(&opt.repex), "process replica exchange trajectory")
        ("repex-fraction,y",  po::value<float>(&opt.repex_fraction)->default_value(repex_fraction_default, repex_fraction_default_string),
         "fraction of frames defining replica exchange states")
        ("write-histogram,H", po::bool_switch(&opt.write_histogram), "write torsion histograms")
        ("write-combined,C", po::bool_switch(&opt.write_combined), "write combined states and trajectory")
        ("write-smoothed,Z", po::bool_switch(&opt.write_smoothed), "write smoothed states and trajectory")
        ("write-sequence,F", po::bool_switch(&opt.write_sequence), "write full state sequence")
        ("write-labelled-data,L", po::value<std::string>(&opt.labelled_data_file), "write input data with state labels to file <arg>")
        ("similarity,S",po::value<std::vector<std::string>>()->default_value(std::vector<std::string>(2), "file1 file2")->multitoken(),
         "write similarities between states in two mdash output files to stdout")
        ;

#ifndef NOAMBER
    po::options_description amber("Amber Interface Options", 90);
    amber.add_options()
        ("amber-parm,P", po::value<std::string>(&opt.amber_parm), "AMBER parameter (topology) file")
        ("amber-traj,T", po::value<std::string>(&opt.amber_traj), "AMBER trajectory (netcdf) file(s)")
        ("residues,R", po::value<std::string>(&opt.amber_residues), "range of residues to analyse")
        ("dihedrals,D", po::value<std::string>(&opt.amber_dihedrals)->default_value("phi,psi"), "dihedral types to analyse")
        ("snap,N", po::bool_switch(&opt.snap), "write PDB files for frames representing DASH states")
        ("keep-mdash-input,k", po::bool_switch(&opt.keep_dash_in), "keep the mdash input file")
        ("keep-cpptraj,j", po::bool_switch(&opt.keep_cpptraj), "keep intermediate cpptraj files")
        ;
    visible.add(amber);
#endif

    po::options_description hidden("Expert Options", 90);

    hidden.add_options()
        ("rev85", po::bool_switch(&opt.rev85), "revision 85 behaviour (cuts not at local minima)")
        ;

    po::options_description all("All options", 90);
    all.add(visible).add(hidden);

    po::variables_map vm;

    try {
        po::store(po::parse_command_line(argc, argv, all), vm);
    } catch(po::error& e) {
        std::cerr << "Error: " << e.what() << "\n\n" << visible << '\n';
        return EXIT_FAILURE;
    }

    if (vm.count("help")) {
        std::cout << dash_version << '\n' << copyright << '\n' << usage << '\n' << visible << '\n';
        return EXIT_SUCCESS;
    }

    if (vm.count("help-expert")) {
        std::cout << usage << '\n' << visible << '\n' << hidden << '\n';
        return EXIT_SUCCESS;
    }

    if (vm.count("version")) {
        std::cout << dash_version << '\n';
        return EXIT_SUCCESS;
    }

    if (vm.count("similarity") && !vm["similarity"].defaulted()) {
        std::vector<std::string> simfiles = vm["similarity"].as< std::vector<std::string> >();

        if (simfiles.size() != 2) {
            std::cerr << "Error: -S option requires exactly two arguments\n";
            return EXIT_FAILURE;
        }

        try {
            dashsim::dash_sim(simfiles[0], simfiles[1]);
        } catch (const DashException& e) {
            std::cerr << e;
            return EXIT_FAILURE;
        }

        return EXIT_SUCCESS;
    }

    try {
        po::notify(vm);
    } catch(po::required_option& e) {
        std::cerr << "Error: " << e.what() << "\n\n" << usage << '\n' << visible << '\n';
        return EXIT_FAILURE;
    } catch(po::error& e) {
        std::cerr << "Error: " << e.what() << "\n\n" << visible << '\n';
        return EXIT_FAILURE;
    }

#ifdef NOAMBER
    if (!vm.count("input")) {
        std::cerr << "Error: an input file (-i) is required\n";
        return EXIT_FAILURE;
    }
#else
    if (vm.count("amber-parm") != vm.count("amber-traj")) {
        std::cerr << "Error: both an Amber parameter file (-P) and a trajectory file (-T) are required\n";
        return EXIT_FAILURE;
    }

    if (vm.count("input") == vm.count("amber-traj")) {
        std::cerr << "Error: an input file (-i) or an Amber trajectory (-T) is required\n";
        return EXIT_FAILURE;
    }
#endif // NOAMBER

    if (vm.count("window")) {
        if (opt.window%2 == 0) {
            std::cerr << "Error: window size must be odd\n";
            return EXIT_FAILURE;
        }
    }

    opt.circular = !opt.distances;

    if (opt.repex) {
        opt.write_smoothed = opt.write_sequence = opt.write_dash = false;
    } else {
        opt.write_dash = true;
    }

    if (opt.repex) {
        opt.write_smoothed = opt.write_dash = false;
        opt.pca = false;
    }

#ifndef NOAMBER
    if (vm.count("amber-traj")) {
        AmberOptions ambopt;
        AmberTrajectoryReader ambtrj;
        std::string ambmsg;

        ambopt.top_file = opt.amber_parm;
        ambopt.trj_file = opt.amber_traj;
        ambopt.residues = opt.amber_residues;

        ambopt.phi = (opt.amber_dihedrals.find("phi") != std::string::npos);
        ambopt.psi = (opt.amber_dihedrals.find("psi") != std::string::npos);
        ambopt.chi = (opt.amber_dihedrals.find("chi") != std::string::npos);
        ambopt.omega = (opt.amber_dihedrals.find("omega") != std::string::npos);

        if (!opt.quiet) {
            std::cerr << "Reading Amber trajectory ...\n";
        }

        int result = ambtrj.read(ambopt, ambmsg);

        if (opt.keep_cpptraj) {
            if (!external::save(ambtrj.cpptraj_in(), "cpptraj.in")) {
                std::cerr << "Warning: failed to save cpptraj input file" << '\n';
            }

            if (!external::save(ambtrj.cpptraj_out(), "cpptraj.out")) {
                std::cerr << "Warning: failed to save cpptraj output file"<< '\n';
            }

            if (!external::save(ambtrj.cpptraj_err(), "cpptraj.err")) {
                std::cerr << "Warning: failed to save cpptraj error file"<< '\n';
            }
        }

        if (!(result && ambmsg.empty())) {
            std::cerr << "Error: " << ambmsg << '\n';
            return EXIT_FAILURE;
        }

        opt.infile = "amberdash.in";
    }
#endif // NOAMBER

    // check input file exists and convert filename to absolute path
    fs::path inpath(opt.infile);

    if (fs::exists(inpath)) {
        opt.infile = fs::absolute(inpath).string();
    } else {
        std::cerr << "Error: input file " << opt.infile << " does not exist\n";
        return EXIT_FAILURE;
    }

    Trajectory trj;
    std::string trjmsg;

    if (!opt.quiet) {
        std::cerr << "Reading trajectory file " << opt.infile << " ...\n";
    }

    bool read_ok = trj.read(opt.infile, trjmsg);

#ifndef NOAMBER
    if (vm.count("amber-traj")) {
        trj.top_file = opt.amber_parm;
        trj.trj_file = opt.amber_traj;

        // remove dash input file generated from amber trajectory
        if (!opt.amber_parm.empty() && !opt.keep_dash_in) {
            boost::system::error_code ec;
            fs::remove(opt.infile, ec);

            if (ec) {
                std::cerr << "Warning: failed to remove mdash input file\nerror_code: "
                          << std::string(ec.category().name()) + ": " + ec.message();
            }
        }
    }
#endif // NOAMBER

    if (read_ok) {
        if (!opt.quiet) {
            std::cerr << "Found " << trj.vars << " variables, " << trj.frames << " frames\n";
        }
    } else {
        std::cerr << trjmsg << '\n';
        return EXIT_FAILURE;
    }

    // PCA requires more than one variable
    if (trj.vars < 2) {
        opt.pca = false;
    }

    // check the output file is writeable, before doing any work
    std::ofstream ofs(opt.outfile.c_str());

    if (!ofs) {
        std::cerr << "Error: failed to open output file " << opt.outfile << '\n';
        return EXIT_FAILURE;
    }

    if (!opt.quiet) {
        std::cerr << "Calculating states ...\n";
    }

    Dash dash(trj, opt);

    try {
        dash.run();
    } catch (const DashException& e) {
        std::cerr << e;
        return EXIT_FAILURE;
    }

    if (!opt.quiet) {
        std::cerr << "Calculation completed successfully in " << dash.total_time() << '\n';
    }

    ofs << dash_version << '\n';
    time_t now = time(0);

    if (now != static_cast<time_t>(-1)) {
        ofs << ctime(&now) << '\n';
    }

    try {
        dash.write(ofs);
    } catch (const DashException& e) {
        std::cerr << e;
        return EXIT_FAILURE;
    }

    ofs.close();

    if (opt.labelled_data_file.length() > 0) {
        if (!opt.quiet) {
            std::cerr << "Writing labelled data file: " << opt.labelled_data_file << " ...\n";
        }

        try {
            dash.write_labelled_data_file(opt.labelled_data_file);
        } catch (const DashException& e) {
            std::cerr << e;
            return EXIT_FAILURE;
        }
    }

#ifndef NOAMBER
    std::string snapmsg;

    if (opt.snap && !dash.write_snapshots(snapmsg)) {
        std::cerr << "Error: failed to write snapshots\n" << snapmsg;
    }
#endif

    return EXIT_SUCCESS;
}
