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
#include <set>
#include <glycerin/Color.hxx>
#include "RapidGL/common.h"
#include "RapidGL/Node.h"
#include "RapidGL/State.h"
namespace RapidGL {


/**
 * Node for clearing a framebuffer, either default or user-defined.
 */
class ClearNode : public Node {
public:
// Methods
    ClearNode(GLbitfield mask, const Glycerin::Color& color, GLfloat depth);
    virtual ~ClearNode();
    Glycerin::Color getColor() const;
    GLfloat getDepth() const;
    GLbitfield getMask() const;
    virtual void visit(State& state);
private:
// Constants
    static const std::set<GLbitfield> MASKS;
// Attributes
    const GLbitfield mask;
    const Glycerin::Color color;
    const GLfloat depth;
// Methods
    static GLfloat clamp(GLfloat value);
    static Glycerin::Color clamp(const Glycerin::Color& color);
    static std::set<GLbitfield> createMasks();
    static bool isMask(GLbitfield bitfield);
};

} /* namespace RapidGL */
#endif
