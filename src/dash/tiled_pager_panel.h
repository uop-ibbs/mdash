//  $Id: tiled_pager_panel.h 51 2015-07-20 13:55:18Z dw $
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

#ifndef DASH_TILED_PAGER_PANEL_H
#define DASH_TILED_PAGER_PANEL_H

#include "dash/tiled_pager_panel_fbui.h"

class TiledPagerPanel : public TiledPagerPanelFBUI
{
 public:
    TiledPagerPanel(int t, int r, int c, wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(500,300), long style = wxTAB_TRAVERSAL);
    ~TiledPagerPanel();

    int get_tiles() const { return tiles; }
    int get_rows() const { return rows; }
    int get_cols() const { return cols; }

    void resize(int rows, int cols);

 protected:
    int page;
    int pagemax;

    void on_next(wxCommandEvent&);
    void on_prev(wxCommandEvent&);

 private:
    int tiles;
    int rows;
    int cols;

    void enable_ctrls();

    virtual void draw_page() {}
    virtual void clear_page() {}
};

#endif // DASH_TILED_PAGER_PANEL_H
