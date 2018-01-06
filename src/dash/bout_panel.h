//  $Id: bout_panel.h 69 2015-11-04 14:43:17Z dw $
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

#ifndef DASH_BOUT_PANEL_H
#define DASH_BOUT_PANEL_H

#include "dash/dash_fbgui.h"
#include "dash/eigen.h"

#include <wx/panel.h>
#include <wx/grid.h>

class BoutPanel : public BoutPanelFBUI
{
 public:
    BoutPanel(const iMatrix& bouts, int timestep, wxWindow* parent);

 private:
    const iMatrix& bouts_;
    const int timestep_;

    void on_units_ctrl(wxCommandEvent&);
    void draw_cells(int units);
};

#endif // DASH_BOUT_PANEL_H
