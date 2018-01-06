//  $Id: dash_gui.cpp 120 2017-10-11 13:49:06Z dw $
//
//  Copyright (C) 2015 Centre for Molecular Design, University of Portsmouth.
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

#include "dash/dash_gui.h"
#include "dash/amber_dialog.h"
#include "dash/amber_trajectory_reader.h"
#include "dash/dash.h"
#include "dash/dash_exception.h"
#include "dash/dash_options_dialog.h"
#include "dash/external.h"
#include "dash/manual_gui.h"
#include "dash/version.h"
#include "dash/viewer_gui.h"

#include "dash/dash_icon.xpm"

#include <fstream>
#include <string>
#include <system_error>
#include <vector>

#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>

#include <wx/aboutdlg.h>
#include <wx/filedlg.h>
#include <wx/arrstr.h>

#include <GL/glew.h>
#include <wx/glcanvas.h>
#include <wx/gdicmn.h>

DashGUI::DashGUI(wxWindow* parent) : DashFBUI(parent)
{
    SetIcon(wxIcon(dash_icon));

#ifdef NOAMBER
    int id = open_menu->FindItem("Amber trajectory...");

    if (id != wxNOT_FOUND) {
        open_menu->Enable(id, false);
    }
#endif

    update_menus(false);
    log_ = new Log(log_ctrl, wxLog::GetActiveTarget());
    wxLog::SetActiveTarget(log_);
    wxImage::AddHandler(new wxPNGHandler);
    check_opengl();
}

void
DashGUI::check_opengl()
{
    int attr_rgba[] = {WX_GL_RGBA, 0};
    int attr_dble[] = {WX_GL_DOUBLEBUFFER, 0};
    int attr_smbf[] = {WX_GL_SAMPLE_BUFFERS, GL_TRUE, 0};
    int attr_samp[] = {WX_GL_SAMPLES, 4, 0};
    int attr_dpth[] = {WX_GL_DEPTH_SIZE, 16, 0};

    if (!wxGLCanvas::IsDisplaySupported(attr_rgba)) {
        wxLogMessage("Warning: GL_RGBA not supported");
    }

    if (!wxGLCanvas::IsDisplaySupported(attr_dble)) {
        wxLogMessage("Warning: GL_DOUBLEBUFFER not supported");
    }

    if (!wxGLCanvas::IsDisplaySupported(attr_smbf)) {
        wxLogMessage("Warning: GL_SAMPLE_BUFFERS not supported");
    }

    if (!wxGLCanvas::IsDisplaySupported(attr_samp)) {
        wxLogMessage("Warning: GL_SAMPLES not supported");
    }

    if (!wxGLCanvas::IsDisplaySupported(attr_dpth)) {
        wxLogMessage("Warning: GL_DEPTH_SIZE not supported");
    }

    int attr[] = {WX_GL_RGBA,
                  WX_GL_DOUBLEBUFFER,
                  WX_GL_SAMPLE_BUFFERS, GL_TRUE,
                  WX_GL_SAMPLES, 4,
                  WX_GL_DEPTH_SIZE, 16,
                  0};

    opengl_support_ = wxGLCanvas::IsDisplaySupported(attr);

    if (!opengl_support_) {
        wxLogMessage("Warning: OpenGL display not supported, PCA plots disabled.");
    }
}

void
DashGUI::on_open_dash(wxCommandEvent& WXUNUSED(event))
{
    wxFileDialog dlg(this,
                     "Open Trajectory File",
                     "",
                     "",
                     "All files (*.*)|*",
                     wxFD_OPEN|wxFD_FILE_MUST_EXIST);

    if (dlg.ShowModal() == wxID_OK) {
        wxString pathname = dlg.GetPath();
        wxLogMessage("Reading trajectory file %s ...", pathname.c_str());
        std::string msg;

        if (trj_.read(pathname.ToStdString(), msg)) {
            wxLogMessage("Found %d variables, %d frames", trj_.vars, trj_.frames);
            status_bar->SetStatusText(wxString::Format("Current trajectory: %s", dlg.GetFilename()));
            update_menus(true);
        } else {
            wxLogMessage(msg.c_str());
            wxLogError("Failed to read trajectory");
        }
    }
}

