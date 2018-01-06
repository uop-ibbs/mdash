//  $Id: pca_options_dialog.cpp 105 2017-04-28 14:47:07Z dw $
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

#include "dash/pca_options_dialog.h"

PCAOptionsDialog::PCAOptionsDialog(const ViewerOptions& opt, int npc, wxWindow* parent)
    : PCAOptionsDialogFBUI(parent)
{
    init_pc_ctrls(npc);
    pcx_ctrl->SetSelection(opt.pca_pcx);
    pcy_ctrl->SetSelection(opt.pca_pcy);
    pcz_ctrl->SetSelection(opt.pca_pcz);
    dim_ctrl->SetSelection(opt.pca_dim-2);
    pcz_ctrl->Enable(dim_ctrl->GetSelection() != 0);

    if (npc < 3) {
        dim_ctrl->Disable();
    }
}

void
PCAOptionsDialog::init_pc_ctrls(int n)
{
    // these are needed because the fbui inserts dummy values to set
    // the width of the drop-downs
    pcx_ctrl->Clear();
    pcy_ctrl->Clear();
    pcz_ctrl->Clear();

    for (int i=1; i<=n; ++i) {
        pcx_ctrl->Append(wxString::Format(" PC%d ", i));
        pcy_ctrl->Append(wxString::Format(" PC%d ", i));
        pcz_ctrl->Append(wxString::Format(" PC%d ", i));
    }
}

void
PCAOptionsDialog::on_dim_ctrl(wxCommandEvent& WXUNUSED(event))
{
    pcz_ctrl->Enable(dim_ctrl->GetSelection() != 0);
}
