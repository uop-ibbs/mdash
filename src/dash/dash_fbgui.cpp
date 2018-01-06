///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Sep 12 2017)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "dash_fbgui.h"

///////////////////////////////////////////////////////////////////////////

DashFBUI::DashFBUI( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( 400,300 ), wxDefaultSize );
	
	menu_bar = new wxMenuBar( 0 );
	file_menu = new wxMenu();
	open_menu = new wxMenu();
	wxMenuItem* open_menuItem = new wxMenuItem( file_menu, wxID_ANY, wxT("&Open"), wxEmptyString, wxITEM_NORMAL, open_menu );
	wxMenuItem* open_dash;
	open_dash = new wxMenuItem( open_menu, wxID_ANY, wxString( wxT("&Dash input file...") ) , wxEmptyString, wxITEM_NORMAL );
	open_menu->Append( open_dash );
	
	wxMenuItem* open_amber;
	open_amber = new wxMenuItem( open_menu, wxID_ANY, wxString( wxT("&Amber trajectory...") ) , wxEmptyString, wxITEM_NORMAL );
	open_menu->Append( open_amber );
	
	file_menu->Append( open_menuItem );
	
	wxMenuItem* file_quit;
	file_quit = new wxMenuItem( file_menu, wxID_EXIT, wxString( wxEmptyString ) , wxEmptyString, wxITEM_NORMAL );
	file_menu->Append( file_quit );
	
	menu_bar->Append( file_menu, wxT("&File") ); 
	
	dash_menu = new wxMenu();
	wxMenuItem* dash_options;
	dash_options = new wxMenuItem( dash_menu, DASH_OPTIONS_ID, wxString( wxT("&Options...") ) , wxT("Set Dash options"), wxITEM_NORMAL );
	dash_menu->Append( dash_options );
	
	wxMenuItem* dash_run;
	dash_run = new wxMenuItem( dash_menu, DASH_RUN_ID, wxString( wxT("&Run") ) , wxT("Run Dash analysis"), wxITEM_NORMAL );
	dash_menu->Append( dash_run );
	
	menu_bar->Append( dash_menu, wxT("Dash") ); 
	
	help_menu = new wxMenu();
	wxMenuItem* help_manual;
	help_manual = new wxMenuItem( help_menu, HELP_MANUAL_ID, wxString( wxT("&Manual...") ) , wxT("View documentation"), wxITEM_NORMAL );
	help_menu->Append( help_manual );
	
	wxMenuItem* help_about;
	help_about = new wxMenuItem( help_menu, HELP_ABOUT_ID, wxString( wxT("&About...") ) , wxT("About this program"), wxITEM_NORMAL );
	help_menu->Append( help_about );
	
	menu_bar->Append( help_menu, wxT("Help") ); 
	
	this->SetMenuBar( menu_bar );
	
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxVERTICAL );
	
	log_ctrl = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxTE_MULTILINE|wxTE_READONLY );
	bSizer3->Add( log_ctrl, 1, wxEXPAND|wxALL, 5 );
	
	
	this->SetSizer( bSizer3 );
	this->Layout();
	status_bar = this->CreateStatusBar( 1, wxST_SIZEGRIP, wxID_ANY );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( open_dash->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( DashFBUI::on_open_dash ) );
	this->Connect( open_amber->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( DashFBUI::on_open_amber ) );
	this->Connect( file_quit->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( DashFBUI::on_quit ) );
	this->Connect( dash_options->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( DashFBUI::on_options ) );
	this->Connect( dash_run->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( DashFBUI::on_run ) );
	this->Connect( help_manual->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( DashFBUI::on_manual ) );
	this->Connect( help_about->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( DashFBUI::on_about ) );
}

DashFBUI::~DashFBUI()
{
	// Disconnect Events
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( DashFBUI::on_open_dash ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( DashFBUI::on_open_amber ) );
	this->Disconnect( wxID_EXIT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( DashFBUI::on_quit ) );
	this->Disconnect( DASH_OPTIONS_ID, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( DashFBUI::on_options ) );
	this->Disconnect( DASH_RUN_ID, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( DashFBUI::on_run ) );
	this->Disconnect( HELP_MANUAL_ID, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( DashFBUI::on_manual ) );
	this->Disconnect( HELP_ABOUT_ID, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( DashFBUI::on_about ) );
	
}

