//  $Id: similarity_panel.h 124 2017-10-23 13:55:21Z dw $
//
//  Copyright (C) 2017 School of Pharmacy and Biomedivcal Sciences, University of Portsmouth.
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

#ifndef DASH_SIMILARITY_PANEL_H
#define DASH_SIMILARITY_PANEL_H

#include "dash/dash_fbgui.h"
#include "dash/eigen.h"

#include <wx/colour.h>

class SimilarityPanel : public SimilarityPanelFBUI
{
 public:
    SimilarityPanel(const dMatrix& circular_sim, const dMatrix& cosine_sim, wxWindow* parent);
    wxImage get_image();
    wxPanel* sim_panel() const { return circsim_panel; }

 private:
    enum sim_type_ {circsim, cosim};

    void draw_legend(sim_type_ type, wxGrid* grid);
    void draw_grid(sim_type_ type, const dMatrix& sim, wxGrid* grid);
    wxColour get_colour(sim_type_ type, double sim);
};

#endif // DASH_SIMILARITY_PANEL_H
