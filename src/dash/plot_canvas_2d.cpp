//  $Id: plot_canvas_2d.cpp 119 2017-10-09 10:58:45Z dw $
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

#include "dash/plot_canvas_2d.h"
#include "dash/palette.h"

#include <iostream>
#include <sstream>

#include <wx/dcclient.h>

PlotCanvas2D::PlotCanvas2D(const std::vector<GLfloat>& coords, const std::vector<GLubyte>& colours, wxWindow *parent, const int *attr)
    : wxGLCanvas(parent, wxID_ANY, attr), coords_(coords), colours_(colours)
{
    context_ = new wxGLContext(this);
    Bind(wxEVT_PAINT, &PlotCanvas2D::on_paint, this);
    Bind(wxEVT_SIZE, &PlotCanvas2D::on_size, this);
    initialized_ = false;
}

PlotCanvas2D::~PlotCanvas2D()
{
    glDeleteProgram(program_);
    glDeleteBuffers(1, &vao_);
    glDeleteBuffers(1, &vertex_buf_);
    glDeleteBuffers(1, &colour_buf_);
    Unbind(wxEVT_PAINT, &PlotCanvas2D::on_paint, this);
    Unbind(wxEVT_SIZE, &PlotCanvas2D::on_size, this);
    delete context_;
}

void
PlotCanvas2D::init_gl()
{
    SetCurrent(*context_);
    GLenum err = glewInit();

    if (err != GLEW_OK) {
        std::ostringstream os;
        os << "Error: " << glewGetErrorString(err);
        wxLogError(wxString(os.str()));
    }

    init_shaders();
    init_buffers();

    GLuint u_clr = glGetUniformLocation(program_, "u_clr");
    const GLfloat white[3] = {1, 1, 1};
    glUniform3fv(u_clr, 1, white);

    rescale();

    GLenum error = glGetError();

    if (error) {
        std::cerr << "GL_ERROR: init error:\n  " << gluErrorString(error) << '\n';
    }

    initialized_ = true;
}

void
PlotCanvas2D::init_shaders()
{
    const GLchar* v_shader_src =
        "#version 130\n"
        "uniform bool monochrome;"
        "uniform vec3 u_clr;"
        "uniform mat4 transform;"
        "in vec2 v_pos;"
        "in vec3 v_clr;"
        "out vec4 f_clr;"
        "void main()"
        "{"
        "  gl_Position = transform * vec4(v_pos, 0.0, 1.0);"
        "  if (monochrome) {"
        "    f_clr = vec4(u_clr, 1.0);"
        "  } else {"
        "    f_clr = vec4(v_clr, 1.0);"
        "  }"
        "}";

    const GLchar* f_shader_src =
        "#version 130\n"
        "in vec4 f_clr;"
        "out vec4 colour;"
        "void main() {"
        "  colour = f_clr;"
        "}";

    GLuint v_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(v_shader, 1, &v_shader_src, NULL);
    glCompileShader(v_shader);

    GLint status;
    glGetShaderiv(v_shader, GL_COMPILE_STATUS, &status);

    if (!status) {
        std::cerr << "GL_ERROR: failed to compile vertex shader\n";

        GLsizei len;
        glGetShaderiv(v_shader, GL_INFO_LOG_LENGTH, &len);

        if (len > 0) {
            std::vector<GLchar> log(len);
            glGetShaderInfoLog(v_shader, len, NULL, &log[0]);
            std::cerr << &log[0] << '\n';
        }
    }

    GLuint f_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(f_shader, 1, &f_shader_src, NULL);
    glCompileShader(f_shader);

    glGetShaderiv(f_shader, GL_COMPILE_STATUS, &status);

    if (!status) {
        std::cerr << "GL_ERROR: failed to compile fragment shader\n";

        GLsizei len;
        glGetShaderiv(f_shader, GL_INFO_LOG_LENGTH, &len);

        if (len > 0) {
            std::vector<GLchar> log(len);
            glGetShaderInfoLog(f_shader, len, NULL, &log[0]);
            std::cerr << &log[0] << '\n';
        }
    }

    program_ = glCreateProgram();
    glAttachShader(program_, v_shader);
    glAttachShader(program_, f_shader);
    glLinkProgram(program_);
    glGetProgramiv(program_, GL_LINK_STATUS, &status);

    if (!status) {
        std::cerr << "GL_ERROR: failed to link shaders\n";

        GLsizei len;
        glGetProgramiv(program_, GL_INFO_LOG_LENGTH, &len);

        if (len > 0) {
            std::vector<GLchar> log(len);
            glGetProgramInfoLog(program_, len, NULL, &log[0]);
            std::cerr << &log[0] << '\n';
        }
    }

    glUseProgram(program_);
    glValidateProgram(program_);

    glGetProgramiv(program_, GL_VALIDATE_STATUS, &status);

    if (!status) {
        std::cerr << "GL_ERROR: invalid program\n";

        GLsizei len;
        glGetProgramiv(program_, GL_INFO_LOG_LENGTH, &len);

        if (len > 0) {
            std::vector<GLchar> log(len);
            glGetProgramInfoLog(program_, len, NULL, &log[0]);
            std::cerr << &log[0] << '\n';
        }
    }

    glDeleteShader(v_shader);
    glDeleteShader(f_shader);
}

