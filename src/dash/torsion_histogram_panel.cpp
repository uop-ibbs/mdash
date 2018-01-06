//  $Id: torsion_histogram_panel.cpp 114 2017-09-20 16:10:59Z dw $
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

#include "dash/torsion_histogram_panel.h"
#include <vector>
#include <numeric>

TorsionHistogramPanel::TorsionHistogramPanel(const std::vector<TorsionData*>& td, int angles, int rows, int cols, wxWindow* parent)
    : TiledPagerPanel(angles, rows, cols, parent), torsion_data(td)
{
    draw_page();
}

TorsionHistogramPanel::~TorsionHistogramPanel()
{
    clear_page();
}

void
TorsionHistogramPanel::clear_page()
{
    for (size_t i=0; i<graphs.size(); i++) {
        grid_sizer->Clear(true); // delete graphs
    }

    graphs.clear();
}

void
TorsionHistogramPanel::draw_page()
{
    int offset = (page-1)*get_rows()*get_cols();

    for (int i=0; i<get_rows(); i++) {
        for (int j=0; j<get_cols(); j++) {
            int idx = i*get_cols()+j+offset;

            if (idx < get_tiles()) {
                // add an extra bin so that the graphs display bars at both -180 and 180
                // and store as a double array for wxfreechart
                const std::vector<int>& td_freq = torsion_data[idx]->freq();
                const int nbins = td_freq.size();
                std::vector<double> freq, bins;
                freq.reserve(nbins+1);
                bins.reserve(nbins+1);

                for (int i=0; i<nbins; ++i) {
                    bins.push_back(torsion_data[idx]->bin_min(i));
                    freq.push_back(td_freq[i]);
                }

                // calculate upper bounds for axes
                int nb = 0;
                const double maxval = *std::max_element(freq.begin(), freq.end());
                while (++nb*100 < maxval) {}
                double sum = std::accumulate(freq.begin(), freq.end(), 0);
                int max_value = 100*nb;
                int max_fraction = 10000*nb/sum;

                // add extra bin at +180 for angles
                if (torsion_data[idx]->circular()) {
                    bins.push_back(torsion_data[idx]->bin_min(nbins));
                    freq.push_back(freq[0]);
                }

                wxString title = wxString::Format("Torsion Angle %d", idx+1);
                Histogram* h = new Histogram(freq, bins, title, max_value, max_fraction,
                                             grid_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSIMPLE_BORDER);
                grid_sizer->Add(h, 1, wxEXPAND|wxALL, 5);
                graphs.push_back(h);
            }
        }
    }

    grid_sizer->Layout();
}
