//  $Id: manual_gui.h 51 2015-07-20 13:55:18Z dw $
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

#ifndef DASH_MANUAL_GUI_H
#define DASH_MANUAL_GUI_H

#include "dash/dash_fbgui.h"

class ManualGUI : public ManualFBUI
{
 public:
    explicit ManualGUI(wxWindow* parent);

 protected:
    void on_close(wxCommandEvent&);
};

#endif // DASH_MANUAL_GUI_H
