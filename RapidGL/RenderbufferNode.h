/*
 * RapidGL - Rapid prototyping for OpenGL
 * Copyright (C) 2013  Andrew Brown
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
#ifndef RAPIDGL_RENDERBUFFER_NODE_H
#define RAPIDGL_RENDERBUFFER_NODE_H
#include <set>
#include <string>
#include <gloop/RenderbufferObject.hxx>
#include "RapidGL/common.h"
#include "RapidGL/Node.h"
#include "RapidGL/State.h"
namespace RapidGL {


/**
 * Node representing an OpenGL renderbuffer object.
 */
class RenderbufferNode : public Node {
public:
// Methods
    RenderbufferNode(const std::string& id, GLenum format, GLsizei width, GLsizei height);
    virtual ~RenderbufferNode();
    Gloop::RenderbufferObject getRenderbufferObject() const;
    virtual void visit(State& state);
private:
// Constants
    static const std::set<GLenum> FORMATS;
// Attributes
    const Gloop::RenderbufferObject rbo;
// Methods
    static std::set<GLenum> createFormats();
    static GLsizei getMaxRenderbufferSize();
    static bool isFormat(GLenum enumeration);
};

} /* namespace RapidGL */
#endif
