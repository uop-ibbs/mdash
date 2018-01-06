//  $Id: trajectory_panel.h 115 2017-09-21 15:20:56Z dw $
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

#ifndef DASH_TRAJECTORY_PANEL_H
#define DASH_TRAJECTORY_PANEL_H

#include "dash/dash_fbgui.h"
#include "dash/state_trajectory.h"

#include <wx/wxfreechartdefs.h>
#include <wx/chartpanel.h>
#include <wx/chart.h>
#include <wx/axis/numberaxis.h>

class TrajectoryPanel : public TrajectoryPanelFBUI
{
 public:
    TrajectoryPanel(const StateTrajectory& traj, wxWindow* parent);

    wxChartPanel* get_chart_panel() const { return chart_panel_; }

 protected:
    void on_zoom(wxScrollEvent& event);

 private:
    wxChartPanel* chart_panel_;
    StateTrajectory traj_;
    NumberAxis* bottomAxis_;

    Chart* Create();
    void calc_axis_data(int n, int& ticks, int& maxval);
};

#endif // DASH_TRAJECTORY_PANEL_H
