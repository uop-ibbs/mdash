//  $Id: torsion_histogram_panel.h 114 2017-09-20 16:10:59Z dw $
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

#ifndef DASH_TORSION_HISTOGRAM_PANEL_H
#define DASH_TORSION_HISTOGRAM_PANEL_H

#include "dash/dash_fbgui.h"
#include "dash/histogram.h"
#include "dash/tiled_pager_panel.h"
#include "dash/torsion_data.h"

#include <vector>

class TorsionHistogramPanel : public TiledPagerPanel
{
 public:
    TorsionHistogramPanel(const std::vector<TorsionData*>& torsion_data, int angles, int rows, int cols, wxWindow* parent);
    ~TorsionHistogramPanel();

    wxPanel* get_grid_panel() const { return grid_panel; }

 private:
    std::vector<TorsionData*> torsion_data;
    std::vector<Histogram*> graphs;

    void draw_page();
    void clear_page();
};

#endif // DASH_TORSION_HISTOGRAM_PANEL_H
