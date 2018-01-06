//  $Id: pca_panel.h 81 2016-02-12 17:12:47Z dw $
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

#ifndef DASH_PCA_PANEL_H
#define DASH_PCA_PANEL_H

#include "dash/plot_canvas_2d.h"
#include "dash/plot_canvas_3d.h"
#include "dash/pca_legend.h"
#include "dash/state_trajectory.h"
#include "dash/viewer_options.h"

#include "cmdlib/pca.h"

#include <vector>

#include <wx/panel.h>
#include <wx/sizer.h>

class PCAPanel : public wxPanel
{
 public:
    PCAPanel(const cmdlib::Matrix& scores, const StateTrajectory& traj, const ViewerOptions& opt, wxWindow* parent,
             wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0);

    void reset();

 private:
    const cmdlib::Matrix& scores_;
    const StateTrajectory& traj_;
    const ViewerOptions& opt_;

    std::vector<GLfloat> coords_;
    std::vector<GLubyte> colours_;

    PlotCanvas2D *canvas2d_;
    PlotCanvas3D *canvas3d_;
    PCALegend *legend_;
    wxBoxSizer *sizer_;

    GLfloat range_;

    void init_legend();
    void init_colours();
    void init_range();
    void init_coords();
    void init_panel();
};

#endif // DASH_PCA_PANEL_H
