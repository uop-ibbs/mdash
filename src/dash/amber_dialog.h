//  $Id: amber_dialog.h 111 2017-08-08 16:08:52Z dw $
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

#ifndef DASH_AMBER_DIALOG_H
#define DASH_AMBER_DIALOG_H

#include "dash/amber_options.h"
#include "dash/dash_fbgui.h"

class
AmberDialog : public AmberDialogFBUI
{
 public:
    AmberDialog(wxWindow* parent, AmberOptions& opt);

    std::string top_file() const { return top_ctrl->GetLineText(0).ToStdString(); }
    std::string trj_file() const { return trj_ctrl->GetLineText(0).ToStdString(); }
    std::string residues() const { return res_ctrl->GetLineText(0).ToStdString(); }
    bool save_dash_input() const { return tmpfile_ctrl->IsChecked(0); }
    bool save_cpptraj_input() const { return tmpfile_ctrl->IsChecked(1); }
    bool save_cpptraj_output() const { return tmpfile_ctrl->IsChecked(2); }

 private:
    void on_top_browse(wxCommandEvent& WXUNUSED(event));
    void on_trj_browse(wxCommandEvent& WXUNUSED(event));
};

#endif // DASH_AMBER_DIALOG_H
