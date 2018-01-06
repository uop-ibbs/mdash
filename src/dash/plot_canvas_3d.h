//  $Id: plot_canvas_3d.h 119 2017-10-09 10:58:45Z dw $
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

#ifndef DASH_PLOT_CANVAS_3D_H
#define DASH_PLOT_CANVAS_3D_H

#include "dash/trackball_canvas.h"

#include <GL/glew.h>
#include <wx/glcanvas.h>

#include <vector>

class PlotCanvas3D : public TrackballCanvas
{
 public:
    PlotCanvas3D(const std::vector<GLfloat>& coords, const std::vector<GLubyte>& colours, wxWindow* parent, const int *attr = nullptr);
    ~PlotCanvas3D();

 private:
    static bool gl_version_displayed_;

    const std::vector<GLfloat>& coords_;
    const std::vector<GLubyte>& colours_;

    const int dim_ = 3;

    wxGLContext* context_;
    bool initialized_;
    GLuint vao_;
    GLuint program_;
    GLuint vertex_buf_;
    GLuint colour_buf_;
    GLuint axis_buf_;
    GLuint xlabel_buf_;
    GLuint ylabel_buf_;
    GLuint zlabel_buf_;
    GLuint monochrome_;

    void init_gl();
    void init_shaders();
    void init_buffers();
    void on_paint(wxPaintEvent& e);
    void on_size(wxSizeEvent& e);
    void draw();
    void rescale();
};

#endif // DASH_PLOT_CANVAS_3D_H
