//  $Id: grid_options_dialog.h 51 2015-07-20 13:55:18Z dw $
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

#ifndef DASH_GRID_OPTIONS_DIALOG_H
#define DASH_GRID_OPTIONS_DIALOG_H

#include "dash/dash_fbgui.h"

class
GridOptionsDialog : public GridOptionsDialogFBUI
{
 public:
    explicit GridOptionsDialog(wxWindow* parent) : GridOptionsDialogFBUI(parent) {}

    int get_rows() const { return rows_ctrl->GetValue(); }
    int get_cols() const { return cols_ctrl->GetValue(); }
    void set_rows(int r) { rows_ctrl->SetValue(r); }
    void set_cols(int c) { cols_ctrl->SetValue(c); }
};

#endif // DASH_GRID_OPTIONS_DIALOG_H
