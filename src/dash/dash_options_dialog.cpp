//  $Id: dash_options_dialog.cpp 105 2017-04-28 14:47:07Z dw $
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

#include "dash/dash_options_dialog.h"
#include "dash/log.h"

DashOptionsDialog::DashOptionsDialog(const DashOptions& opt, int nvars, wxWindow* parent) : DashOptionsDialogFBUI(parent)
{
    vars_choice->SetSelection(opt.circular?0:1);
    window_ctrl->SetValue(opt.window);
    binsize_ctrl->SetValue(opt.binsize);
    runlen_ctrl->SetValue(opt.runlen);
    fmax_ctrl->SetValue(opt.fmax);
    smin_ctrl->SetValue(opt.smin);
    boutlen_ctrl->SetValue(opt.boutlen);
    smooth_ctrl->SetValue(opt.smooth);
    rough_ctrl->SetValue(opt.rough);
    repex_chkbox->SetValue(opt.repex);
    timestep_ctrl->SetValue(opt.timestep);

    if (nvars < 2) {
        pca_chkbox->SetValue(false);
        pca_chkbox->Disable();
    } else {
        pca_chkbox->SetValue(opt.pca);
    }

    pca_autoscale_chkbox->SetValue(opt.pca_autoscale);
    pca_autoscale_chkbox->Enable(opt.pca);
}

void
DashOptionsDialog::load_default_values()
{
    vars_choice->SetSelection(0);
    window_ctrl->SetValue(window_default);
    binsize_ctrl->SetValue(binsize_circular_default);
    runlen_ctrl->SetValue(runlen_default);
    fmax_ctrl->SetValue(fmax_default);
    smin_ctrl->SetValue(smin_circular_default);
    boutlen_ctrl->SetValue(boutlen_default);
    smooth_ctrl->SetValue(smooth_default);
    rough_ctrl->SetValue(rough_default);
    repex_chkbox->SetValue(repex_default);
    timestep_ctrl->SetValue(timestep_default);
    pca_chkbox->SetValue(true);
    pca_autoscale_chkbox->SetValue(pca_autoscale_default);
    pca_autoscale_chkbox->Enable(true);
}

void
DashOptionsDialog::on_pca_chkbox(wxCommandEvent& WXUNUSED(event))
{
    pca_autoscale_chkbox->Enable(pca_chkbox->GetValue());
}

void
DashOptionsDialog::on_vars_choice(wxCommandEvent& WXUNUSED(event))
{
    if (circular()) {
        binsize_ctrl->SetValue(binsize_circular_default);
        smin_ctrl->SetValue(smin_circular_default);
    } else {
        binsize_ctrl->SetValue(binsize_distance_default);
        smin_ctrl->SetValue(smin_distance_default);
    }
}
