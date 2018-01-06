//  $Id: trajectory_options_dialog.h 51 2015-07-20 13:55:18Z dw $
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

#ifndef DASH_TRAJECTORY_OPTIONS_DIALOG_H
#define DASH_TRAJECTORY_OPTIONS_DIALOG_H

#include "dash/dash_fbgui.h"

class
TrajectoryOptionsDialog : public TrajectoryOptionsDialogFBUI
{
 public:
    TrajectoryOptionsDialog(int frames, wxWindow* parent);

    int get_first_frame() const { return first_frame_ctrl->GetValue(); }
    int get_last_frame() const { return last_frame_ctrl->GetValue(); }
    void set_first_frame(int i) { first_frame_ctrl->SetValue(i); }
    void set_last_frame(int i) { last_frame_ctrl->SetValue(i); }
};

#endif // DASH_TRAJECTORY_OPTIONS_DIALOG_H
