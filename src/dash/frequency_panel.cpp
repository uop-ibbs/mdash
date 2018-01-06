//  $Id: frequency_panel.cpp 55 2015-07-23 15:12:29Z dw $
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

#include "dash/frequency_panel.h"

#include <wx/axis/categoryaxis.h>
#include <wx/bars/barplot.h>
#include <wx/category/categorysimpledataset.h>
#include <wx/chartpanel.h>

FrequencyPanel::FrequencyPanel(const iMatrix& bouts, wxWindow* parent) : wxPanel(parent), bouts(bouts)
{
    chart_panel = new wxChartPanel(this, wxID_ANY, Create(), wxDefaultPosition, this->GetSize());
    wxBoxSizer* bSizer;
    bSizer = new wxBoxSizer(wxVERTICAL);
    bSizer->Add(chart_panel, 1, wxEXPAND | wxALL, 5);
    this->SetSizer(bSizer);
    this->Layout();
}

Chart*
FrequencyPanel::Create()
{
    const int nstates = bouts.rows();
    const int nbouts = bouts.cols(); // max #bouts in a single state

    // find maximum #frames in a single state and total #frames
    int max_frames = 0;
    int total_frames = 0;

    for (int i=0; i<nstates; ++i) {
        int state_frames = 0;

        for (int j=0; j<nbouts; ++j) {
            state_frames += bouts(i,j);
        }

        if (state_frames > max_frames) max_frames = state_frames;
        total_frames += state_frames;
    }

    // create state names for x-axis labels
    wxString *names = new wxString[nstates];

    for (int i=0; i<nstates; ++i) {
        names[i] = wxString::Format("%d", i+1);
    }

    // create dataset
    CategorySimpleDataset *dataset = new CategorySimpleDataset(names, nstates);
    delete[] names;

    for (int i=0; i<nbouts; ++i) {
        double *plotvals = new double[nstates];

        for (int j=0; j<nstates; ++j) {
            plotvals[j] = bouts(j,i);
        }

        dataset->AddSerie("", plotvals, nstates);
        delete[] plotvals;
    }

    // setup plot
    BarType *barType = new StackedBarType(10, 0);
    dataset->SetRenderer(new BarRenderer(barType));
    BarPlot *plot = new BarPlot();

    // left axis
    NumberAxis *leftAxis = new NumberAxis(AXIS_LEFT);
    leftAxis->SetMargins(0, 0);
    int nb = 0;
    while (++nb*500 < max_frames) {}
    leftAxis->SetFixedBounds(0, 500*nb);
    leftAxis->SetTitle("Frames");
    leftAxis->IntegerValues();
    plot->AddAxis(leftAxis);

    // right axis
    NumberAxis *rightAxis = new NumberAxis(AXIS_RIGHT);
    rightAxis->SetMargins(0, 0);
    rightAxis->SetFixedBounds(0, 50000*nb/total_frames);
    rightAxis->SetTitle("%Frames");
    rightAxis->SetTitleLocation(wxRIGHT);
    plot->AddAxis(rightAxis);

    // bottom axis
    CategoryAxis *bottomAxis = new CategoryAxis(AXIS_BOTTOM);
    bottomAxis->SetMargins(10, 10);
    bottomAxis->SetTitle("State");
    plot->AddAxis(bottomAxis);

    // add dataset and axes to plot
    plot->AddDataset(dataset);
    plot->LinkDataHorizontalAxis(0, 0);
    plot->LinkDataVerticalAxis(0, 0);

    // create chart
    return new Chart(plot, "Dash State Frequencies");
}
