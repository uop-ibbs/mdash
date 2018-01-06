//  $Id: histogram.cpp 81 2016-02-12 17:12:47Z dw $
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

#include "dash/histogram.h"

#include <numeric>
#include <vector>

#include <wx/axis/categoryaxis.h>
#include <wx/bars/barplot.h>
#include <wx/category/categorysimpledataset.h>
#include <wx/xy/xyplot.h>
#include <wx/xy/xylinerenderer.h>
#include <wx/xy/xysimpledataset.h>
#include <wx/xy/xyhistorenderer.h>

Histogram::Histogram(std::vector<double>& f, std::vector<double>& b, const wxString& t, int mv, int mf,
                     wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
    : wxPanel(parent, id, pos, size, style), title(t), freq(f), bins(b), max_value(mv), max_fraction(mf)
{
    chart_panel = new wxChartPanel(this, wxID_ANY, Create(), wxDefaultPosition, this->GetSize());
    wxBoxSizer* bSizer;
    bSizer = new wxBoxSizer(wxVERTICAL);
    bSizer->Add(chart_panel, 1, wxEXPAND, 0);
    this->SetSizer(bSizer);
    this->Layout();
}

Chart*
Histogram::Create()
{
    // create data
    const int nbins = bins.size();

    std::vector<double> data(2*nbins);

    for (int i=0; i<nbins; ++i) {
        data[2*i] = bins[i];
        data[2*i+1] = freq[i];
    }

    // create plot
    XYPlot *plot = new XYPlot();

    // create dataset
    XYSimpleDataset *dataset = new XYSimpleDataset();
    dataset->AddSerie(static_cast<double*>(data.data()), nbins);

    // create histogram renderer
    XYHistoRenderer *histoRenderer = new XYHistoRenderer(5, true);
    histoRenderer->SetBarArea(0, new FillAreaDraw(*wxBLACK_PEN, *wxRED_BRUSH));
    dataset->SetRenderer(histoRenderer);

    // add dataset to plot
    plot->AddDataset(dataset);

    // left axis
    NumberAxis *leftAxis = new NumberAxis(AXIS_LEFT);
    leftAxis->SetMargins(0, 0);
    leftAxis->SetFixedBounds(0, max_value);
    leftAxis->SetTitle("Frames");
    leftAxis->IntegerValues();
    plot->AddAxis(leftAxis);

    // right axis
    NumberAxis *rightAxis = new NumberAxis(AXIS_RIGHT);
    rightAxis->SetMargins(0, 0);
    rightAxis->SetFixedBounds(0, max_fraction);
    rightAxis->SetTitle("%Frames");
    rightAxis->SetTitleLocation(wxRIGHT);
    plot->AddAxis(rightAxis);

    // bottom axis
    NumberAxis *bottomAxis = new NumberAxis(AXIS_BOTTOM);
    bottomAxis->SetMargins(15, 15);
    bottomAxis->SetLabelCount(7);
    bottomAxis->IntegerValues();
    plot->AddAxis(bottomAxis);

    // link axes to plot
    plot->LinkDataHorizontalAxis(0, 0);
    plot->LinkDataVerticalAxis(0, 0);

    // create chart
    return new Chart(plot, title);
}
