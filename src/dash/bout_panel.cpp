//  $Id: bout_panel.cpp 69 2015-11-04 14:43:17Z dw $
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

#include "dash/bout_panel.h"

#include <wx/sizer.h>

BoutPanel::BoutPanel(const iMatrix& bouts, int timestep, wxWindow* parent)
    : BoutPanelFBUI(parent), bouts_(bouts), timestep_(timestep)
{
    // setup grid
    grid->AppendRows(bouts_.rows());
    grid->AppendCols(bouts_.cols());
    grid->SetMargins(0, 0);
    grid->EnableEditing(false);
    grid->DisableDragGridSize();
    grid->DisableDragRowSize();
    grid->DisableDragColSize();
    grid->SetColLabelAlignment(wxALIGN_CENTRE, wxALIGN_CENTRE);
    grid->SetRowLabelAlignment(wxALIGN_CENTRE, wxALIGN_CENTRE);
    grid->SetDefaultCellAlignment(wxALIGN_RIGHT, wxALIGN_CENTRE);

    // column labels
    for (int i=0; i<bouts_.cols(); ++i) {
        grid->SetColLabelValue(i, wxString::Format("Bout %d", i+1));
    }

    // row labels
    for (int i=0; i<bouts_.rows(); ++i) {
        grid->SetRowLabelValue(i, wxString::Format("State %d", i+1));
    }

    // grid values
    draw_cells(0);
}

void
BoutPanel::draw_cells(int units)
{
    for (int i=0; i<bouts_.rows(); ++i) {
        for (int j=0; j<bouts_.cols(); ++j) {
            if (bouts_(i,j) > 0) {
                if (units == 0) {
                    // frames
                    grid->SetCellValue(i, j, wxString::Format("%d", static_cast<int>(bouts_(i,j))));
                } else {
                    // times
                    grid->SetCellValue(i, j, wxString::Format("%d", static_cast<int>(bouts_(i,j)*timestep_)));
                }
            }
        }
    }
}

void
BoutPanel::on_units_ctrl(wxCommandEvent& WXUNUSED(event))
{
    draw_cells(units_ctrl->GetSelection());
}
