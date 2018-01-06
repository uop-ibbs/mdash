//  $Id: tiled_pager_panel.cpp 51 2015-07-20 13:55:18Z dw $
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

#include "dash/tiled_pager_panel.h"

TiledPagerPanel::TiledPagerPanel(int t, int r, int c, wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
    : TiledPagerPanelFBUI(parent, id, pos, size, style), tiles(t), rows(r), cols(c)
{
    page = 1;
    pagemax = static_cast<int>(ceil(static_cast<float>(tiles/rows/cols)));

    grid_sizer->SetRows(rows);
    grid_sizer->SetCols(cols);

    enable_ctrls();
}

TiledPagerPanel::~TiledPagerPanel()
{
    clear_page();
}

void
TiledPagerPanel::resize(int r, int c)
{
    clear_page();
    rows = r;
    cols = c;
    grid_sizer->SetRows(rows);
    grid_sizer->SetCols(cols);
    pagemax = static_cast<int>(ceil(static_cast<float>(tiles/rows/cols)));
    page = 1;
    draw_page();
    enable_ctrls();
}

void
TiledPagerPanel::on_next(wxCommandEvent& WXUNUSED(event))
{
    if (page < pagemax) {
        ++page;
        clear_page();
        draw_page();
        enable_ctrls();
    }
}

void
TiledPagerPanel::on_prev(wxCommandEvent& WXUNUSED(event))
{
    if (page > 1) {
        --page;
        clear_page();
        draw_page();
        enable_ctrls();
    }
}

void
TiledPagerPanel::enable_ctrls()
{
    next_btn->Enable(page < pagemax);
    prev_btn->Enable(page > 1);
}
