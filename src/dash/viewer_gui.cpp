//  $Id: viewer_gui.cpp 131 2017-11-29 08:52:35Z dw $
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

#include "dash/viewer_gui.h"

#include "dash/bout_panel.h"
#include "dash/dash_state_panel.h"
#include "dash/dash_exception.h"
#include "dash/frequency_panel.h"
#include "dash/grid_options_dialog.h"
#include "dash/pca_options_dialog.h"
#include "dash/pca_panel.h"
#include "dash/repex_state_panel.h"
#include "dash/scree_plot_panel.h"
#include "dash/similarity_panel.h"
#include "dash/summary_panel.h"
#include "dash/torsion_histogram_panel.h"
#include "dash/torsion_state_panel.h"
#include "dash/trajectory_options_dialog.h"
#include "dash/trajectory_panel.h"
#include "dash/version.h"

#include "dash/icons/mdash128.xpm"

#include <algorithm>
#include <ctime>
#include <fstream>

#include <wx/filedlg.h>
#include <wx/log.h>

ViewerGUI::ViewerGUI(const Dash* dash, DashGUI* dash_gui) : ViewerFBUI(dash_gui), dash_(dash)
{
    SetIcon(wxIcon(mdash));
    opt_.pca_dim = std::min(opt_.pca_dim, static_cast<int>(dash_->vars()));
    pca_options->Enable(dash_->pca() && dash_gui->opengl_support());

    init_save_menu();

    SummaryPanel* summary_panel = new SummaryPanel(dash_->summary(), notebook);
    notebook->AddPage(summary_panel, "Summary");

    if (dash_->time_series()) {
        try {
            trajectory_panel_ = new TrajectoryPanel(dash_->dash_trajectory(), notebook);
            notebook->AddPage(trajectory_panel_, "Trajectory");
        } catch (const DashException& e) {
            wxLogMessage(e.what());
            wxLogError("Failed to draw dash trajectory");
        }

        // frequency and bout panels require bouts as a matrix
        calc_bout_matrix(dash_->dash_state_map());
        frequency_panel_ = new FrequencyPanel(bouts_, notebook);
        notebook->AddPage(frequency_panel_, "Frequencies");

        BoutPanel* bout_panel = new BoutPanel(bouts_, dash_->timestep(), notebook);
        notebook->AddPage(bout_panel, "Bouts");

        DashStatePanel* dash_state_panel = new DashStatePanel(dash_->dash_state_map(), dash_->frames(), notebook);
        notebook->AddPage(dash_state_panel, "Dash States");

        similarity_panel_ = new SimilarityPanel(dash_->dash_trajectory().circular_sim, dash_->dash_trajectory().cosine_sim, notebook);
        notebook->AddPage(similarity_panel_, "Similarity");
    } else {
        RepexStatePanel* repex_state_panel = new RepexStatePanel(dash_->new_repex_states_ref(), dash_->frames(), notebook);
        notebook->AddPage(repex_state_panel, "Replica Exchange States");

        similarity_panel_ = new SimilarityPanel(dash_->repex_trajectory().circular_sim, dash_->repex_trajectory().cosine_sim, notebook);
        notebook->AddPage(similarity_panel_, "Similarity");
    }

    torsion_histogram_panel_ = new TorsionHistogramPanel(dash_->torsion_data_ptr(), dash_->vars(), opt_.thp_rows, opt_.thp_cols, notebook);
    notebook->AddPage(torsion_histogram_panel_, "Torsion Histograms");

    TorsionStatePanel* torsion_state_panel = new TorsionStatePanel(dash_->torsion_data_ptr(), notebook);
    notebook->AddPage(torsion_state_panel, "Torsion States");

    if (dash_->pca() != nullptr) {
        scree_plot_panel_ = new ScreePlotPanel(dash_->pca(), notebook);
        notebook->AddPage(scree_plot_panel_, "Scree Plot");

        if (dash_gui->opengl_support()) {
            pca_panel_ = new PCAPanel(dash_->pca()->scores(), dash_->dash_trajectory(), opt_, notebook);
            notebook->AddPage(pca_panel_, "PCA");
        }
    }

    status_bar->SetStatusText(wxString::Format("Trajectory: %s", dash_->trajectory_input_file()));
}

ViewerGUI::~ViewerGUI()
{
    delete dash_;
}

