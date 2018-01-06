//  $Id: viewer_gui.h 115 2017-09-21 15:20:56Z dw $
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

#ifndef DASH_VIEWER_GUI_H
#define DASH_VIEWER_GUI_H

#include "dash/dash_fbgui.h"
#include "dash/dash.h"
#include "dash/dash_gui.h"
#include "dash/eigen.h"
#include "dash/frequency_panel.h"
#include "dash/pca_panel.h"
#include "dash/scree_plot_panel.h"
#include "dash/similarity_panel.h"
#include "dash/torsion_histogram_panel.h"
#include "dash/trajectory_panel.h"
#include "dash/viewer_options.h"

#include <wx/bookctrl.h>

class ViewerGUI : public ViewerFBUI
{
 public:
    ViewerGUI(const Dash* dash, DashGUI* parent);
    ~ViewerGUI();

 protected:
    void on_save_dash_output(wxCommandEvent&);
    void on_save_traj_png(wxCommandEvent&);
    void on_save_freq_png(wxCommandEvent&);
    void on_save_sim_png(wxCommandEvent&);
    void on_save_torhist_png(wxCommandEvent&);
    void on_save_scree_png(wxCommandEvent&);
    void on_save_pca_png(wxCommandEvent&);
#ifndef NOAMBER
    void on_save_snapshots(wxCommandEvent&);
#endif
    void on_close(wxCommandEvent&);
    void on_grid_options(wxCommandEvent&);
    void on_pca_options(wxCommandEvent&);
    void on_page_changed(wxBookCtrlEvent&);

 private:
    const Dash* dash_;
    TrajectoryPanel* trajectory_panel_;
    FrequencyPanel* frequency_panel_;
    SimilarityPanel* similarity_panel_;
    TorsionHistogramPanel* torsion_histogram_panel_;
    ScreePlotPanel* scree_plot_panel_;
    PCAPanel* pca_panel_;
    iMatrix bouts_;
    ViewerOptions opt_;

    void init_save_menu();
    void calc_bout_matrix(const state_map& states);
    void save_png(wxImage image);
    wxImage get_image(wxPanel* panel);
};

#endif // DASH_VIEWER_GUI_H
