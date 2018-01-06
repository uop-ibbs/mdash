//  $Id: dash_state_panel.cpp 106 2017-05-09 08:45:16Z dw $
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

#include "dash/dash_state_panel.h"
#include <wx/sizer.h>

DashStatePanel::DashStatePanel(const state_map& states, int nframes, wxWindow* parent) : wxPanel(parent)
{
    const int nstates = states.size();
    const int nangles = states.begin()->second.mean.size();

    grid = new wxGrid(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0);

    // setup grid
    grid->CreateGrid(nstates, nangles+4);
    grid->SetMargins(0, 0);
    grid->EnableEditing(false);
    grid->DisableDragGridSize();
    grid->DisableDragRowSize();
    grid->DisableDragColSize();
    grid->SetColLabelAlignment(wxALIGN_CENTRE, wxALIGN_CENTRE);
    grid->SetRowLabelAlignment(wxALIGN_CENTRE, wxALIGN_CENTRE);
    grid->SetDefaultCellAlignment(wxALIGN_RIGHT, wxALIGN_CENTRE);

    // column labels
    for (int i=0; i<nangles; ++i) {
        grid->SetColLabelValue(i, wxString::Format("Angle %d", i+1));
    }

    grid->SetColLabelValue(nangles, "Frames");
    grid->SetColLabelValue(nangles+1, "%Frames");
    grid->SetColLabelValue(nangles+2, "Rep. Frame");
    grid->SetColLabelValue(nangles+3, "RMSD");

    // row labels
    for (int i=0; i<nstates; ++i) {
        grid->SetRowLabelValue(i, wxString::Format("State %d", i+1));
    }

    // grid values
    int s = 0;
    for (state_map::const_iterator i=states.begin(); i!=states.end(); ++i, ++s) {
        const StateData& sdata = i->second;

        for (int j=0; j<nangles; ++j) {
            grid->SetCellValue(s, j, wxString::Format("%.2f", sdata.mean[j]));
        }

        grid->SetCellValue(s, nangles, wxString::Format("%d", sdata.freq));
        grid->SetCellValue(s, nangles+1, wxString::Format("%.2f", (100.0*sdata.freq)/nframes));
        grid->SetCellValue(s, nangles+2, wxString::Format("%d", sdata.frame));
        grid->SetCellValue(s, nangles+3, wxString::Format("%.2f", sdata.rmsd));
    }

    grid->AutoSize();

    wxBoxSizer* bSizer = new wxBoxSizer(wxVERTICAL);
    bSizer->Add(grid, 0, wxALL, 5);
    this->SetSizer(bSizer);
    this->Layout();
}
