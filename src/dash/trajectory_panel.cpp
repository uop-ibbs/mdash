//  $Id: trajectory_panel.cpp 115 2017-09-21 15:20:56Z dw $
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

#include "dash/trajectory_panel.h"
#include "dash/dash_exception.h"

#include <wx/xy/xyplot.h>
#include <wx/xy/xysimpledataset.h>
#include <wx/xy/xylinerenderer.h>

TrajectoryPanel::TrajectoryPanel(const StateTrajectory& traj, wxWindow* parent) : TrajectoryPanelFBUI(parent), traj_(traj)
{
    chart_panel_ = new wxChartPanel(main_panel, wxID_ANY, Create(), wxDefaultPosition, main_panel->GetSize());
    wxBoxSizer* bSizer = new wxBoxSizer(wxVERTICAL);
    bSizer->Add(chart_panel_, 1, wxEXPAND | wxALL, 5);
    main_panel->SetSizer(bSizer);
    this->Layout();
}

Chart*
TrajectoryPanel::Create()
{
    const int nstates = traj_.states.size();
    const int npts= 2*traj_.transitions+2;
    double *data = new double[2*npts];

    state_set_const_iter current;
    state_set_const_iter last;
    int count = 1;
    int frame = 0;
    int idx = -1;
    state_map::const_iterator pos = traj_.states.find(traj_.seq[0]);

    if (pos == traj_.states.end()) {
        delete[] data;
        DASH_RUNTIME_ERROR("find state failed");
    }

    data[++idx] = frame;
    data[++idx] = pos->second.index;

    for (size_t n=1; n<traj_.seq.size(); n++) {
        current = traj_.seq[n];
        last = traj_.seq[n-1];

        if (current == last) {
            ++count;
        } else {
            frame += count;
            data[++idx] = frame;
            data[++idx] = pos->second.index;
            pos = traj_.states.find(current);

            if (pos == traj_.states.end()) {
                delete[] data;
                DASH_RUNTIME_ERROR("find state failed");
            }

            data[++idx] = frame;
            data[++idx] = pos->second.index;
            count = 1;
        }
    }

    frame += count;
    data[++idx] = frame;
    data[++idx] = pos->second.index;

    // setup plot
    XYPlot *plot = new XYPlot();
    XYSimpleDataset *dataset = new XYSimpleDataset();
    dataset->AddSerie(data, npts);
    delete[] data;

    // set line renderer for dataset
    dataset->SetRenderer(new XYLineRenderer());

    // left axis
    NumberAxis *leftAxis = new NumberAxis(AXIS_LEFT);
    leftAxis->SetMargins(10, 10);
    leftAxis->SetTitle("State");
    leftAxis->IntegerValues();
    int ticks;
    int maxval;
    calc_axis_data(nstates, ticks, maxval);
    leftAxis->SetLabelCount(ticks);
    leftAxis->SetFixedBounds(1, maxval);
    plot->AddAxis(leftAxis);

    // bottom axis
    bottomAxis_ = new NumberAxis(AXIS_BOTTOM);
    bottomAxis_->SetMargins(10, 10);
    bottomAxis_->SetTitle("Frame");
    bottomAxis_->IntegerValues();
    plot->AddAxis(bottomAxis_);

    // add dataset and axes to plot
    plot->AddDataset(dataset);
    plot->LinkDataHorizontalAxis(0, 0);
    plot->LinkDataVerticalAxis(0, 0);

    // create chart
    Chart* chart = new Chart(plot, "Dash State Trajectory");
    chart->SetMargin(25);
    chart->SetScrolledAxis(bottomAxis_);
    return chart;
}

void
TrajectoryPanel::on_zoom(wxScrollEvent& WXUNUSED(event))
{
    const int frames = traj_.seq.size();

    if (slider->GetValue() > 0) {
        int width = (10 - frames/100.0)*slider->GetValue() + frames;
        chart_panel_->GetChart()->GetHorizScrolledAxis()->SetWindowWidth(width);
        chart_panel_->GetChart()->GetHorizScrolledAxis()->SetUseWindow(true);
        bottomAxis_->SetLabelCount(5*frames/width);
        bottomAxis_->UpdateBounds();
        chart_panel_->ChartScrollsChanged(chart_panel_->GetChart());
    } else {
        chart_panel_->GetChart()->GetHorizScrolledAxis()->SetUseWindow(false);
        bottomAxis_->SetLabelCount(5);
        bottomAxis_->UpdateBounds();
    }
}

void
TrajectoryPanel::calc_axis_data(int n, int& ticks, int& maxval)
{
    const int maxticks = 10;
    int p = -1;

    do {
        ++p;
        int step = std::pow(2, p);
        int range = n - 1;
        int mod = range % step;
        if (mod != 0) range = range + step - mod;
        ticks = 1 + range/step;
        maxval = range + 1;
    } while (ticks > maxticks);
}
