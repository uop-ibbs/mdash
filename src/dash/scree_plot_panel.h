//  $Id: scree_plot_panel.h 115 2017-09-21 15:20:56Z dw $
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

#ifndef DASH_SCREE_PLOT_PANEL_H
#define DASH_SCREE_PLOT_PANEL_H

#include "dash/eigen.h"

#include "cmdlib/pca.h"

#include <wx/chart.h>
#include <wx/chartpanel.h>
#include <wx/panel.h>

class ScreePlotPanel : public wxPanel
{
 public:
    ScreePlotPanel(const cmdlib::PCA* pca, wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0);

    wxChartPanel* get_chart_panel() const { return chart_panel_; }

 private:
    wxChartPanel* chart_panel_;
    const cmdlib::PCA* pca_;

    Chart* Create();
};

#endif // DASH_SCREE_PLOT_PANEL_H
