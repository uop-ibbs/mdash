///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Sep 12 2017)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __DASH_FBGUI_H__
#define __DASH_FBGUI_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/menu.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/textctrl.h>
#include <wx/sizer.h>
#include <wx/statusbr.h>
#include <wx/frame.h>
#include <wx/stattext.h>
#include <wx/choice.h>
#include <wx/spinctrl.h>
#include <wx/checkbox.h>
#include <wx/button.h>
#include <wx/dialog.h>
#include <wx/notebook.h>
#include <wx/panel.h>
#include <wx/slider.h>
#include <wx/html/htmlwin.h>
#include <wx/radiobox.h>
#include <wx/statbox.h>
#include <wx/grid.h>
#include <wx/checklst.h>
#include <wx/gbsizer.h>

///////////////////////////////////////////////////////////////////////////

#define DASH_OPTIONS_ID 1000
#define DASH_RUN_ID 1001
#define HELP_MANUAL_ID 1002
#define HELP_ABOUT_ID 1003

///////////////////////////////////////////////////////////////////////////////
/// Class DashFBUI
///////////////////////////////////////////////////////////////////////////////
class DashFBUI : public wxFrame 
{
	private:
	
	protected:
		wxMenuBar* menu_bar;
		wxMenu* file_menu;
		wxMenu* open_menu;
		wxMenu* dash_menu;
		wxMenu* help_menu;
		wxTextCtrl* log_ctrl;
		wxStatusBar* status_bar;
		
