//  $Id: amber_dialog.cpp 116 2017-09-21 16:19:22Z dw $
//
//  Copyright (C) 2017 School of Pharmacy and Biomedical Sciences, University of Portsmouth.
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

#include "dash/amber_dialog.h"

#include <wx/filedlg.h>
#include <wx/valgen.h>
#include <wx/valtext.h>

AmberDialog::AmberDialog(wxWindow* parent, AmberOptions& opt) : AmberDialogFBUI(parent) {
    top_ctrl->SetValidator(wxTextValidator(wxFILTER_EMPTY));
    trj_ctrl->SetValidator(wxTextValidator(wxFILTER_EMPTY));
    phi_ctrl->SetValidator(wxGenericValidator(&opt.phi));
    psi_ctrl->SetValidator(wxGenericValidator(&opt.psi));
    chi_ctrl->SetValidator(wxGenericValidator(&opt.chi));
    omega_ctrl->SetValidator(wxGenericValidator(&opt.omega));
}

void
AmberDialog::on_top_browse(wxCommandEvent& WXUNUSED(event))
{
    wxFileDialog dialog(this,
                        "Open Amber topology file",
                        "",
                        "",
                        "Topology files (*.top;*.parm;*.parm7)|*.top;*.parm;*.parm7|All files (*.*)|*",
                        wxFD_OPEN|wxFD_FILE_MUST_EXIST);

    if (dialog.ShowModal() == wxID_OK) {
        wxString path = dialog.GetPath();
        top_ctrl->SetValue(path);
    }
}

void
AmberDialog::on_trj_browse(wxCommandEvent& WXUNUSED(event))
{
    wxFileDialog dialog(this,
                        "Open Amber trajectory file",
                        "",
                        "",
                        "Trajectory files (*.nc;*.trj;*.trajin)|*.nc;*.trj;*.trajin|All files (*.*)|*",
                        wxFD_OPEN|wxFD_FILE_MUST_EXIST);

    if (dialog.ShowModal() == wxID_OK) {
        wxString path = dialog.GetPath();
        trj_ctrl->SetValue(path);
    }
}
