//  $Id: torsion_state_panel.cpp 106 2017-05-09 08:45:16Z dw $
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

#include "dash/torsion_state_panel.h"
#include <iomanip>
#include <vector>
#include <wx/sizer.h>

TorsionStatePanel::TorsionStatePanel(const std::vector<TorsionData*>& tdata, wxWindow* parent)
    : wxPanel(parent), torsion_data(tdata)
{
    const int nangles = torsion_data.size();
    int nstates = 0;

    for (int i=0; i<nangles; ++i) {
        const std::vector<int>& codes = torsion_data[i]->codes();

        for (size_t j=0; j<codes.size(); ++j) {
            if (codes[j] > nstates) ++nstates;
        }
    }

    grid = new wxGrid(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0);

    // setup grid
    int subcols = 2;
    grid->CreateGrid(nangles+2, subcols*nstates+1);
    grid->SetMargins(0, 0);
    grid->EnableEditing(false);
    grid->DisableDragGridSize();
    grid->DisableDragRowSize();
    grid->DisableDragColSize();
    grid->SetColLabelAlignment(wxALIGN_CENTRE, wxALIGN_CENTRE);
    grid->SetRowLabelAlignment(wxALIGN_CENTRE, wxALIGN_CENTRE);
    grid->SetDefaultCellAlignment(wxALIGN_RIGHT, wxALIGN_CENTRE);

    // add column labels manually in first two rows
    grid->HideColLabels();

    for (int i=0; i<nstates; ++i) {
        grid->SetCellSize(0, subcols*i, 1, subcols);
        grid->SetCellValue(0, subcols*i, wxString::Format("State %d", i+1));
        grid->SetCellValue(1, subcols*i, "Interval");
        grid->SetCellValue(1, subcols*i+1, "Maximum");
    }

    grid->SetCellValue(0, subcols*nstates, "Reassigned");

    wxGridCellAttr* attr = new wxGridCellAttr(grid->GetLabelTextColour(), grid->GetLabelBackgroundColour(), grid->GetLabelFont(), wxALIGN_CENTRE, wxALIGN_CENTRE);
    grid->SetRowAttr(0, attr);
    grid->SetRowAttr(1, attr->Clone());

    // row labels
    grid->SetRowLabelValue(0, "");
    grid->SetRowLabelValue(1, "");

    for (int i=0; i<nangles; ++i) {
        grid->SetRowLabelValue(i+2, wxString::Format("Angle %d", i+1));
    }

    // grid values
    for (int i=0; i<nangles; ++i) {
        const std::vector<double>& maxima = torsion_data[i]->maxima();
        const std::vector<double>& cuts = torsion_data[i]->cuts();
        const std::vector<int>& codes = torsion_data[i]->codes();

        for (int j=0; j<nstates; ++j) {
            std::ostringstream os;

            if (!torsion_data[i]->circular()) {
                os << std::fixed << std::setprecision(2);
            }

            for (std::vector<double>::size_type k=0; k<cuts.size()-1; ++k) {
                if (codes[k] == j+1) {
                    os << "[" << cuts[k] << ", " << cuts[k+1] << ") ";
                    wxString max_string = (torsion_data[i]->circular()) ? wxString::Format("%.0f ", maxima[j]) : wxString::Format("%.2f ", maxima[j]);
                    grid->SetCellValue(i+2, subcols*j+1, max_string);
                }
            }

            grid->SetCellValue(i+2, subcols*j, os.str());
        }

        grid->SetCellValue(i+2, subcols*nstates,
                           wxString::Format("%d (%.2f%%) ", torsion_data[i]->reassigned(),
                                            (100.0*torsion_data[i]->reassigned())/torsion_data[i]->frames()));
    }

    grid->AutoSize();

    wxBoxSizer* bSizer;
    bSizer = new wxBoxSizer(wxVERTICAL);
    bSizer->Add(grid, 0, wxALL, 5);
    this->SetSizer(bSizer);
    this->Layout();
}
