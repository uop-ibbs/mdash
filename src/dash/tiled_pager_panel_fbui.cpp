///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 15 2015)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "tiled_pager_panel_fbui.h"

///////////////////////////////////////////////////////////////////////////

TiledPagerPanelFBUI::TiledPagerPanelFBUI( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) : wxPanel( parent, id, pos, size, style )
{
	wxBoxSizer* bSizer15;
	bSizer15 = new wxBoxSizer( wxVERTICAL );
	
	grid_panel = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	grid_sizer = new wxGridSizer( 0, 2, 0, 0 );
	
	
	grid_panel->SetSizer( grid_sizer );
	grid_panel->Layout();
	grid_sizer->Fit( grid_panel );
	bSizer15->Add( grid_panel, 1, wxALL|wxEXPAND, 5 );
	
	navigation_panel = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer16;
	bSizer16 = new wxBoxSizer( wxHORIZONTAL );
	
	prev_btn = new wxButton( navigation_panel, wxID_ANY, wxT("Previous"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer16->Add( prev_btn, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	next_btn = new wxButton( navigation_panel, wxID_ANY, wxT("Next"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer16->Add( next_btn, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	navigation_panel->SetSizer( bSizer16 );
	navigation_panel->Layout();
	bSizer16->Fit( navigation_panel );
	bSizer15->Add( navigation_panel, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	this->SetSizer( bSizer15 );
	this->Layout();
	
	// Connect Events
	prev_btn->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( TiledPagerPanelFBUI::on_prev ), NULL, this );
	next_btn->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( TiledPagerPanelFBUI::on_next ), NULL, this );
}

TiledPagerPanelFBUI::~TiledPagerPanelFBUI()
{
	// Disconnect Events
	prev_btn->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( TiledPagerPanelFBUI::on_prev ), NULL, this );
	next_btn->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( TiledPagerPanelFBUI::on_next ), NULL, this );
	
}
