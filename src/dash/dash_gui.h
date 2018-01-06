//  $Id: dash_gui.h 113 2017-08-18 14:59:42Z dw $
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

#ifndef DASH_DASH_GUI_H
#define DASH_DASH_GUI_H

#include "dash/dash_fbgui.h"
#include "dash/dash_options.h"
#include "dash/log.h"
#include "dash/trajectory.h"

class DashGUI : public DashFBUI
{
 public:
    explicit DashGUI(wxWindow* parent);

    bool opengl_support() const { return opengl_support_; };

 protected:
    void on_open_dash(wxCommandEvent&);
#ifndef NOAMBER
    void on_open_amber(wxCommandEvent&);
    void write_log(std::string s);
#endif
    void on_quit(wxCommandEvent&);
    void on_options(wxCommandEvent&);
    void on_run(wxCommandEvent&);
    void on_manual(wxCommandEvent&);
    void on_about(wxCommandEvent&);

 private:
    Log* log_;
    DashOptions opt_;
    Trajectory trj_;
    bool opengl_support_;

    // used in enabling/disabling top-level menus
    enum {FILE_MENU, DASH_MENU, HELP_MENU};

    void update_menus(bool enable_dash_menu);
    void check_opengl();
};

#endif // DASH_DASH_GUI_H
