//  $Id: trajectory_options_dialog.cpp 51 2015-07-20 13:55:18Z dw $
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

#include "dash/trajectory_options_dialog.h"

TrajectoryOptionsDialog::TrajectoryOptionsDialog(int frames, wxWindow* parent) : TrajectoryOptionsDialogFBUI(parent)
{
    first_frame_ctrl->SetRange(1, frames);
    last_frame_ctrl->SetRange(1, frames);
}
