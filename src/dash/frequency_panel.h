//  $Id: frequency_panel.h 55 2015-07-23 15:12:29Z dw $
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

#ifndef DASH_FREQUENCY_PANEL_H
#define DASH_FREQUENCY_PANEL_H

#include "dash/eigen.h"

#include <wx/chart.h>
#include <wx/chartpanel.h>
#include <wx/panel.h>
#include <wx/wxfreechartdefs.h>

class FrequencyPanel : public wxPanel
{
 public:
    FrequencyPanel(const iMatrix& bouts, wxWindow* parent);

    wxChartPanel* get_chart_panel() const { return chart_panel; }

 private:
    wxChartPanel* chart_panel;
    const iMatrix& bouts;

    Chart* Create();
};

#endif // DASH_FREQUENCY_PANEL_H
