//  $Id: palette.h 116 2017-09-21 16:19:22Z dw $
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

#ifndef DASH_PALETTE_H
#define DASH_PALETTE_H

#include <string>

static const struct PALETTE_ENTRY
{
    std::string name;
    unsigned char r, g, b;
} PALETTE[] = {
    {"WHITE", 255, 255, 255},
    {"RED", 255, 0, 0},
    {"GREEN", 0, 255, 0},
    {"YELLOW", 255, 255, 0},
    {"CYAN", 0, 255, 255},
    {"MAGENTA", 255, 0, 255},
    {"SLATE BLUE", 0, 127, 255},
    {"FOREST GREEN", 35, 142, 35},
    {"Grayish Yellow", 206, 162, 98},
    {"CADET BLUE", 95, 159, 159},
    {"Strong Purplish Pink", 246, 118, 142},
    {"PLUM", 234, 173, 234},
    {"MEDIUM AQUAMARINE", 50, 204, 153},
    {"Very Light Blue", 166, 189, 215},
    {"Vivid Yellowish Green", 147, 170, 0},
    {"MEDIUM GOLDENROD", 234, 234, 173},
    {"CORAL", 255, 127, 0},
    {"VIOLET RED", 204, 50, 153},
    {"Vivid Red", 193, 0, 32},
    {"Vivid Greenish Yellow", 244, 200, 0},
    {"PINK", 255, 192, 203},
    {"PURPLE", 176, 0, 255},
    {"Strong Yellowish Pink", 255, 122, 92},
    {"LIGHT BLUE", 191, 216, 216},
    {"GREEN YELLOW", 147, 219, 112},
    {"ORANGE RED", 255, 0, 127},
    {"PALE GREEN", 143, 188, 143},
    {"KHAKI", 159, 159, 95},
    {"LIGHT GREY", 192, 192, 192},
    {"THISTLE", 216, 191, 216},
    {"LIGHT MAGENTA", 255, 119, 255},
    {"MEDIUM FOREST GREEN", 107, 142, 35},
    {"GOLD", 204, 127, 50},
    {"WHEAT", 216, 216, 191},
    {"Vivid Yellow", 255, 179, 0},
    {"LIME GREEN", 50, 204, 50},
    {"MEDIUM TURQUOISE", 112, 219, 219},
    {"SPRING GREEN", 0, 255, 127},
    {"GOLDENROD", 219, 219, 112},
    {"YELLOW GREEN", 153, 204, 50},
    {"TURQUOISE", 173, 234, 234},
    {"AQUAMARINE", 112, 219, 147},
    {"BPINK", 255, 128, 128},
    {"ORCHID", 219, 112, 219},
    {"MEDIUM VIOLET RED", 219, 112, 147},
    {"Vivid Orange", 255, 104, 0},
    {"ORANGE", 204, 50, 50},
    {"MEDIUM SPRING GREEN", 127, 255, 0},
    {"Vivid Orange Yellow", 255, 142, 0},
    {"Vivid Reddish Orange", 241, 58, 19}
};

#endif // DASH_PALETTE_H
