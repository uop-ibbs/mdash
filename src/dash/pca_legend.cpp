//  $Id: pca_legend.cpp 80 2016-02-10 12:26:55Z dw $
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

#include "dash/pca_legend.h"
#include <vector>
#include <wx/grid.h>
#include <wx/settings.h>
#include <wx/sizer.h>
#include <wx/stattext.h>

PCALegend::PCALegend(int nstates, const std::vector<unsigned char>& colours, wxWindow* parent,
                     wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
    : wxPanel(parent, id, pos, size, style)
{
    SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOWFRAME));

    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

    wxStaticText* title = new wxStaticText(this, wxID_ANY, wxT("States"));
    title->Wrap(-1);
    sizer->Add(title, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5);

    wxGrid* grid = new wxGrid(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxVSCROLL);

    // grid properties
    grid->CreateGrid(0, 0);
    grid->EnableEditing(false);
    grid->EnableGridLines(false);
    grid->EnableDragGridSize(false);
    grid->SetMargins(20, 0);

    // column properties
    grid->EnableDragColMove(false);
    grid->EnableDragColSize(false);
    grid->SetColLabelSize(0);
    grid->SetColLabelAlignment(wxALIGN_CENTRE, wxALIGN_CENTRE);

    // row properties
    grid->EnableDragRowSize(false);
    grid->SetRowLabelSize(0);
    grid->SetRowLabelAlignment(wxALIGN_CENTRE, wxALIGN_CENTRE);

    // cell properties
    grid->SetDefaultCellBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOWFRAME));
    grid->SetDefaultCellAlignment(wxALIGN_LEFT, wxALIGN_TOP);

    // contents
    grid->AppendRows(nstates);
    grid->AppendCols(2);
    grid->SetDefaultColSize(25);
    grid->SetDefaultRowSize(25);
    grid->SetDefaultCellAlignment(wxALIGN_LEFT, wxALIGN_CENTRE);

    for (int i=0; i<nstates; ++i) {
        grid->SetCellBackgroundColour(i, 0, wxColour(colours[3*i], colours[3*i+1], colours[3*i+2]));
        grid->SetCellValue(i, 1, wxString::Format("%d", i+1));
    }

    sizer->Add(grid, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5);
    SetSizer(sizer);
    Layout();
}