#ifndef NOAMBER
void
DashGUI::on_open_amber(wxCommandEvent& WXUNUSED(event))
{
    AmberOptions opt;
    AmberDialog dlg(this, opt);

    if (dlg.ShowModal() == wxID_OK) {
        opt.top_file = dlg.top_file();
        opt.trj_file = dlg.trj_file();
        opt.residues = dlg.residues();
        opt.save_dash_input = dlg.save_dash_input();
        opt.save_cpptraj_input = dlg.save_cpptraj_input();
        opt.save_cpptraj_output = dlg.save_cpptraj_output();

        AmberTrajectoryReader ambtrj;
        std::string ambmsg;

        wxLogMessage("Reading Amber trajectory ...");
        bool result = ambtrj.read(opt, ambmsg);

        if (dlg.save_cpptraj_input() && !external::save(ambtrj.cpptraj_in(), "cpptraj.in")) {
            wxLogWarning("Failed to save cpptraj input file");
        }

        if (dlg.save_cpptraj_output() && !external::save(ambtrj.cpptraj_out(), "cpptraj.out")) {
            wxLogWarning("Failed to save cpptraj output file");
        }

        if (dlg.save_cpptraj_output() && !external::save(ambtrj.cpptraj_err(), "cpptraj.err")) {
            wxLogWarning("Failed to save cpptraj error file");
        }

        write_log(ambtrj.cpptraj_out());
        write_log(ambtrj.cpptraj_err());

        if (!(result && ambmsg.empty())) {
            wxLogMessage(ambmsg.c_str());
            wxLogError("Failed to read Amber trajectory");
            return;
        }

        wxLogMessage("Reading trajectory file %s ...", opt.dash_input_file.c_str());
        std::string trjmsg;

        if (trj_.read(opt.dash_input_file, trjmsg, opt.top_file, opt.trj_file)) {
            wxLogMessage("Found %d variables, %d frames", trj_.vars, trj_.frames);
            status_bar->SetStatusText(wxString::Format("Current trajectory: %s", opt.trj_file.c_str()));
            update_menus(true);
        } else {
            wxLogMessage(trjmsg.c_str());
            wxLogError("Failed to read trajectory");
        }

        if (!dlg.save_dash_input()) {
            boost::system::error_code ec;
            boost::filesystem::remove(opt.dash_input_file, ec);

            if (ec) {
                std::string msg = "Failed to remove mdash input file\nerror_code: "
                    + std::string(ec.category().name()) + ": " + ec.message();
                wxLogMessage(msg.c_str());
            }
        }
    }
}

void
DashGUI::write_log(std::string s)
{
    if (s.empty()) return;

    std::vector<std::string> log;
    boost::split(log, s, boost::is_any_of("\n"));

    for (auto&& s : log) {
        wxLogMessage(s.c_str());
    }
}
#endif // NOAMBER

void
DashGUI::on_quit(wxCommandEvent& WXUNUSED(event))
{
    Close();
}

void
DashGUI::on_options(wxCommandEvent& WXUNUSED(event))
{
    DashOptionsDialog dlg(opt_, trj_.vars, this);

    if (dlg.ShowModal() == wxID_OK) {
        opt_.circular = dlg.circular();
        opt_.window = dlg.window();
        opt_.binsize = dlg.binsize();
        opt_.runlen = dlg.runlen();
        opt_.fmax = dlg.fmax();
        opt_.smin = dlg.smin();
        opt_.boutlen = dlg.boutlen();
        opt_.smooth = dlg.smooth();
        opt_.rough = dlg.rough();
        opt_.repex = dlg.repex();
        opt_.timestep = dlg.timestep();
        opt_.repex_fraction = dlg.repex_fraction();
        opt_.pca = dlg.pca();
        opt_.pca_autoscale = dlg.pca_autoscale();

        if (opt_.repex) {
            opt_.write_smoothed = opt_.write_sequence = opt_.write_dash = false;
            opt_.pca = false;
        }
    }
}

void
DashGUI::on_run(wxCommandEvent& WXUNUSED(event))
{
    Dash* dash = new Dash(trj_, opt_);

    try {
        dash->run();
    } catch (const DashException& e) {
        wxLogMessage(e.what());
        wxLogError("Dash calculation failed");
        delete dash;
        return;
    }

    ViewerGUI* viewer = new ViewerGUI(dash, this);
    wxPoint pos = GetPosition();
    wxPoint offset(100,100);
    viewer->SetPosition(pos+offset);
    viewer->Show();
}

void
DashGUI::on_manual(wxCommandEvent& WXUNUSED(event))
{
    ManualGUI* manual = new ManualGUI(this);
    wxPoint pos = GetPosition();
    wxPoint offset(100,100);
    manual->SetPosition(pos+offset);
    manual->Show();
}

void
DashGUI::on_about(wxCommandEvent& WXUNUSED(event))
{
    wxAboutDialogInfo aboutInfo;
    aboutInfo.SetName("MDASH");
    aboutInfo.SetVersion(version);
    aboutInfo.SetDescription("Extract states from molecular dynamics trajectories");
    aboutInfo.SetCopyright("(C) 2008-2017 Centre for Molecular Design, University of Portsmouth");
    aboutInfo.SetWebSite("http://www.port.ac.uk/research/cmd/software");
    aboutInfo.SetIcon(wxIcon(dash_icon));
    aboutInfo.SetLicense("This program is free software; you can redistribute it and/or modify\n"
                         "it under the terms of the GNU General Public Licence as published by\n"
                         "the Free Software Foundation; either version 3 of the Licence, or\n"
                         "(at your option) any later version.\n\n"
                         "This program is distributed in the hope that it will be useful,\n"
                         "but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
                         "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
                         "GNU General Public Licence for more details.\n\n"
                         "You should have received a copy of the GNU General Public Licence\n"
                         "along with this program; if not, write to the Free Software\n"
                         "Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA.");
    wxAboutBox(aboutInfo, this);
}

void
DashGUI::update_menus(bool enable_dash_menu)
{
    menu_bar->EnableTop(DASH_MENU, enable_dash_menu);
}
