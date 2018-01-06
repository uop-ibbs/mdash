//  $Id: pca_panel.cpp 119 2017-10-09 10:58:45Z dw $
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

#include "dash/pca_panel.h"
#include "dash/palette.h"

#include <vector>

#include <wx/log.h>

PCAPanel::PCAPanel(const cmdlib::Matrix& scores, const StateTrajectory& traj, const ViewerOptions& opt, wxWindow* parent,
                   wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
    : wxPanel(parent, id, pos, size, style), scores_(scores), traj_(traj), opt_(opt)
{
    canvas2d_ = nullptr;
    canvas3d_ = nullptr;

    sizer_ = new wxBoxSizer(wxHORIZONTAL);
    SetSizer(sizer_);

    init_legend();
    init_colours();
    init_range();
    init_coords();
    init_panel();
}

void
PCAPanel::init_legend()
{
    const int nclrs = sizeof(PALETTE)/sizeof(PALETTE_ENTRY);
    const int nstates = traj_.states.size();

    std::vector<unsigned char> state_colours;
    state_colours.reserve(3*nstates);

    for (int i=0; i<nstates; ++i) {
        state_colours.push_back(PALETTE[i%nclrs].r);
        state_colours.push_back(PALETTE[i%nclrs].g);
        state_colours.push_back(PALETTE[i%nclrs].b);
    }

    legend_ = new PCALegend(nstates, state_colours, this);
}

void
PCAPanel::init_colours()
{
    std::vector<int> colour_idx_;
    colour_idx_.reserve(traj_.seq.size());

    for (auto state : traj_.seq) {
        state_map::const_iterator pos = traj_.states.find(state);
        colour_idx_.push_back(pos->second.index - 1);
    }

    const int nclrs = sizeof(PALETTE)/sizeof(PALETTE_ENTRY);
    const int npts = scores_.rows();
    colours_.reserve(3*npts);

    for (int i=0; i<npts; ++i) {
        PALETTE_ENTRY c = PALETTE[colour_idx_[i]%nclrs];
        colours_.push_back(c.r);
        colours_.push_back(c.g);
        colours_.push_back(c.b);
    }
}

void
PCAPanel::init_range()
{
    const int ix = 0, iy = 1;

    const double xmax = scores_.col(ix).maxCoeff();
    const double xmin = scores_.col(ix).minCoeff();
    const double ymax = scores_.col(iy).maxCoeff();
    const double ymin = scores_.col(iy).minCoeff();
    double vmax = (xmax>ymax) ? xmax : ymax;
    double vmin = (xmin<ymin) ? xmin : ymin;

    if (opt_.pca_dim == 3) {
        const int iz = 2;

        const double zmax = scores_.col(iz).maxCoeff();
        const double zmin = scores_.col(iz).minCoeff();
        vmax = (zmax > vmax) ? zmax : vmax;
        vmin = (zmin < vmin) ? zmin : vmin;
    }

    range_ = (vmax > -vmin) ? vmax : -vmin;
}

void
PCAPanel::init_coords()
{
    const int dim = opt_.pca_dim;
    const int idx[] = {opt_.pca_pcx, opt_.pca_pcy, opt_.pca_pcz};
    const int npts = scores_.rows();

    if (!coords_.empty()) {
        coords_.clear();
    }

    coords_.reserve(npts*dim);

    for (int i=0; i<npts; ++i) {
        for (int j=0; j<dim; ++j) {
            coords_.push_back(scores_(i,idx[j])/range_);
        }
    }
}

void
PCAPanel::init_panel()
{
    const int dim = opt_.pca_dim;
    sizer_->Clear();

    if (dim == 2) {
        canvas2d_ = new PlotCanvas2D(coords_, colours_, this);
        sizer_->Add(canvas2d_, 1, wxEXPAND | wxALL, 5);
    } else if (dim == 3) {
        int attr[] = {WX_GL_RGBA,
                      WX_GL_DOUBLEBUFFER,
                      WX_GL_SAMPLE_BUFFERS, GL_TRUE,
                      WX_GL_SAMPLES, 4,
                      WX_GL_DEPTH_SIZE, 16,
                      0};

        canvas3d_ = new PlotCanvas3D(coords_, colours_, this, attr);
        sizer_->Add(canvas3d_, 1, wxEXPAND | wxALL, 5);
    } else {
        wxLogMessage("Invalid dimension (%d) for PCA plot", dim);
        wxLogError("Failed to draw PCA plot");
    }

    sizer_->Add(legend_, 0, wxALL, 5);
    sizer_->Layout();
}

void
PCAPanel::reset()
{
    init_range();
    init_coords();
    init_panel();
}
