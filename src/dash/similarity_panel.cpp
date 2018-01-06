//  $Id: similarity_panel.cpp 124 2017-10-23 13:55:21Z dw $
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

#include "dash/similarity_panel.h"
#include "dash/eigen.h"

#include <wx/dcclient.h>
#include <wx/dcmemory.h>

SimilarityPanel::SimilarityPanel(const dMatrix& circular_sim, const dMatrix& cosine_sim, wxWindow* parent) :
    SimilarityPanelFBUI(parent)
{
    draw_legend(circsim, circsim_legend);
    draw_legend(cosim, cosim_legend);
    draw_grid(circsim, circular_sim, circsim_grid);
    draw_grid(cosim, cosine_sim, cosim_grid);
}

void
SimilarityPanel::draw_legend(sim_type_ type, wxGrid* grid) {
    const int bins = 25;
    const int binsize = 20; //pixels

    grid->AppendRows(1);
    grid->AppendCols(bins);

    for (int i = 0; i < bins; ++i)
    {
        grid->SetColSize(i, binsize);
        double sim = (type == circsim) ? (i*1.0)/bins : -1.0 + (i*2.0)/bins;
        grid->SetCellBackgroundColour(0, i, get_colour(type, sim));
    }
}

void
SimilarityPanel::draw_grid(sim_type_ type, const dMatrix& sim, wxGrid* grid) {
    const int nrows = sim.rows();
    const int ncols = sim.cols();

    // setup grid
    grid->AppendRows(nrows);
    grid->AppendCols(ncols);
    grid->SetMargins(0, 0);

    // row labels
    for (int i=0; i<nrows; ++i) {
        grid->SetRowLabelValue(i, wxString::Format("State %d", i+1));
    }

    // column labels
    for (int i=0; i<ncols; ++i) {
        grid->SetColLabelValue(i, wxString::Format("State %d", i+1));
    }

    // grid values
    for (int i=0; i<nrows; ++i) {
        for (int j=0; j<ncols; ++j) {
            grid->SetCellValue(i, j, wxString::Format("%.2f", sim(i,j)));
            grid->SetCellBackgroundColour(i, j, get_colour(type, sim(i,j)));
        }
    }
}

wxColour
SimilarityPanel::get_colour(sim_type_ type, double sim)
{
    unsigned int r;
    unsigned int g;
    unsigned int b;

    if (type == circsim) {
        r = (sim < 0.5) ? 0 : (sim > 0.75) ? 255 : 255 * (sim - 0.5) * 4;
        g = (sim > 0.25 && sim < 0.75) ? 255 : (sim <= 0.25) ? 255 * sim * 4 : 255 * fabs(sim - 1) * 4;
        b = (sim > 0.5) ? 0 : (sim < 0.25) ? 255 : 255 * (0.75 - sim) * 4;
    } else {
        r = (sim < 0) ? 0 : (sim > 0.5) ? 255 : 255 * sim * 2;
        g = (sim > -0.5 && sim < 0.5) ? 255 : (sim <= -0.5) ? 255 * (sim + 1) * 2 : 255 * fabs(sim - 1) * 2;
        b = (sim > 0) ? 0 : (sim < -0.5) ? 255 : 255 * fabs(sim) * 2;
    }

    return wxColour(r, g, b);
}

wxImage
SimilarityPanel::get_image()
{
    wxWindow *panel = (notebook->GetSelection() == circsim) ? circsim_panel : cosim_panel;
    wxClientDC clientDC(panel);
    wxCoord width, height;
    clientDC.GetSize(&width, &height);
    wxBitmap screenshot(width, height, -1);
    wxMemoryDC memDC;
    memDC.SelectObject(screenshot);
    memDC.Blit( 0, 0, width, height, &clientDC, 0, 0);
    memDC.SelectObject(wxNullBitmap);

    return screenshot.ConvertToImage();
}
