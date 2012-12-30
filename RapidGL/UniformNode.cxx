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
#include "RapidGL/UniformNode.hxx"
namespace RapidGL {

/**
 * Constructs a uniform node from a name.
 *
 * @param name Name of the uniform in the shader
 * @param type Data type of uniform, e.g. `GL_FLOAT` or `GL_FLOAT_VEC2`
 * @throws invalid_argument if name is empty
 */
UniformNode::UniformNode(const std::string& name, const GLenum type) :
        name(name), type(type), location(-1), prepared(false) {
    if (name.empty()) {
        throw std::invalid_argument("[UniformNode] Name is empty!");
    }
}

/**
 * Returns the location of this uniform in the shader program.
 *
 * @return Location of this uniform in the shader program
 */
GLint UniformNode::getLocation() const {
    return location;
}

/**
 * Returns the name of this uniform as declared in the shader.
 *
 * @return Name of this uniform as declared in the shader
 */
std::string UniformNode::getName() const {
    return name;
}

/**
 * Returns the data type of this uniform.
 *
 * @return Data type of this uniform
 */
GLenum UniformNode::getType() const {
    return type;
}

void UniformNode::preVisit(State& state) {

    // Skip if already prepared
    if (prepared) {
        return;
    }

    // Find program node
    const ProgramNode* programNode = findAncestor<ProgramNode>(this);
    if (programNode == NULL) {
        throw std::runtime_error("[UniformNode] Could not find program node!");
    }

    // Get program
    const Gloop::Program program = programNode->getProgram();

    // Find uniform
    const std::map<std::string,Gloop::Uniform> uniforms = program.activeUniforms();
    const std::map<std::string,Gloop::Uniform>::const_iterator it = uniforms.find(name);
    if (it == uniforms.end()) {
        throw std::runtime_error("[UniformNode] Could not find uniform!");
    }

    // Check type
    if (it->second.type() != type) {
        throw std::runtime_error("[UniformNode] Uniform is of wrong type!");
    }

    // Store location
    location = it->second.location();

    // Successfully prepared
    prepared = true;
}

} /* namespace RapidGL */
