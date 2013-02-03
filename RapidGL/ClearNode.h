/*
 * RapidGL - Rapid prototyping for OpenGL
 * Copyright (C) 2012  Andrew Brown
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef RAPIDGL_CLEAR_NODE_H
#define RAPIDGL_CLEAR_NODE_H
#include "RapidGL/common.h"
#include "RapidGL/Node.h"
#include "RapidGL/State.h"
namespace RapidGL {


/**
 * Node for clearing a framebuffer, either default or user-defined.
 */
class ClearNode : public Node {
public:
// Constants
    static const GLfloat DEFAULT_RED = 0.0f; ///< Initial value for red component
    static const GLfloat DEFAULT_GREEN = 0.0f; ///< Initial value for green component
    static const GLfloat DEFAULT_BLUE = 0.0f; ///< Initial value for blue component
    static const GLfloat DEFAULT_ALPHA = 0.0f; ///< Initial value for alpha component
// Methods
    ClearNode();
    ClearNode(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
    virtual ~ClearNode();
    GLfloat getAlpha() const;
    GLfloat getBlue() const;
    GLfloat getGreen() const;
    GLfloat getRed() const;
    virtual void visit(State& state);
private:
// Attributes
    const GLfloat red;
    const GLfloat green;
    const GLfloat blue;
    const GLfloat alpha;
// Methods
    static GLfloat clamp(GLfloat value);
};

} /* namespace RapidGL */
#endif
