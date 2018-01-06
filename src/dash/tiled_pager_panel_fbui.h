///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 15 2015)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __TILED_PAGER_PANEL_FBUI_H__
#define __TILED_PAGER_PANEL_FBUI_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/sizer.h>
#include <wx/gdicmn.h>
#include <wx/panel.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/button.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class TiledPagerPanelFBUI
///////////////////////////////////////////////////////////////////////////////
class TiledPagerPanelFBUI : public wxPanel 
{
	private:
	
	protected:
		wxPanel* grid_panel;
		wxGridSizer* grid_sizer;
		wxPanel* navigation_panel;
		wxButton* prev_btn;
		wxButton* next_btn;
		
		// Virtual event handlers, overide them in your derived class
		virtual void on_prev( wxCommandEvent& event ) { event.Skip(); }
		virtual void on_next( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		TiledPagerPanelFBUI( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,300 ), long style = wxTAB_TRAVERSAL ); 
		~TiledPagerPanelFBUI();
	
};

#endif //__TILED_PAGER_PANEL_FBUI_H__
