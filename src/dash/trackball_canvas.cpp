//  $Id: trackball_canvas.cpp 97 2017-03-07 10:44:39Z dw $
//
//  Copyright (C) 2016 Centre for Molecular Design, University of Portsmouth.
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

#include "dash/trackball_canvas.h"

#include <GL/glu.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <algorithm>

TrackballCanvas::TrackballCanvas(wxWindow *parent, const int *attr, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
    : wxGLCanvas(parent, id, attr, pos, size, style)
{
    model_view_ = glm::mat4(1.0f);
    rotating_ = false;

    Bind(wxEVT_LEFT_DOWN, &TrackballCanvas::on_left_down, this);
    Bind(wxEVT_LEFT_UP, &TrackballCanvas::on_left_up, this);
    Bind(wxEVT_MOTION, &TrackballCanvas::on_motion, this);
    Bind(wxEVT_KEY_DOWN, &TrackballCanvas::on_key_down, this);
}

TrackballCanvas::~TrackballCanvas()
{
    Unbind(wxEVT_LEFT_DOWN, &TrackballCanvas::on_left_down, this);
    Unbind(wxEVT_LEFT_UP, &TrackballCanvas::on_left_up, this);
    Unbind(wxEVT_MOTION, &TrackballCanvas::on_motion, this);
    Unbind(wxEVT_KEY_DOWN, &TrackballCanvas::on_key_down, this);
}

glm::vec3
TrackballCanvas::trackball_vector(int x, int y)
{
    const wxSize size = GetClientSize();
    return glm::normalize(glm::vec3(2.0*x/size.GetWidth() - 1.0, 1.0 - 2.0*y/size.GetHeight(), 1.0));
}

void
TrackballCanvas::update_model_view(const wxPoint& oldpos, const wxPoint& newpos)
{
    glm::vec3 p0 = trackball_vector(oldpos.x, oldpos.y);
    glm::vec3 p1 = trackball_vector(newpos.x, newpos.y);
    float angle = acos(std::min(1.0f, glm::dot(p0, p1)));
    glm::vec3 axis = glm::normalize(glm::cross(p0, p1));
    model_view_ = glm::rotate(model_view_, angle, glm::inverse(glm::mat3(model_view_))*axis);
}

void
TrackballCanvas::on_left_down(wxMouseEvent& e)
{
    rotating_ = true;
    mouse_pos_ = e.GetPosition();
    SetFocus();  // to ensure the reset key works
}

void
TrackballCanvas::on_left_up(wxMouseEvent& WXUNUSED(e))
{
    rotating_ = false;
}

void
TrackballCanvas::on_motion(wxMouseEvent& e)
{
    if (rotating_) {
        const wxPoint pos = e.GetPosition();

        if (mouse_pos_ != pos) {
            update_model_view(mouse_pos_, pos);
            draw();
        }

        mouse_pos_ = pos;
    }
}

void
TrackballCanvas::on_key_down(wxKeyEvent& e)
{
    if (e.GetUnicodeKey() == 'R') {
        reset();
    }
}

void
TrackballCanvas::reset()
{
    model_view_ = glm::mat4(1.0f);
    draw();
}
