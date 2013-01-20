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
#include "config.h"
#include <stdexcept>
#include "RapidGL/ShaderNode.hxx"
namespace RapidGL {

/**
 * Constructs a shader node.
 *
 * @param type Type of shader, e.g. `GL_VERTEX_SHADER` or `GL_FRAGMENT_SHADER`
 * @param source Source code of shader
 * @throws invalid_argument if type is invalid or source is empty
 * @throws runtime_error if shader could not be compiled
 */
ShaderNode::ShaderNode(const GLenum type, const std::string& source) : shader(createShader(type, source)) {
    // empty
}

/**
 * Destructs this shader node.
 */
ShaderNode::~ShaderNode() {
    shader.dispose();
}

/**
 * Creates a shader from a type and a file.
 *
 * @param type Type of shader
 * @param source Source code of shader
 * @return Resulting shader
 * @throws invalid_argument if type is invalid or source is empty
 * @throws runtime_error if shader could not be compiled
 */
Gloop::Shader ShaderNode::createShader(const GLenum type, const std::string& source) {
    Glycerin::ShaderFactory factory;
    return factory.createShaderFromString(type, source);
}

/**
 * Returns a handle to the shader.
 *
 * @return Handle to the shader
 */
Gloop::Shader ShaderNode::getShader() const {
    return shader;
}

void ShaderNode::visit(State& state) {
    // empty
}

} /* namespace RapidGL */
