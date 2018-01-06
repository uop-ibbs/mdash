//  $Id: trackball_canvas.h 84 2016-03-14 12:13:24Z dw $
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

#ifndef DASH_TRACKBALL_CANVAS_H
#define DASH_TRACKBALL_CANVAS_H

#define GLM_FORCE_RADIANS
#include <glm/mat4x4.hpp>

#include <GL/glew.h>
#include <wx/glcanvas.h>
#include <wx/gdicmn.h>

class TrackballCanvas : public wxGLCanvas
{
 public:
    TrackballCanvas(wxWindow *parent, const int *attr = nullptr, wxWindowID id = wxID_ANY,
                    const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize,
                    long style = wxFULL_REPAINT_ON_RESIZE|wxTAB_TRAVERSAL);
    ~TrackballCanvas();

 protected:
    glm::mat4 projection_;
    glm::mat4 model_view_;

    virtual void draw() = 0;

    void reset();
    void on_left_down(wxMouseEvent& e);
    void on_left_up(wxMouseEvent& e);
    void on_motion(wxMouseEvent& e);
    void on_key_down(wxKeyEvent& e);

 private:
    bool rotating_;
    wxPoint mouse_pos_;

    void update_model_view(const wxPoint& oldpos, const wxPoint& newpos);
    glm::vec3 trackball_vector(int x, int y);
};

#endif // DASH_TRACKBALL_CANVAS_H