DashOptionsDialogFBUI::DashOptionsDialogFBUI( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	wxFlexGridSizer* fgSizer2;
	fgSizer2 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer2->SetFlexibleDirection( wxBOTH );
	fgSizer2->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText19 = new wxStaticText( this, wxID_ANY, wxT("Data:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText19->Wrap( -1 );
	fgSizer2->Add( m_staticText19, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxString vars_choiceChoices[] = { wxT("Angles"), wxT("Distances") };
	int vars_choiceNChoices = sizeof( vars_choiceChoices ) / sizeof( wxString );
	vars_choice = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, vars_choiceNChoices, vars_choiceChoices, 0 );
	vars_choice->SetSelection( 0 );
	fgSizer2->Add( vars_choice, 0, wxALL, 5 );
	
	m_staticText3 = new wxStaticText( this, wxID_ANY, wxT("Window size:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText3->Wrap( -1 );
	fgSizer2->Add( m_staticText3, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxALL, 5 );
	
	window_ctrl = new wxSpinCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 1, 100, 0 );
	fgSizer2->Add( window_ctrl, 0, wxALL, 5 );
	
	m_staticText4 = new wxStaticText( this, wxID_ANY, wxT("Bin size:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText4->Wrap( -1 );
	fgSizer2->Add( m_staticText4, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	binsize_ctrl = new wxSpinCtrlDouble( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 10, 0, 0.1 );
	fgSizer2->Add( binsize_ctrl, 0, wxALL, 5 );
	
	m_staticText5 = new wxStaticText( this, wxID_ANY, wxT("Run length:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText5->Wrap( -1 );
	fgSizer2->Add( m_staticText5, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	runlen_ctrl = new wxSpinCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 100, 0 );
	fgSizer2->Add( runlen_ctrl, 0, wxALL, 5 );
	
	m_staticText6 = new wxStaticText( this, wxID_ANY, wxT("Fmax:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText6->Wrap( -1 );
	fgSizer2->Add( m_staticText6, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	fmax_ctrl = new wxSpinCtrlDouble( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 10, 0, 0.1 );
	fgSizer2->Add( fmax_ctrl, 0, wxALL, 5 );
	
	m_staticText7 = new wxStaticText( this, wxID_ANY, wxT("Smin:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText7->Wrap( -1 );
	fgSizer2->Add( m_staticText7, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	smin_ctrl = new wxSpinCtrlDouble( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 180, 0, 0.1 );
	fgSizer2->Add( smin_ctrl, 0, wxALL, 5 );
	
	m_staticText1 = new wxStaticText( this, wxID_ANY, wxT("Bout length:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	fgSizer2->Add( m_staticText1, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	boutlen_ctrl = new wxSpinCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 100, 0 );
	boutlen_ctrl->SetToolTip( wxT("Bout length") );
	
	fgSizer2->Add( boutlen_ctrl, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText2 = new wxStaticText( this, wxID_ANY, wxT("Smoothing level:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	fgSizer2->Add( m_staticText2, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	smooth_ctrl = new wxSpinCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 100, 0 );
	fgSizer2->Add( smooth_ctrl, 0, wxALL, 5 );
	
	m_staticText10 = new wxStaticText( this, wxID_ANY, wxT("Roughening level:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText10->Wrap( -1 );
	fgSizer2->Add( m_staticText10, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	rough_ctrl = new wxSpinCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 100, 0 );
	fgSizer2->Add( rough_ctrl, 0, wxALL, 5 );
	
	m_staticText18 = new wxStaticText( this, wxID_ANY, wxT("Repex fraction:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText18->Wrap( -1 );
	fgSizer2->Add( m_staticText18, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	repex_fraction_ctrl = new wxSpinCtrlDouble( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 1, 0.010000, 0.001 );
	fgSizer2->Add( repex_fraction_ctrl, 0, wxALL, 5 );
	
	m_staticText20 = new wxStaticText( this, wxID_ANY, wxT("Timestep (ps):"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText20->Wrap( -1 );
	fgSizer2->Add( m_staticText20, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	timestep_ctrl = new wxSpinCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 1, 1000000, 1 );
	fgSizer2->Add( timestep_ctrl, 0, wxALL, 5 );
	
	
	bSizer1->Add( fgSizer2, 0, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	wxBoxSizer* bSizer13;
	bSizer13 = new wxBoxSizer( wxVERTICAL );
	
	repex_chkbox = new wxCheckBox( this, wxID_ANY, wxT("Replica exchange trajectory"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer13->Add( repex_chkbox, 0, wxALL|wxEXPAND, 5 );
	
	pca_chkbox = new wxCheckBox( this, wxID_ANY, wxT("Calculate Principal Components"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer13->Add( pca_chkbox, 0, wxALL|wxEXPAND, 5 );
	
	pca_autoscale_chkbox = new wxCheckBox( this, wxID_ANY, wxT("Autoscale Principal Components"), wxDefaultPosition, wxDefaultSize, 0 );
	pca_autoscale_chkbox->SetValue(true); 
	pca_autoscale_chkbox->Enable( false );
	
	bSizer13->Add( pca_autoscale_chkbox, 0, wxALL|wxEXPAND, 5 );
	
	
	bSizer1->Add( bSizer13, 0, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxHORIZONTAL );
	
	cancel_btn = new wxButton( this, wxID_CANCEL, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( cancel_btn, 0, wxALL, 5 );
	
	default_btn = new wxButton( this, wxID_ANY, wxT("Defaults"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( default_btn, 0, wxALL, 5 );
	
	ok_btn = new wxButton( this, wxID_OK, wxT("OK"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( ok_btn, 0, wxALL, 5 );
	
	
	bSizer1->Add( bSizer2, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );
	
	
	this->SetSizer( bSizer1 );
	this->Layout();
	bSizer1->Fit( this );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	vars_choice->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( DashOptionsDialogFBUI::on_vars_choice ), NULL, this );
	pca_chkbox->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( DashOptionsDialogFBUI::on_pca_chkbox ), NULL, this );
	default_btn->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DashOptionsDialogFBUI::on_defaults_btn ), NULL, this );
}

DashOptionsDialogFBUI::~DashOptionsDialogFBUI()
{
	// Disconnect Events
	vars_choice->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( DashOptionsDialogFBUI::on_vars_choice ), NULL, this );
	pca_chkbox->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( DashOptionsDialogFBUI::on_pca_chkbox ), NULL, this );
	default_btn->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DashOptionsDialogFBUI::on_defaults_btn ), NULL, this );
	
}

ViewerFBUI::ViewerFBUI( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( 400,300 ), wxDefaultSize );
	
	menu_bar = new wxMenuBar( 0 );
	file_menu = new wxMenu();
	file_save = new wxMenu();
	wxMenuItem* file_saveItem = new wxMenuItem( file_menu, wxID_ANY, wxT("Save"), wxEmptyString, wxITEM_NORMAL, file_save );
	wxMenuItem* save_dash_output;
	save_dash_output = new wxMenuItem( file_save, wxID_ANY, wxString( wxT("Output file...") ) , wxEmptyString, wxITEM_NORMAL );
	file_save->Append( save_dash_output );
	
	wxMenuItem* save_traj_png;
	save_traj_png = new wxMenuItem( file_save, wxID_ANY, wxString( wxT("Trajectory plot...") ) , wxEmptyString, wxITEM_NORMAL );
	file_save->Append( save_traj_png );
	
	wxMenuItem* save_freq_png;
	save_freq_png = new wxMenuItem( file_save, wxID_ANY, wxString( wxT("Frequency plot...") ) , wxEmptyString, wxITEM_NORMAL );
	file_save->Append( save_freq_png );
	
	wxMenuItem* save_sim_png;
	save_sim_png = new wxMenuItem( file_save, wxID_ANY, wxString( wxT("Similarity matrix...") ) , wxEmptyString, wxITEM_NORMAL );
	file_save->Append( save_sim_png );
	save_sim_png->Enable( false );
	
	wxMenuItem* save_torhist_png;
	save_torhist_png = new wxMenuItem( file_save, wxID_ANY, wxString( wxT("Torsion histograms...") ) , wxEmptyString, wxITEM_NORMAL );
	file_save->Append( save_torhist_png );
	save_torhist_png->Enable( false );
	
	wxMenuItem* save_scree_png;
	save_scree_png = new wxMenuItem( file_save, wxID_ANY, wxString( wxT("Scree plot...") ) , wxEmptyString, wxITEM_NORMAL );
	file_save->Append( save_scree_png );
	save_scree_png->Enable( false );
	
	wxMenuItem* save_pca_png;
	save_pca_png = new wxMenuItem( file_save, wxID_ANY, wxString( wxT("PCA plot...") ) , wxEmptyString, wxITEM_NORMAL );
	file_save->Append( save_pca_png );
	save_pca_png->Enable( false );
	
	wxMenuItem* save_snapshots;
	save_snapshots = new wxMenuItem( file_save, wxID_ANY, wxString( wxT("PDB snapshots...") ) , wxEmptyString, wxITEM_NORMAL );
	file_save->Append( save_snapshots );
	save_snapshots->Enable( false );
	
	file_menu->Append( file_saveItem );
	
	wxMenuItem* file_close;
	file_close = new wxMenuItem( file_menu, wxID_CLOSE, wxString( wxT("Close") ) , wxT("Close window"), wxITEM_NORMAL );
	file_menu->Append( file_close );
	
	menu_bar->Append( file_menu, wxT("&File") ); 
	
	options_menu = new wxMenu();
	wxMenuItem* grid_options;
	grid_options = new wxMenuItem( options_menu, wxID_ANY, wxString( wxT("Torsion Histogram &Grid...") ) , wxEmptyString, wxITEM_NORMAL );
	options_menu->Append( grid_options );
	
	pca_options = new wxMenuItem( options_menu, wxID_ANY, wxString( wxT("PCA Plot...") ) , wxEmptyString, wxITEM_NORMAL );
	options_menu->Append( pca_options );
	
	menu_bar->Append( options_menu, wxT("&Options") ); 
	
	this->SetMenuBar( menu_bar );
	
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxVERTICAL );
	
	notebook = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	
	bSizer4->Add( notebook, 1, wxEXPAND | wxALL, 5 );
	
	
	this->SetSizer( bSizer4 );
	this->Layout();
	status_bar = this->CreateStatusBar( 1, wxST_SIZEGRIP, wxID_ANY );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( save_dash_output->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( ViewerFBUI::on_save_dash_output ) );
	this->Connect( save_traj_png->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( ViewerFBUI::on_save_traj_png ) );
	this->Connect( save_freq_png->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( ViewerFBUI::on_save_freq_png ) );
	this->Connect( save_sim_png->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( ViewerFBUI::on_save_sim_png ) );
	this->Connect( save_torhist_png->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( ViewerFBUI::on_save_torhist_png ) );
	this->Connect( save_scree_png->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( ViewerFBUI::on_save_scree_png ) );
	this->Connect( save_pca_png->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( ViewerFBUI::on_save_pca_png ) );
	this->Connect( save_snapshots->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( ViewerFBUI::on_save_snapshots ) );
	this->Connect( file_close->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( ViewerFBUI::on_close ) );
	this->Connect( grid_options->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( ViewerFBUI::on_grid_options ) );
	this->Connect( pca_options->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( ViewerFBUI::on_pca_options ) );
	notebook->Connect( wxEVT_COMMAND_NOTEBOOK_PAGE_CHANGED, wxNotebookEventHandler( ViewerFBUI::on_page_changed ), NULL, this );
}

ViewerFBUI::~ViewerFBUI()
{
	// Disconnect Events
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( ViewerFBUI::on_save_dash_output ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( ViewerFBUI::on_save_traj_png ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( ViewerFBUI::on_save_freq_png ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( ViewerFBUI::on_save_sim_png ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( ViewerFBUI::on_save_torhist_png ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( ViewerFBUI::on_save_scree_png ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( ViewerFBUI::on_save_pca_png ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( ViewerFBUI::on_save_snapshots ) );
	this->Disconnect( wxID_CLOSE, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( ViewerFBUI::on_close ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( ViewerFBUI::on_grid_options ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( ViewerFBUI::on_pca_options ) );
	notebook->Disconnect( wxEVT_COMMAND_NOTEBOOK_PAGE_CHANGED, wxNotebookEventHandler( ViewerFBUI::on_page_changed ), NULL, this );
	
}

SummaryPanelFBUI::SummaryPanelFBUI( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) : wxPanel( parent, id, pos, size, style )
{
	this->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOWFRAME ) );
	
	wxBoxSizer* bSizer9;
	bSizer9 = new wxBoxSizer( wxVERTICAL );
	
	text_ctrl = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxTE_MULTILINE|wxTE_READONLY );
	bSizer9->Add( text_ctrl, 1, wxALL|wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer9 );
	this->Layout();
}

SummaryPanelFBUI::~SummaryPanelFBUI()
{
}

TrajectoryPanelFBUI::TrajectoryPanelFBUI( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name ) : wxPanel( parent, id, pos, size, style, name )
{
	this->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOWFRAME ) );
	
	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer( wxVERTICAL );
	
	main_panel = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	bSizer7->Add( main_panel, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText15 = new wxStaticText( this, wxID_ANY, wxT("Zoom:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText15->Wrap( -1 );
	bSizer5->Add( m_staticText15, 0, wxALIGN_CENTER_VERTICAL|wxTOP|wxBOTTOM|wxLEFT, 5 );
	
	slider = new wxSlider( this, wxID_ANY, 0, 0, 100, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL );
	slider->SetMinSize( wxSize( 100,-1 ) );
	
	bSizer5->Add( slider, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer7->Add( bSizer5, 0, wxALL, 5 );
	
	
	this->SetSizer( bSizer7 );
	this->Layout();
	
	// Connect Events
	slider->Connect( wxEVT_SCROLL_TOP, wxScrollEventHandler( TrajectoryPanelFBUI::on_zoom ), NULL, this );
	slider->Connect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( TrajectoryPanelFBUI::on_zoom ), NULL, this );
	slider->Connect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( TrajectoryPanelFBUI::on_zoom ), NULL, this );
	slider->Connect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( TrajectoryPanelFBUI::on_zoom ), NULL, this );
	slider->Connect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( TrajectoryPanelFBUI::on_zoom ), NULL, this );
	slider->Connect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( TrajectoryPanelFBUI::on_zoom ), NULL, this );
	slider->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( TrajectoryPanelFBUI::on_zoom ), NULL, this );
	slider->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( TrajectoryPanelFBUI::on_zoom ), NULL, this );
	slider->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( TrajectoryPanelFBUI::on_zoom ), NULL, this );
}

TrajectoryPanelFBUI::~TrajectoryPanelFBUI()
{
	// Disconnect Events
	slider->Disconnect( wxEVT_SCROLL_TOP, wxScrollEventHandler( TrajectoryPanelFBUI::on_zoom ), NULL, this );
	slider->Disconnect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( TrajectoryPanelFBUI::on_zoom ), NULL, this );
	slider->Disconnect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( TrajectoryPanelFBUI::on_zoom ), NULL, this );
	slider->Disconnect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( TrajectoryPanelFBUI::on_zoom ), NULL, this );
	slider->Disconnect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( TrajectoryPanelFBUI::on_zoom ), NULL, this );
	slider->Disconnect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( TrajectoryPanelFBUI::on_zoom ), NULL, this );
	slider->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( TrajectoryPanelFBUI::on_zoom ), NULL, this );
	slider->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( TrajectoryPanelFBUI::on_zoom ), NULL, this );
	slider->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( TrajectoryPanelFBUI::on_zoom ), NULL, this );
	
}

ManualFBUI::ManualFBUI( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	menu_bar = new wxMenuBar( 0 );
	file_menu = new wxMenu();
	wxMenuItem* file_close;
	file_close = new wxMenuItem( file_menu, wxID_CLOSE, wxString( wxEmptyString ) , wxT("Close window"), wxITEM_NORMAL );
	file_menu->Append( file_close );
	
	menu_bar->Append( file_menu, wxT("&File") ); 
	
	this->SetMenuBar( menu_bar );
	
	wxBoxSizer* bSizer13;
	bSizer13 = new wxBoxSizer( wxVERTICAL );
	
	html_window = new wxHtmlWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHW_SCROLLBAR_AUTO );
	bSizer13->Add( html_window, 1, wxALL|wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer13 );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( file_close->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( ManualFBUI::on_close ) );
}

ManualFBUI::~ManualFBUI()
{
	// Disconnect Events
	this->Disconnect( wxID_CLOSE, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( ManualFBUI::on_close ) );
	
}

GridOptionsDialogFBUI::GridOptionsDialogFBUI( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer14;
	bSizer14 = new wxBoxSizer( wxVERTICAL );
	
	wxFlexGridSizer* fgSizer2;
	fgSizer2 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer2->SetFlexibleDirection( wxBOTH );
	fgSizer2->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText11 = new wxStaticText( this, wxID_ANY, wxT("Rows:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText11->Wrap( -1 );
	fgSizer2->Add( m_staticText11, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	rows_ctrl = new wxSpinCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 1, 10, 0 );
	fgSizer2->Add( rows_ctrl, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText12 = new wxStaticText( this, wxID_ANY, wxT("Columns:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText12->Wrap( -1 );
	fgSizer2->Add( m_staticText12, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	cols_ctrl = new wxSpinCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 1, 10, 0 );
	fgSizer2->Add( cols_ctrl, 0, wxALL, 5 );
	
	
	bSizer14->Add( fgSizer2, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );
	
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxHORIZONTAL );
	
	cancel_btn = new wxButton( this, wxID_CANCEL, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( cancel_btn, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	ok_btn = new wxButton( this, wxID_OK, wxT("OK"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( ok_btn, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer14->Add( bSizer2, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );
	
	
	this->SetSizer( bSizer14 );
	this->Layout();
	bSizer14->Fit( this );
	
	this->Centre( wxBOTH );
}

GridOptionsDialogFBUI::~GridOptionsDialogFBUI()
{
}

PCAOptionsDialogFBUI::PCAOptionsDialogFBUI( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer15;
	bSizer15 = new wxBoxSizer( wxVERTICAL );
	
	wxFlexGridSizer* fgSizer5;
	fgSizer5 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer5->SetFlexibleDirection( wxBOTH );
	fgSizer5->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	wxString dim_ctrlChoices[] = { wxT("2"), wxT("3") };
	int dim_ctrlNChoices = sizeof( dim_ctrlChoices ) / sizeof( wxString );
	dim_ctrl = new wxRadioBox( this, wxID_ANY, wxT("Dimension"), wxDefaultPosition, wxDefaultSize, dim_ctrlNChoices, dim_ctrlChoices, 1, wxRA_SPECIFY_COLS );
	dim_ctrl->SetSelection( 1 );
	fgSizer5->Add( dim_ctrl, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	wxStaticBoxSizer* sbSizer1;
	sbSizer1 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("PCs") ), wxVERTICAL );
	
	wxFlexGridSizer* fgSizer6;
	fgSizer6 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer6->SetFlexibleDirection( wxBOTH );
	fgSizer6->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText16 = new wxStaticText( sbSizer1->GetStaticBox(), wxID_ANY, wxT("X :"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText16->Wrap( -1 );
	fgSizer6->Add( m_staticText16, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxTOP|wxBOTTOM|wxLEFT, 5 );
	
	wxString pcx_ctrlChoices[] = { wxT(" PC1"), wxT(" PC2"), wxT(" PC3") };
	int pcx_ctrlNChoices = sizeof( pcx_ctrlChoices ) / sizeof( wxString );
	pcx_ctrl = new wxChoice( sbSizer1->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, pcx_ctrlNChoices, pcx_ctrlChoices, 0 );
	pcx_ctrl->SetSelection( 0 );
	fgSizer6->Add( pcx_ctrl, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );
	
	m_staticText17 = new wxStaticText( sbSizer1->GetStaticBox(), wxID_ANY, wxT("Y :"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText17->Wrap( -1 );
	fgSizer6->Add( m_staticText17, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxTOP|wxBOTTOM|wxLEFT, 5 );
	
	wxString pcy_ctrlChoices[] = { wxT(" PC1 "), wxT(" PC2 "), wxT(" PC3 ") };
	int pcy_ctrlNChoices = sizeof( pcy_ctrlChoices ) / sizeof( wxString );
	pcy_ctrl = new wxChoice( sbSizer1->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, pcy_ctrlNChoices, pcy_ctrlChoices, 0 );
	pcy_ctrl->SetSelection( 1 );
	fgSizer6->Add( pcy_ctrl, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_staticText18 = new wxStaticText( sbSizer1->GetStaticBox(), wxID_ANY, wxT("Z :"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText18->Wrap( -1 );
	fgSizer6->Add( m_staticText18, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxTOP|wxBOTTOM|wxLEFT, 5 );
	
	wxString pcz_ctrlChoices[] = { wxT(" PC1 "), wxT(" PC2 "), wxT(" PC3 ") };
	int pcz_ctrlNChoices = sizeof( pcz_ctrlChoices ) / sizeof( wxString );
	pcz_ctrl = new wxChoice( sbSizer1->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, pcz_ctrlNChoices, pcz_ctrlChoices, 0 );
	pcz_ctrl->SetSelection( 2 );
	fgSizer6->Add( pcz_ctrl, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	sbSizer1->Add( fgSizer6, 1, wxEXPAND|wxALL, 5 );
	
	
	fgSizer5->Add( sbSizer1, 1, wxALL, 5 );
	
	
	bSizer15->Add( fgSizer5, 1, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizer16;
	bSizer16 = new wxBoxSizer( wxHORIZONTAL );
	
	cancel_btn = new wxButton( this, wxID_CANCEL, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer16->Add( cancel_btn, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	ok_btn = new wxButton( this, wxID_OK, wxT("OK"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer16->Add( ok_btn, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer15->Add( bSizer16, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );
	
	
	this->SetSizer( bSizer15 );
	this->Layout();
	bSizer15->Fit( this );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	dim_ctrl->Connect( wxEVT_COMMAND_RADIOBOX_SELECTED, wxCommandEventHandler( PCAOptionsDialogFBUI::on_dim_ctrl ), NULL, this );
	pcx_ctrl->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( PCAOptionsDialogFBUI::on_pcx_ctrl ), NULL, this );
	pcy_ctrl->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( PCAOptionsDialogFBUI::on_pcy_ctrl ), NULL, this );
	pcz_ctrl->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( PCAOptionsDialogFBUI::on_pcz_ctrl ), NULL, this );
}

PCAOptionsDialogFBUI::~PCAOptionsDialogFBUI()
{
	// Disconnect Events
	dim_ctrl->Disconnect( wxEVT_COMMAND_RADIOBOX_SELECTED, wxCommandEventHandler( PCAOptionsDialogFBUI::on_dim_ctrl ), NULL, this );
	pcx_ctrl->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( PCAOptionsDialogFBUI::on_pcx_ctrl ), NULL, this );
	pcy_ctrl->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( PCAOptionsDialogFBUI::on_pcy_ctrl ), NULL, this );
	pcz_ctrl->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( PCAOptionsDialogFBUI::on_pcz_ctrl ), NULL, this );
	
}

TrajectoryOptionsDialogFBUI::TrajectoryOptionsDialogFBUI( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer13;
	bSizer13 = new wxBoxSizer( wxVERTICAL );
	
	wxFlexGridSizer* fgSizer3;
	fgSizer3 = new wxFlexGridSizer( 0, 4, 0, 0 );
	fgSizer3->SetFlexibleDirection( wxBOTH );
	fgSizer3->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText13 = new wxStaticText( this, wxID_ANY, wxT("Frames:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText13->Wrap( -1 );
	fgSizer3->Add( m_staticText13, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	first_frame_ctrl = new wxSpinCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 1, 10, 0 );
	fgSizer3->Add( first_frame_ctrl, 0, wxALL, 5 );
	
	m_staticText14 = new wxStaticText( this, wxID_ANY, wxT("to"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText14->Wrap( -1 );
	fgSizer3->Add( m_staticText14, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	last_frame_ctrl = new wxSpinCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 1, 10, 0 );
	fgSizer3->Add( last_frame_ctrl, 0, wxALL, 5 );
	
	
	bSizer13->Add( fgSizer3, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxHORIZONTAL );
	
	cancel_btn = new wxButton( this, wxID_CANCEL, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( cancel_btn, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	ok_btn = new wxButton( this, wxID_OK, wxT("OK"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( ok_btn, 1, wxALL, 5 );
	
	
	bSizer13->Add( bSizer2, 1, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	this->SetSizer( bSizer13 );
	this->Layout();
	bSizer13->Fit( this );
	
	this->Centre( wxBOTH );
}

TrajectoryOptionsDialogFBUI::~TrajectoryOptionsDialogFBUI()
{
}

BoutPanelFBUI::BoutPanelFBUI( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) : wxPanel( parent, id, pos, size, style )
{
	wxBoxSizer* bSizer17;
	bSizer17 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer18;
	bSizer18 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText21 = new wxStaticText( this, wxID_ANY, wxT("Units:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText21->Wrap( -1 );
	bSizer18->Add( m_staticText21, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxString units_ctrlChoices[] = { wxT("Frames"), wxT("Times (ps)") };
	int units_ctrlNChoices = sizeof( units_ctrlChoices ) / sizeof( wxString );
	units_ctrl = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, units_ctrlNChoices, units_ctrlChoices, 0 );
	units_ctrl->SetSelection( 0 );
	bSizer18->Add( units_ctrl, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer17->Add( bSizer18, 0, 0, 5 );
	
	grid = new wxGrid( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	
	// Grid
	grid->CreateGrid( 0, 0 );
	grid->EnableEditing( true );
	grid->EnableGridLines( true );
	grid->EnableDragGridSize( false );
	grid->SetMargins( 0, 0 );
	
	// Columns
	grid->EnableDragColMove( false );
	grid->EnableDragColSize( true );
	grid->SetColLabelSize( 30 );
	grid->SetColLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );
	
	// Rows
	grid->EnableDragRowSize( true );
	grid->SetRowLabelSize( 80 );
	grid->SetRowLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );
	
	// Label Appearance
	
	// Cell Defaults
	grid->SetDefaultCellAlignment( wxALIGN_LEFT, wxALIGN_TOP );
	bSizer17->Add( grid, 0, wxALL, 5 );
	
	
	this->SetSizer( bSizer17 );
	this->Layout();
	
	// Connect Events
	units_ctrl->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( BoutPanelFBUI::on_units_ctrl ), NULL, this );
}

BoutPanelFBUI::~BoutPanelFBUI()
{
	// Disconnect Events
	units_ctrl->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( BoutPanelFBUI::on_units_ctrl ), NULL, this );
	
}

SimilarityPanelFBUI::SimilarityPanelFBUI( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) : wxPanel( parent, id, pos, size, style )
{
	wxBoxSizer* bSizer18;
	bSizer18 = new wxBoxSizer( wxVERTICAL );
	
	notebook = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	circsim_panel = new wxPanel( notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer19;
	bSizer19 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer20;
	bSizer20 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText21 = new wxStaticText( circsim_panel, wxID_ANY, wxT("Circular similarity: low (0)"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText21->Wrap( -1 );
	bSizer20->Add( m_staticText21, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	circsim_legend = new wxGrid( circsim_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	
	// Grid
	circsim_legend->CreateGrid( 0, 0 );
	circsim_legend->EnableEditing( false );
	circsim_legend->EnableGridLines( false );
	circsim_legend->EnableDragGridSize( false );
	circsim_legend->SetMargins( 0, 0 );
	
	// Columns
	circsim_legend->EnableDragColMove( false );
	circsim_legend->EnableDragColSize( false );
	circsim_legend->SetColLabelSize( 0 );
	circsim_legend->SetColLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );
	
	// Rows
	circsim_legend->EnableDragRowSize( false );
	circsim_legend->SetRowLabelSize( 0 );
	circsim_legend->SetRowLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );
	
	// Label Appearance
	
	// Cell Defaults
	circsim_legend->SetDefaultCellAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );
	bSizer20->Add( circsim_legend, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText22 = new wxStaticText( circsim_panel, wxID_ANY, wxT("high (1)"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText22->Wrap( -1 );
	bSizer20->Add( m_staticText22, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer19->Add( bSizer20, 0, 0, 5 );
	
	circsim_grid = new wxGrid( circsim_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	
	// Grid
	circsim_grid->CreateGrid( 0, 0 );
	circsim_grid->EnableEditing( false );
	circsim_grid->EnableGridLines( false );
	circsim_grid->EnableDragGridSize( false );
	circsim_grid->SetMargins( 0, 0 );
	
	// Columns
	circsim_grid->EnableDragColMove( false );
	circsim_grid->EnableDragColSize( false );
	circsim_grid->SetColLabelSize( 30 );
	circsim_grid->SetColLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );
	
	// Rows
	circsim_grid->EnableDragRowSize( false );
	circsim_grid->SetRowLabelSize( 80 );
	circsim_grid->SetRowLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );
	
	// Label Appearance
	
	// Cell Defaults
	circsim_grid->SetDefaultCellAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );
	bSizer19->Add( circsim_grid, 1, wxALL, 5 );
	
	
	circsim_panel->SetSizer( bSizer19 );
	circsim_panel->Layout();
	bSizer19->Fit( circsim_panel );
	notebook->AddPage( circsim_panel, wxT("Circular"), true );
	cosim_panel = new wxPanel( notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer21;
	bSizer21 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer22;
	bSizer22 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText23 = new wxStaticText( cosim_panel, wxID_ANY, wxT("Cosine similarity: low (-1)"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText23->Wrap( -1 );
	bSizer22->Add( m_staticText23, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	cosim_legend = new wxGrid( cosim_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	
	// Grid
	cosim_legend->CreateGrid( 0, 0 );
	cosim_legend->EnableEditing( false );
	cosim_legend->EnableGridLines( false );
	cosim_legend->EnableDragGridSize( false );
	cosim_legend->SetMargins( 0, 0 );
	
	// Columns
	cosim_legend->EnableDragColMove( false );
	cosim_legend->EnableDragColSize( false );
	cosim_legend->SetColLabelSize( 0 );
	cosim_legend->SetColLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );
	
	// Rows
	cosim_legend->EnableDragRowSize( false );
	cosim_legend->SetRowLabelSize( 0 );
	cosim_legend->SetRowLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );
	
	// Label Appearance
	
	// Cell Defaults
	cosim_legend->SetDefaultCellAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );
	bSizer22->Add( cosim_legend, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText24 = new wxStaticText( cosim_panel, wxID_ANY, wxT("high (+1)"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText24->Wrap( -1 );
	bSizer22->Add( m_staticText24, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer21->Add( bSizer22, 0, 0, 5 );
	
	cosim_grid = new wxGrid( cosim_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	
	// Grid
	cosim_grid->CreateGrid( 0, 0 );
	cosim_grid->EnableEditing( false );
	cosim_grid->EnableGridLines( false );
	cosim_grid->EnableDragGridSize( false );
	cosim_grid->SetMargins( 0, 0 );
	
	// Columns
	cosim_grid->EnableDragColMove( false );
	cosim_grid->EnableDragColSize( false );
	cosim_grid->SetColLabelSize( 30 );
	cosim_grid->SetColLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );
	
	// Rows
	cosim_grid->EnableDragRowSize( false );
	cosim_grid->SetRowLabelSize( 80 );
	cosim_grid->SetRowLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );
	
	// Label Appearance
	
	// Cell Defaults
	cosim_grid->SetDefaultCellAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );
	bSizer21->Add( cosim_grid, 1, wxALL, 5 );
	
	
	cosim_panel->SetSizer( bSizer21 );
	cosim_panel->Layout();
	bSizer21->Fit( cosim_panel );
	notebook->AddPage( cosim_panel, wxT("Cosine"), false );
	
	bSizer18->Add( notebook, 0, 0, 5 );
	
	
	this->SetSizer( bSizer18 );
	this->Layout();
}

SimilarityPanelFBUI::~SimilarityPanelFBUI()
{
}

AmberDialogFBUI::AmberDialogFBUI( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	amber_dialog_sizer = new wxGridBagSizer( 0, 0 );
	amber_dialog_sizer->SetFlexibleDirection( wxBOTH );
	amber_dialog_sizer->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText25 = new wxStaticText( this, wxID_ANY, wxT("Topology:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText25->Wrap( -1 );
	amber_dialog_sizer->Add( m_staticText25, wxGBPosition( 0, 0 ), wxGBSpan( 1, 1 ), wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	top_ctrl = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	top_ctrl->SetMinSize( wxSize( 200,-1 ) );
	
	amber_dialog_sizer->Add( top_ctrl, wxGBPosition( 0, 1 ), wxGBSpan( 1, 1 ), wxALL|wxEXPAND|wxALIGN_CENTER_VERTICAL, 5 );
	
	top_browse = new wxButton( this, wxID_ANY, wxT("Browse"), wxDefaultPosition, wxDefaultSize, 0 );
	amber_dialog_sizer->Add( top_browse, wxGBPosition( 0, 2 ), wxGBSpan( 1, 1 ), wxALL, 5 );
	
	m_staticText26 = new wxStaticText( this, wxID_ANY, wxT("       Trajectory:"), wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_staticText26->Wrap( -1 );
	amber_dialog_sizer->Add( m_staticText26, wxGBPosition( 1, 0 ), wxGBSpan( 1, 1 ), wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	trj_ctrl = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	trj_ctrl->SetMinSize( wxSize( 200,-1 ) );
	
	amber_dialog_sizer->Add( trj_ctrl, wxGBPosition( 1, 1 ), wxGBSpan( 1, 1 ), wxALL|wxEXPAND|wxALIGN_CENTER_VERTICAL, 5 );
	
	trj_browse = new wxButton( this, wxID_ANY, wxT("Browse"), wxDefaultPosition, wxDefaultSize, 0 );
	amber_dialog_sizer->Add( trj_browse, wxGBPosition( 1, 2 ), wxGBSpan( 1, 1 ), wxALL, 5 );
	
	m_staticText29 = new wxStaticText( this, wxID_ANY, wxT("Residues:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText29->Wrap( -1 );
	amber_dialog_sizer->Add( m_staticText29, wxGBPosition( 2, 0 ), wxGBSpan( 1, 1 ), wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	res_ctrl = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	amber_dialog_sizer->Add( res_ctrl, wxGBPosition( 2, 1 ), wxGBSpan( 1, 1 ), wxALL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	m_staticText30 = new wxStaticText( this, wxID_ANY, wxT("Dihedrals:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText30->Wrap( -1 );
	amber_dialog_sizer->Add( m_staticText30, wxGBPosition( 3, 0 ), wxGBSpan( 1, 1 ), wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxBoxSizer* bSizer24;
	bSizer24 = new wxBoxSizer( wxHORIZONTAL );
	
	phi_ctrl = new wxCheckBox( this, wxID_ANY, wxT("phi"), wxDefaultPosition, wxDefaultSize, 0 );
	phi_ctrl->SetValue(true); 
	bSizer24->Add( phi_ctrl, 0, wxALL, 5 );
	
	psi_ctrl = new wxCheckBox( this, wxID_ANY, wxT("psi"), wxDefaultPosition, wxDefaultSize, 0 );
	psi_ctrl->SetValue(true); 
	bSizer24->Add( psi_ctrl, 0, wxALL, 5 );
	
	chi_ctrl = new wxCheckBox( this, wxID_ANY, wxT("chi"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer24->Add( chi_ctrl, 0, wxALL, 5 );
	
	omega_ctrl = new wxCheckBox( this, wxID_ANY, wxT("omega"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer24->Add( omega_ctrl, 0, wxALL, 5 );
	
	
	amber_dialog_sizer->Add( bSizer24, wxGBPosition( 3, 1 ), wxGBSpan( 1, 1 ), wxALL|wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer4;
	sbSizer4 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Save Intermediate Files") ), wxVERTICAL );
	
	wxString tmpfile_ctrlChoices[] = { wxT("mdash input file"), wxT("cpptraj input file"), wxT("cpptraj output file") };
	int tmpfile_ctrlNChoices = sizeof( tmpfile_ctrlChoices ) / sizeof( wxString );
	tmpfile_ctrl = new wxCheckListBox( sbSizer4->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, tmpfile_ctrlNChoices, tmpfile_ctrlChoices, 0 );
	sbSizer4->Add( tmpfile_ctrl, 0, wxALL, 5 );
	
	
	amber_dialog_sizer->Add( sbSizer4, wxGBPosition( 4, 1 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );
	
	m_sdbSizer1 = new wxStdDialogButtonSizer();
	m_sdbSizer1OK = new wxButton( this, wxID_OK );
	m_sdbSizer1->AddButton( m_sdbSizer1OK );
	m_sdbSizer1Cancel = new wxButton( this, wxID_CANCEL );
	m_sdbSizer1->AddButton( m_sdbSizer1Cancel );
	m_sdbSizer1->Realize();
	
	amber_dialog_sizer->Add( m_sdbSizer1, wxGBPosition( 5, 0 ), wxGBSpan( 1, 3 ), wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	
	this->SetSizer( amber_dialog_sizer );
	this->Layout();
	amber_dialog_sizer->Fit( this );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	top_browse->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AmberDialogFBUI::on_top_browse ), NULL, this );
	trj_browse->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AmberDialogFBUI::on_trj_browse ), NULL, this );
	tmpfile_ctrl->Connect( wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler( AmberDialogFBUI::on_save_tmpfiles ), NULL, this );
}

AmberDialogFBUI::~AmberDialogFBUI()
{
	// Disconnect Events
	top_browse->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AmberDialogFBUI::on_top_browse ), NULL, this );
	trj_browse->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AmberDialogFBUI::on_trj_browse ), NULL, this );
	tmpfile_ctrl->Disconnect( wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler( AmberDialogFBUI::on_save_tmpfiles ), NULL, this );
	
}
