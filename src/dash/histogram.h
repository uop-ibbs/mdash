//  $Id: histogram.h 68 2015-10-30 17:13:59Z dw $
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

#ifndef DASH_HISTOGRAM_H
#define DASH_HISTOGRAM_H

#include "dash/eigen.h"

#include <vector>

#include <wx/chartpanel.h>
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/wxfreechartdefs.h>

class Histogram : public wxPanel
{
 public:
    Histogram(std::vector<double>& freq, std::vector<double>& bins, const wxString& title,
              int maxv, int maxf, wxWindow* parent, wxWindowID id = wxID_ANY,
              const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0);

    wxChartPanel* get_chart_panel() const { return chart_panel; }

 private:
    wxChartPanel* chart_panel;
    wxString title;
    std::vector<double> freq;
    std::vector<double> bins;
    int max_value;
    int max_fraction;

    Chart* Create();
};

#endif // DASH_HISTOGRAM_H
