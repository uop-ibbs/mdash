//  $Id: pca_legend.h 80 2016-02-10 12:26:55Z dw $
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

#ifndef DASH_PCA_LEGEND_H
#define DASH_PCA_LEGEND_H

#include <vector>
#include <wx/panel.h>

class PCALegend : public wxPanel
{
 public:
    PCALegend(int nstates, const std::vector<unsigned char>& colours, wxWindow* parent,
              wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0);
};

#endif // DASH_PCA_LEGEND_H
