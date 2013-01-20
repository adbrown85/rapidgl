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
#ifndef RAPIDGL_SHADERNODE_H
#define RAPIDGL_SHADERNODE_H
#include <gloop/Shader.hxx>
#include <glycerin/ShaderFactory.hxx>
#include <string>
#include "RapidGL/common.h"
#include "RapidGL/Node.h"
#include "RapidGL/State.h"
namespace RapidGL {


/**
 * Node representing a shader.
 */
class ShaderNode : public Node {
public:
// Methods
    ShaderNode(GLenum type, const std::string& source);
    virtual ~ShaderNode();
    Gloop::Shader getShader() const;
    virtual void visit(State& state);
private:
// Attributes
    Gloop::Shader shader;
// Methods
    static Gloop::Shader createShader(GLenum type, const std::string& source);
};

} /* namespace RapidGL */
#endif
