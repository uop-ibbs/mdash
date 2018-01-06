//  $Id: dash_sim.cpp 116 2017-09-21 16:19:22Z dw $
//
//  Copyright (C) 2017 School of Pharmacy and Biomedical Sciences, University of Portsmouth.
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

#include "dash/dash_sim.h"
#include "dash/circular.h"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <map>

namespace dashsim
{
const std::vector<std::string> state_type = {"Combined", "Smoothed", "Dash", "Replica Exchange"};

void
dash_sim(const std::string& file1, const std::string& file2)
{
    state_angle_map angles1, angles2;
    matrix2d sim;

    read_dash_output_file(file1, angles1);
    read_dash_output_file(file2, angles2);

    for (auto s : state_type) {
        // check both files contain this state type
        if (angles1.find(s) == angles1.end() || angles2.find(s) == angles2.end()) continue;

        if (angles1[s][0].size() != angles2[s][0].size()) {
            std::cerr << "Can't compare states with different numbers of angles\n";
            return;
        }

        const int states1 = angles1[s].size();
        const int states2 = angles2[s].size();

        // circular similarity
        for (int i=0; i<states1; ++i) {
            std::vector<double> v(states2);

            for (int j=0; j<states2; ++j) {
                v[j] = circular::similarity(angles1[s][i], angles2[s][j]);
            }

            sim.push_back(v);
        }

        std::string label = s + " State Circular";
        write_similarity_matrix(sim, label, file1, file2);
        sim.clear();

        // cosine similarity
        for (int i=0; i<states1; ++i) {
            std::vector<double> v(states2);

            for (int j=0; j<states2; ++j) {
                v[j] = circular::cosine_similarity(angles1[s][i], angles2[s][j]);
            }

            sim.push_back(v);
        }

        label = s + " State Cosine";
        write_similarity_matrix(sim, label, file1, file2);
        sim.clear();
    }
}

void
read_dash_output_file(std::string file, state_angle_map& angles)
{
    std::ifstream ifs(file.c_str());

    if (!ifs) {
        std::cerr << "failed to open file: " << file << '\n';
        exit(1);
    }

    std::cout << "reading file " << file << "... ";

    // tags used in different versions of output file
    const std::string angles_tag_1 = "torsion angles =";
    const std::string angles_tag_2 = "angles :";
    const std::string angles_tag_3 = "variables :";
    const std::string dash_tag_1 = "<DashStateMeanAngles>";
    const std::string dash_tag_2 = "[DASH_STATE_MEAN_ANGLES]";
    const std::string dash_tag_3 = "[DASH_STATE_MEANS]";
    const std::string smoothed_tag_1 = "[SMOOTHED_STATE_MEAN_ANGLES]";
    const std::string smoothed_tag_2 = "[SMOOTHED_STATE_MEANS]";
    const std::string combined_tag_1 = "[COMBINED_STATE_MEAN_ANGLES]";
    const std::string combined_tag_2 = "[COMBINED_STATE_MEANS]";
    const std::string repex_tag = "[REPLICA_EXCHANGE_STATE_MEAN_ANGLES]";

    std::string line;
    int num_angles = 0;

    while (getline(ifs, line)) {
        if ((line.compare(0, angles_tag_3.length(), angles_tag_3) == 0) ||
            (line.compare(0, angles_tag_2.length(), angles_tag_2) == 0)) {
            std::string tag, colon;
            std::istringstream is(line);
            is >> tag >> colon >> num_angles;
            std::cout << "found " << num_angles << " torsion angles\n";
        }

        if (line.compare(0, angles_tag_1.length(), angles_tag_1) == 0) {
            std::string tag1, tag2, equals;
            std::istringstream is(line);
            is >> tag1 >> tag2 >> equals >> num_angles;
            std::cout << "found " << num_angles << " torsion angles\n";
        }

        if (line.compare(0, combined_tag_2.length(), combined_tag_2) == 0) {
            std::cout << "reading COMBINED_STATE_MEANS block ... ";
            read_state_mean_angles(ifs, angles, "Combined", num_angles);
        }

        if (line.compare(0, combined_tag_1.length(), combined_tag_1) == 0) {
            std::cout << "reading COMBINED_STATE_MEAN_ANGLES block ... ";
            read_state_mean_angles(ifs, angles, "Combined", num_angles);
        }

        if (line.compare(0, smoothed_tag_2.length(), smoothed_tag_2) == 0) {
            std::cout << "reading SMOOTHED_STATE_MEANS block ... ";
            read_state_mean_angles(ifs, angles, "Smoothed", num_angles);
        }

        if (line.compare(0, smoothed_tag_1.length(), smoothed_tag_1) == 0) {
            std::cout << "reading SMOOTHED_STATE_MEAN_ANGLES block ... ";
            read_state_mean_angles(ifs, angles, "Smoothed", num_angles);
        }

        if (line.compare(0, dash_tag_3.length(), dash_tag_3) == 0) {
            std::cout << "reading DASH_STATE_MEANS block ... ";
            read_state_mean_angles(ifs, angles, "Dash", num_angles);
        }

        if (line.compare(0, dash_tag_2.length(), dash_tag_2) == 0) {
            std::cout << "reading DASH_STATE_MEAN_ANGLES block ... ";
            read_state_mean_angles(ifs, angles, "Dash", num_angles);
        }

        if (line.compare(0, dash_tag_1.length(), dash_tag_1) == 0) {
            std::cout << "reading DashStateMeanAngles block ... ";
            read_state_mean_angles(ifs, angles, "Dash", num_angles);
        }

        if (line.compare(0, repex_tag.length(), repex_tag) == 0) {
            std::cout << "reading REPLICA_EXCHANGE_STATE_MEAN_ANGLES block ...";
            read_state_mean_angles(ifs, angles, "Replica Exchange", num_angles);
        }
    }

    std::cout << '\n';
}

void
read_state_mean_angles(std::istream& is, state_angle_map& angles, const std::string& state_type, int num_angles)
{
    std::string line;
    const std::string end_tag = "</";

    while (getline(is, line)) {
        // old format block has closing tag; new format block ends with blank line
        if (line.empty()) break;
        if (line.compare(0, end_tag.length(), end_tag) == 0) break;

        std::istringstream is(line);
        std::vector<double> mean_angles;
        std::string state_tag;
        double x;

        is >> state_tag;

        // old format is "state [n]"; new format is "[n]"
        if (state_tag == "state") is >> state_tag;

        for (int i=0; i<num_angles; ++i) {
            is >> x;
            mean_angles.push_back(x);
        }

        angles[state_type].push_back(mean_angles);
    }

    std::cout << "found " << angles[state_type].size() << " states\n";
}

void
write_similarity_matrix(const matrix2d& sim, const std::string& label, const std::string& file1, const std::string& file2)
{
    const size_t states1 = sim.size();
    const size_t states2 = sim[0].size();

    std::cout << std::fixed << std::setprecision(2);

    std::cout << label << " Similarity Matrix\n"
              << "A = " << file1 << " states\n"
              << "B = " << file2 << " states\n\n";

    std::cout << std::left;
    std::cout << std::setw(9) << ' ';

    for (size_t j=0; j<states2; ++j) {
        std::cout << "B" << std::setw(7) << j+1;
    }

    std::cout << '\n';

    for (size_t i=0; i<states1; ++i) {
        std::cout << std::left;
        std::cout << "A" << std::setw(7) << i+1;
        std::cout << std::right;
        std::cout << std::setw(5) << sim[i][0];

        for (size_t j=1; j<states2; ++j) {
            std::cout << std::setw(8) << sim[i][j];
        }

        std::cout << '\n';
    }

    std::cout << '\n';
}

} // dashsim