void
PlotCanvas2D::init_buffers()
{
    glGenVertexArrays(1, &vao_);
    glBindVertexArray(vao_);

    glGenBuffers(1, &vertex_buf_);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buf_);
    glBufferData(GL_ARRAY_BUFFER, coords_.size()*sizeof(GLfloat), &coords_[0], GL_STATIC_DRAW);

    GLuint v_pos = glGetAttribLocation(program_, "v_pos");
    glEnableVertexAttribArray(v_pos);

    glGenBuffers(1, &colour_buf_);
    glBindBuffer(GL_ARRAY_BUFFER, colour_buf_);
    glBufferData(GL_ARRAY_BUFFER, colours_.size()*sizeof(GLubyte), &colours_[0], GL_STATIC_DRAW);

    GLuint v_clr = glGetAttribLocation(program_, "v_clr");
    glEnableVertexAttribArray(v_clr);

    const GLfloat axis[4][2] = {
        {-1, 0},
        { 1, 0},
        { 0,-1},
        { 0, 1}
    };

    glGenBuffers(1, &axis_buf_);
    glBindBuffer(GL_ARRAY_BUFFER, axis_buf_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(axis), axis, GL_STATIC_DRAW);

    const GLfloat xlabel[4][2] = {
        {0.92f,-0.10f},
        {0.96f,-0.04f},
        {0.92f,-0.04f},
        {0.96f,-0.10f}
    };

    glGenBuffers(1, &xlabel_buf_);
    glBindBuffer(GL_ARRAY_BUFFER, xlabel_buf_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(xlabel), xlabel, GL_STATIC_DRAW);

    const GLfloat ylabel[6][2] = {
        {0.04f,0.98f},
        {0.06f,0.96f},
        {0.06f,0.96f},
        {0.08f,0.98f},
        {0.06f,0.92f},
        {0.06f,0.96f}
    };

    glGenBuffers(1, &ylabel_buf_);
    glBindBuffer(GL_ARRAY_BUFFER, ylabel_buf_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(ylabel), ylabel, GL_STATIC_DRAW);
}

void
PlotCanvas2D::on_paint(wxPaintEvent& WXUNUSED(e))
{
    wxPaintDC dc(this); // required but unused
    if (!initialized_) init_gl();
    SetCurrent(*context_);
    draw();
}

void
PlotCanvas2D::draw()
{
    GLint v_pos = glGetAttribLocation(program_, "v_pos");
    GLint v_clr = glGetAttribLocation(program_, "v_clr");
    GLint monochrome = glGetUniformLocation(program_, "monochrome");

    glPointSize(2.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glBindBuffer(GL_ARRAY_BUFFER, vertex_buf_);
    glVertexAttribPointer(v_pos, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, colour_buf_);
    glVertexAttribPointer(v_clr, 3, GL_UNSIGNED_BYTE, GL_TRUE, 0, 0);

    glUniform1i(monochrome, false);
    glDrawArrays(GL_POINTS, 0, coords_.size()/dim_);

    glUniform1i(monochrome, true);
    glBindBuffer(GL_ARRAY_BUFFER, axis_buf_);
    glVertexAttribPointer(v_pos, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glDrawArrays(GL_LINES, 0, 4);

    glBindBuffer(GL_ARRAY_BUFFER, xlabel_buf_);
    glVertexAttribPointer(v_pos, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glDrawArrays(GL_LINES, 0, 4);

    glBindBuffer(GL_ARRAY_BUFFER, ylabel_buf_);
    glVertexAttribPointer(v_pos, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glDrawArrays(GL_LINES, 0, 6);

    SwapBuffers();
}

void
PlotCanvas2D::on_size(wxSizeEvent& WXUNUSED(e))
{
    if (initialized_) {
        rescale();
    }
}

void
PlotCanvas2D::rescale()
{
    const wxSize size = GetClientSize();
    int width = size.GetWidth();
    int height = size.GetHeight();

    GLfloat aspect = static_cast<GLfloat>(width)/static_cast<GLfloat>(height);
    GLfloat xscale, yscale;

    if (aspect > 1.0) {
        xscale = 1.0/aspect;
        yscale = 1.0;
    } else {
        xscale = 1.0;
        yscale = aspect;
    }

    GLfloat transform[] = {
        xscale, 0, 0, 0,
        0, yscale, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    };

    GLint transform_loc = glGetUniformLocation(program_, "transform");
    glUniformMatrix4fv(transform_loc, 1, GL_FALSE, transform);
    glViewport(0, 0, width, height);
    GLenum error = glGetError();

    if (error) {
        std::cerr << "GL_ERROR: rescale error:\n  " << gluErrorString(error) << '\n';
    }
}