		// Virtual event handlers, overide them in your derived class
		virtual void on_open_dash( wxCommandEvent& event ) { event.Skip(); }
		virtual void on_open_amber( wxCommandEvent& event ) { event.Skip(); }
		virtual void on_quit( wxCommandEvent& event ) { event.Skip(); }
		virtual void on_options( wxCommandEvent& event ) { event.Skip(); }
		virtual void on_run( wxCommandEvent& event ) { event.Skip(); }
		virtual void on_manual( wxCommandEvent& event ) { event.Skip(); }
		virtual void on_about( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		DashFBUI( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("MDASH"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 600,450 ), long style = wxDEFAULT_FRAME_STYLE|wxSYSTEM_MENU|wxTAB_TRAVERSAL );
		
		~DashFBUI();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class DashOptionsDialogFBUI
///////////////////////////////////////////////////////////////////////////////
class DashOptionsDialogFBUI : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticText19;
		wxChoice* vars_choice;
		wxStaticText* m_staticText3;
		wxSpinCtrl* window_ctrl;
		wxStaticText* m_staticText4;
		wxSpinCtrlDouble* binsize_ctrl;
		wxStaticText* m_staticText5;
		wxSpinCtrl* runlen_ctrl;
		wxStaticText* m_staticText6;
		wxSpinCtrlDouble* fmax_ctrl;
		wxStaticText* m_staticText7;
		wxSpinCtrlDouble* smin_ctrl;
		wxStaticText* m_staticText1;
		wxSpinCtrl* boutlen_ctrl;
		wxStaticText* m_staticText2;
		wxSpinCtrl* smooth_ctrl;
		wxStaticText* m_staticText10;
		wxSpinCtrl* rough_ctrl;
		wxStaticText* m_staticText18;
		wxSpinCtrlDouble* repex_fraction_ctrl;
		wxStaticText* m_staticText20;
		wxSpinCtrl* timestep_ctrl;
		wxCheckBox* repex_chkbox;
		wxCheckBox* pca_chkbox;
		wxCheckBox* pca_autoscale_chkbox;
		wxButton* cancel_btn;
		wxButton* default_btn;
		wxButton* ok_btn;
		
		// Virtual event handlers, overide them in your derived class
		virtual void on_vars_choice( wxCommandEvent& event ) { event.Skip(); }
		virtual void on_pca_chkbox( wxCommandEvent& event ) { event.Skip(); }
		virtual void on_defaults_btn( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		DashOptionsDialogFBUI( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("MDASH Options"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE ); 
		~DashOptionsDialogFBUI();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class ViewerFBUI
///////////////////////////////////////////////////////////////////////////////
class ViewerFBUI : public wxFrame 
{
	private:
	
	protected:
		wxMenuBar* menu_bar;
		wxMenu* file_menu;
		wxMenu* file_save;
		wxMenu* options_menu;
		wxMenuItem* pca_options;
		wxNotebook* notebook;
		wxStatusBar* status_bar;
		
		// Virtual event handlers, overide them in your derived class
		virtual void on_save_dash_output( wxCommandEvent& event ) { event.Skip(); }
		virtual void on_save_traj_png( wxCommandEvent& event ) { event.Skip(); }
		virtual void on_save_freq_png( wxCommandEvent& event ) { event.Skip(); }
		virtual void on_save_sim_png( wxCommandEvent& event ) { event.Skip(); }
		virtual void on_save_torhist_png( wxCommandEvent& event ) { event.Skip(); }
		virtual void on_save_scree_png( wxCommandEvent& event ) { event.Skip(); }
		virtual void on_save_pca_png( wxCommandEvent& event ) { event.Skip(); }
		virtual void on_save_snapshots( wxCommandEvent& event ) { event.Skip(); }
		virtual void on_close( wxCommandEvent& event ) { event.Skip(); }
		virtual void on_grid_options( wxCommandEvent& event ) { event.Skip(); }
		virtual void on_pca_options( wxCommandEvent& event ) { event.Skip(); }
		virtual void on_page_changed( wxNotebookEvent& event ) { event.Skip(); }
		
	
	public:
		
		ViewerFBUI( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("MDASH Viewer"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 800,600 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		
		~ViewerFBUI();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class SummaryPanelFBUI
///////////////////////////////////////////////////////////////////////////////
class SummaryPanelFBUI : public wxPanel 
{
	private:
	
	protected:
		wxTextCtrl* text_ctrl;
	
	public:
		
		SummaryPanelFBUI( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,300 ), long style = wxTAB_TRAVERSAL ); 
		~SummaryPanelFBUI();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class TrajectoryPanelFBUI
///////////////////////////////////////////////////////////////////////////////
class TrajectoryPanelFBUI : public wxPanel 
{
	private:
	
	protected:
		wxPanel* main_panel;
		wxStaticText* m_staticText15;
		wxSlider* slider;
		
		// Virtual event handlers, overide them in your derived class
		virtual void on_zoom( wxScrollEvent& event ) { event.Skip(); }
		
	
	public:
		
		TrajectoryPanelFBUI( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,300 ), long style = wxTAB_TRAVERSAL, const wxString& name = wxT("NAME") ); 
		~TrajectoryPanelFBUI();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class ManualFBUI
///////////////////////////////////////////////////////////////////////////////
class ManualFBUI : public wxFrame 
{
	private:
	
	protected:
		wxMenuBar* menu_bar;
		wxMenu* file_menu;
		wxHtmlWindow* html_window;
		
		// Virtual event handlers, overide them in your derived class
		virtual void on_close( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		ManualFBUI( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("MDASH Manual"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,300 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		
		~ManualFBUI();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class GridOptionsDialogFBUI
///////////////////////////////////////////////////////////////////////////////
class GridOptionsDialogFBUI : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticText11;
		wxSpinCtrl* rows_ctrl;
		wxStaticText* m_staticText12;
		wxSpinCtrl* cols_ctrl;
		wxButton* cancel_btn;
		wxButton* ok_btn;
	
	public:
		
		GridOptionsDialogFBUI( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Histogram Grid Size"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE ); 
		~GridOptionsDialogFBUI();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class PCAOptionsDialogFBUI
///////////////////////////////////////////////////////////////////////////////
class PCAOptionsDialogFBUI : public wxDialog 
{
	private:
	
	protected:
		wxRadioBox* dim_ctrl;
		wxStaticText* m_staticText16;
		wxChoice* pcx_ctrl;
		wxStaticText* m_staticText17;
		wxChoice* pcy_ctrl;
		wxStaticText* m_staticText18;
		wxChoice* pcz_ctrl;
		wxButton* cancel_btn;
		wxButton* ok_btn;
		
		// Virtual event handlers, overide them in your derived class
		virtual void on_dim_ctrl( wxCommandEvent& event ) { event.Skip(); }
		virtual void on_pcx_ctrl( wxCommandEvent& event ) { event.Skip(); }
		virtual void on_pcy_ctrl( wxCommandEvent& event ) { event.Skip(); }
		virtual void on_pcz_ctrl( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		PCAOptionsDialogFBUI( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("PCA Plot"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE ); 
		~PCAOptionsDialogFBUI();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class TrajectoryOptionsDialogFBUI
///////////////////////////////////////////////////////////////////////////////
class TrajectoryOptionsDialogFBUI : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticText13;
		wxSpinCtrl* first_frame_ctrl;
		wxStaticText* m_staticText14;
		wxSpinCtrl* last_frame_ctrl;
		wxButton* cancel_btn;
		wxButton* ok_btn;
	
	public:
		
		TrajectoryOptionsDialogFBUI( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Trajectory Frames"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE ); 
		~TrajectoryOptionsDialogFBUI();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class BoutPanelFBUI
///////////////////////////////////////////////////////////////////////////////
class BoutPanelFBUI : public wxPanel 
{
	private:
	
	protected:
		wxStaticText* m_staticText21;
		wxChoice* units_ctrl;
		wxGrid* grid;
		
		// Virtual event handlers, overide them in your derived class
		virtual void on_units_ctrl( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		BoutPanelFBUI( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,300 ), long style = wxTAB_TRAVERSAL ); 
		~BoutPanelFBUI();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class SimilarityPanelFBUI
///////////////////////////////////////////////////////////////////////////////
class SimilarityPanelFBUI : public wxPanel 
{
	private:
	
	protected:
		wxNotebook* notebook;
		wxPanel* circsim_panel;
		wxStaticText* m_staticText21;
		wxGrid* circsim_legend;
		wxStaticText* m_staticText22;
		wxGrid* circsim_grid;
		wxPanel* cosim_panel;
		wxStaticText* m_staticText23;
		wxGrid* cosim_legend;
		wxStaticText* m_staticText24;
		wxGrid* cosim_grid;
	
	public:
		
		SimilarityPanelFBUI( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 600,300 ), long style = wxTAB_TRAVERSAL ); 
		~SimilarityPanelFBUI();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class AmberDialogFBUI
///////////////////////////////////////////////////////////////////////////////
class AmberDialogFBUI : public wxDialog 
{
	private:
	
	protected:
		wxGridBagSizer* amber_dialog_sizer;
		wxStaticText* m_staticText25;
		wxTextCtrl* top_ctrl;
		wxButton* top_browse;
		wxStaticText* m_staticText26;
		wxTextCtrl* trj_ctrl;
		wxButton* trj_browse;
		wxStaticText* m_staticText29;
		wxTextCtrl* res_ctrl;
		wxStaticText* m_staticText30;
		wxCheckBox* phi_ctrl;
		wxCheckBox* psi_ctrl;
		wxCheckBox* chi_ctrl;
		wxCheckBox* omega_ctrl;
		wxCheckListBox* tmpfile_ctrl;
		wxStdDialogButtonSizer* m_sdbSizer1;
		wxButton* m_sdbSizer1OK;
		wxButton* m_sdbSizer1Cancel;
		
		// Virtual event handlers, overide them in your derived class
		virtual void on_top_browse( wxCommandEvent& event ) { event.Skip(); }
		virtual void on_trj_browse( wxCommandEvent& event ) { event.Skip(); }
		virtual void on_save_tmpfiles( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		AmberDialogFBUI( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Read Amber Trajectory"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE ); 
		~AmberDialogFBUI();
	
};

#endif //__DASH_FBGUI_H__
