//  $Id: dash_options_dialog.h 105 2017-04-28 14:47:07Z dw $
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

#ifndef DASH_DASH_OPTIONS_DIALOG_H
#define DASH_DASH_OPTIONS_DIALOG_H

#include "dash/dash_fbgui.h"
#include "dash/dash_options.h"

class
DashOptionsDialog : public DashOptionsDialogFBUI
{
 public:
    DashOptionsDialog(const DashOptions& opt, int nvars, wxWindow* parent);

    bool circular() const { return (vars_choice->GetSelection() == 0);}
    int window() const { return window_ctrl->GetValue(); }
    float binsize() const { return binsize_ctrl->GetValue(); }
    int runlen() const { return runlen_ctrl->GetValue(); }
    float fmax() const { return fmax_ctrl->GetValue(); }
    float smin() const { return smin_ctrl->GetValue(); }
    int boutlen() const { return boutlen_ctrl->GetValue(); }
    int smooth() const { return smooth_ctrl->GetValue(); }
    int rough() const { return rough_ctrl->GetValue(); }
    float repex_fraction() const { return repex_fraction_ctrl->GetValue(); }
    bool repex() const { return repex_chkbox->GetValue(); }
    int timestep() const { return timestep_ctrl->GetValue(); }
    bool pca() const { return pca_chkbox->GetValue(); }
    bool pca_autoscale() const { return pca_autoscale_chkbox->GetValue(); }

 protected:
    void on_defaults_btn(wxCommandEvent&) { load_default_values(); }
    void on_ok_btn(wxCommandEvent&);
    void on_pca_chkbox(wxCommandEvent&);
    void on_vars_choice(wxCommandEvent&);

 private:
    void load_default_values();
};

#endif // DASH_DASH_OPTIONS_DIALOG_H