void
ViewerGUI::init_save_menu()
{
    const std::string traj_label = "Trajectory plot...";
    const std::string freq_label = "Frequency plot...";
    const std::string scree_label = "Scree plot...";

    const int traj_id = file_save->FindItem(traj_label);
    const int freq_id = file_save->FindItem(freq_label);
    const int scree_id = file_save->FindItem(scree_label);

    if (traj_id != wxNOT_FOUND) file_save->Enable(traj_id, dash_->time_series());
    if (freq_id != wxNOT_FOUND) file_save->Enable(freq_id, dash_->time_series());
    if (scree_id != wxNOT_FOUND) file_save->Enable(scree_id, dash_->pca());

#ifndef NOAMBER
    const std::string snap_label = "PDB snapshots...";
    const int snap_id = file_save->FindItem(snap_label);
    if (snap_id != wxNOT_FOUND) file_save->Enable(snap_id, dash_->time_series() && !dash_->top_file().empty());
#endif
}

void
ViewerGUI::calc_bout_matrix(const state_map& states)
{
    // find maximum number of bouts in a single state
    size_t maxbouts = 0;

    for (state_map::const_iterator i=states.begin(); i!=states.end(); ++i) {
        size_t nbouts = i->second.bouts.size();
        if (nbouts > maxbouts) maxbouts = nbouts;
    }

    // calculate bout matrix
    int s = 0;
    bouts_.resize(states.size(), maxbouts);

    for (state_map::const_iterator i=states.begin(); i!=states.end(); ++i, ++s) {
        int state_nvals = 0;

        for (size_t j=0; j<i->second.bouts.size(); ++j) {
            bouts_(s,j) = i->second.bouts[j];
            state_nvals += bouts_(s,j);
        }

        for (size_t j=i->second.bouts.size(); j<maxbouts; ++j) {
            bouts_(s,j) = 0;
        }
    }
}

void
ViewerGUI::on_close(wxCommandEvent& WXUNUSED(event))
{
    Close();
}

void
ViewerGUI::on_save_dash_output(wxCommandEvent& WXUNUSED(event))
{
    wxFileDialog dlg(this,
                     "Save Dash Output As...",
                     wxEmptyString,
                     wxEmptyString,
                     ("All files (*.*)|*.*"),
                     wxFD_SAVE|wxFD_OVERWRITE_PROMPT);

    if (dlg.ShowModal() == wxID_OK) {
        std::ofstream ofs(dlg.GetPath().ToStdString());

        if (!ofs) {
            wxLogMessage("Unable to write file %s", dlg.GetPath().ToStdString());
            wxLogError("Unable to write output file");
            return;
        }

        ofs << dash_version << '\n';
        time_t now = time(0);

        if (now != static_cast<time_t>(-1)) {
            ofs << ctime(&now) << '\n';
        }

        try {
            dash_->write(ofs);
        } catch (const DashException& e) {
            wxLogMessage(e.what());
            wxLogError("Failed to write output file");
            return;
        }
    }
}

void
ViewerGUI::on_save_traj_png(wxCommandEvent& WXUNUSED(event))
{
    save_png(trajectory_panel_->get_chart_panel()->CopyBackbuffer().ConvertToImage());
}

void
ViewerGUI::on_save_freq_png(wxCommandEvent& WXUNUSED(event))
{
    save_png(frequency_panel_->get_chart_panel()->CopyBackbuffer().ConvertToImage());
}

void
ViewerGUI::on_save_sim_png(wxCommandEvent& WXUNUSED(event))
{
    if (similarity_panel_->IsShown()) {
        save_png(get_image(similarity_panel_->sim_panel()));
    } else {
        wxLogError("Unable to save png: similarity panel not visible");
    }
}

void
ViewerGUI::on_save_torhist_png(wxCommandEvent& WXUNUSED(event))
{
    if (torsion_histogram_panel_->IsShown()) {
        save_png(get_image(torsion_histogram_panel_->get_grid_panel()));
    } else {
        wxLogError("Unable to save png: histogram panel not visible");
    }
}

void
ViewerGUI::on_save_scree_png(wxCommandEvent& WXUNUSED(event))
{
    save_png(scree_plot_panel_->get_chart_panel()->CopyBackbuffer().ConvertToImage());
}

void
ViewerGUI::on_save_pca_png(wxCommandEvent& WXUNUSED(event))
{
    if (pca_panel_->IsShown()) {
        GLint view[4];
        glGetIntegerv(GL_VIEWPORT, view);

        // wximage requires use of malloc
        unsigned char *pixels = (unsigned char*)malloc(3 * view[2] * view[3]);
        glPixelStorei(GL_PACK_ALIGNMENT, 1);
        glReadBuffer(GL_BACK_LEFT);
        glReadPixels(0, 0, view[2], view[3], GL_RGB, GL_UNSIGNED_BYTE, pixels);
        wxImage img(view[2], view[3]);
        img.SetData(pixels); // wximage now responsible for freeing pixels
        save_png(img.Mirror(false));
    } else {
        wxLogError("Unable to save png: pca panel not visible");
    }
}

