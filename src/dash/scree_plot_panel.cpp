//  $Id: scree_plot_panel.cpp 115 2017-09-21 15:20:56Z dw $
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

#include "dash/scree_plot_panel.h"

#include <wx/axis/categoryaxis.h>
#include <wx/bars/barplot.h>
#include <wx/category/categorysimpledataset.h>

ScreePlotPanel::ScreePlotPanel(const cmdlib::PCA* pca, wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
    : wxPanel(parent, id, pos, size, style), pca_(pca)
{
    chart_panel_ = new wxChartPanel(this, wxID_ANY, Create(), wxDefaultPosition, this->GetSize());
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(chart_panel_, 1, wxEXPAND | wxALL, 5);
    SetSizer(sizer);
    Layout();
}

Chart*
ScreePlotPanel::Create()
{
    // create dataset
    const int nbars = pca_->p();
    wxString *labels = new wxString[nbars];
    double *series1 = new double[nbars];
    double *series2 = new double[nbars];

    for (int i=0; i<nbars; ++i) {
        labels[i] = wxString::Format("%d", i+1);
        series1[i] = 100 * pca_->explained(i);
        series2[i] = 100 * (pca_->cumulative(i) - pca_->explained(i));
    }

    CategorySimpleDataset *dataset = new CategorySimpleDataset(labels, nbars);
    dataset->AddSerie("", series1, nbars);
    dataset->AddSerie("", series2, nbars);
    delete[] labels;
    delete[] series1;
    delete[] series2;

    // setup plot
    BarType *barType = new StackedBarType(20, 0);
    dataset->SetRenderer(new BarRenderer(barType));
    BarPlot *plot = new BarPlot();

    // left axis
    NumberAxis *leftAxis = new NumberAxis(AXIS_LEFT);
    leftAxis->SetMargins(0, 0);
    leftAxis->IntegerValues();
    leftAxis->SetTitle("% Variance Explained");
    plot->AddAxis(leftAxis);

    // right axis
    NumberAxis *rightAxis = new NumberAxis(AXIS_RIGHT);
    rightAxis->SetMargins(0, 0);
    rightAxis->SetFixedBounds(0, pca_->var().sum());
    rightAxis->SetTitle("Variance");
    rightAxis->SetTitleLocation(wxRIGHT);
    plot->AddAxis(rightAxis);

    // bottom axis
    CategoryAxis *bottomAxis = new CategoryAxis(AXIS_BOTTOM);
    bottomAxis->SetMargins(10, 10);
    bottomAxis->SetTitle("Component");
    plot->AddAxis(bottomAxis);

    // add dataset and axes to plot
    plot->AddDataset(dataset);
    plot->LinkDataHorizontalAxis(0, 0);
    plot->LinkDataVerticalAxis(0, 0);

    // create chart
    return new Chart(plot, "Scree Plot");
}
