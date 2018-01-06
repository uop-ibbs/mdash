//  $Id: manual_gui.cpp 71 2015-11-24 17:30:39Z dw $
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

#include "dash/manual_gui.h"
#include "dash/mdash_html.h"
#include <string>

ManualGUI::ManualGUI(wxWindow* parent) : ManualFBUI(parent)
{
    html_window->SetPage(mdash_html);
}

void
ManualGUI::on_close(wxCommandEvent& WXUNUSED(event))
{
    Close();
}