void
ViewerGUI::save_png(wxImage image)
{
    wxFileDialog dlg(this,
                     "Save PNG Image As...",
                     wxEmptyString,
                     wxEmptyString,
                     ("PNG files (*.png)|*.png"),
                     wxFD_SAVE|wxFD_OVERWRITE_PROMPT);

    if (dlg.ShowModal() == wxID_OK) {
        if (image.IsOk()) {
            if (image.HasAlpha()) image.ClearAlpha();  // necessary for Windows
            image.SetOption(wxIMAGE_OPTION_PNG_FORMAT, wxPNG_TYPE_COLOUR);
            image.SetOption(wxIMAGE_OPTION_PNG_BITDEPTH, 16);
            image.SaveFile(dlg.GetPath(), wxBITMAP_TYPE_PNG);
        } else {
            wxLogError("Unable to save png: no image data");
        }
    }
}

#ifndef NOAMBER
void
ViewerGUI::on_save_snapshots(wxCommandEvent& WXUNUSED(event))
{
    std::string msg;

    if (!dash_->write_snapshots(msg)) {
        wxLogError(msg.c_str());
    } else {
        wxMessageDialog dlg(this, "Snapshots saved successfully");
        dlg.ShowModal();
    }
}
#endif // NOAMBER

void
ViewerGUI::on_grid_options(wxCommandEvent& WXUNUSED(event))
{
    GridOptionsDialog dlg(this);

    int orows = opt_.thp_rows;
    int ocols = opt_.thp_cols;

    dlg.set_rows(orows);
    dlg.set_cols(ocols);

    if (dlg.ShowModal() == wxID_OK) {
        opt_.thp_rows = dlg.get_rows();
        opt_.thp_cols = dlg.get_cols();

        if (orows != opt_.thp_rows || ocols != opt_.thp_cols) {
            torsion_histogram_panel_->resize(opt_.thp_rows, opt_.thp_cols);
        }
    }
}

void
ViewerGUI::on_pca_options(wxCommandEvent& WXUNUSED(event))
{
    PCAOptionsDialog dlg(opt_, dash_->vars(), this);

    if (dlg.ShowModal() == wxID_OK) {
        opt_.pca_dim = dlg.dim();
        opt_.pca_pcx = dlg.pcx();
        opt_.pca_pcy = dlg.pcy();
        opt_.pca_pcz = dlg.pcz();
    }

    pca_panel_->reset();
}

wxImage
ViewerGUI::get_image(wxPanel* panel)
{
    wxClientDC clientDC(panel);
    wxCoord width, height;
    clientDC.GetSize(&width, &height);
    wxBitmap screenshot(width, height, -1);
    wxMemoryDC memDC;
    memDC.SelectObject(screenshot);
    memDC.Blit(0, 0, width, height, &clientDC, 0, 0);
    memDC.SelectObject(wxNullBitmap);

    return screenshot.ConvertToImage();
}

// png images of similarity matrices, torsion histograms
// and pca can only be saved when the pages are visible
void
ViewerGUI::on_page_changed(wxBookCtrlEvent& event)
{
    const std::string sim_label = "Similarity matrix...";
    const std::string tor_label = "Torsion histograms...";
    const std::string pca_label = "PCA plot...";

    const int sim_page = dash_->time_series() ? 5 : 2;
    const int tor_page = dash_->time_series() ? 6 : 3;
    const int pca_page = dash_->time_series() ? 9 : 6;

    if (event.GetSelection() == sim_page) {
        int id = file_save->FindItem(sim_label);
        if (id != wxNOT_FOUND) file_save->Enable(id, true);
    } else if (event.GetSelection() == tor_page) {
        int id = file_save->FindItem(tor_label);
        if (id != wxNOT_FOUND) file_save->Enable(id, true);
    } else if (event.GetSelection() == pca_page) {
        int id = file_save->FindItem(pca_label);
        if (id != wxNOT_FOUND) file_save->Enable(id, true);
    }

    if (event.GetOldSelection() == sim_page) {
        int id = file_save->FindItem(sim_label);
        if (id != wxNOT_FOUND) file_save->Enable(id, false);
    } else if (event.GetOldSelection() == tor_page) {
        int id = file_save->FindItem(tor_label);
        if (id != wxNOT_FOUND) file_save->Enable(id, false);
    } else if (event.GetOldSelection() == pca_page) {
        int id = file_save->FindItem(pca_label);
        if (id != wxNOT_FOUND) file_save->Enable(id, false);
    }
}
