//  $Id: pca_options_dialog.h 81 2016-02-12 17:12:47Z dw $
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

#ifndef DASH_PCA_OPTIONS_DIALOG_H
#define DASH_PCA_OPTIONS_DIALOG_H

#include "dash/dash_fbgui.h"
#include "dash/viewer_options.h"

class
PCAOptionsDialog : public PCAOptionsDialogFBUI
{
 public:
    PCAOptionsDialog(const ViewerOptions& opt, int npc, wxWindow* parent);

    int dim() const { return dim_ctrl->GetSelection() + 2; }
    int pcx() const { return pcx_ctrl->GetSelection(); }
    int pcy() const { return pcy_ctrl->GetSelection(); }
    int pcz() const { return pcz_ctrl->GetSelection(); }

    void on_dim_ctrl(wxCommandEvent&);

 private:
    void init_pc_ctrls(int i);
};

#endif // DASH_PCA_OPTIONS_DIALOG_H
