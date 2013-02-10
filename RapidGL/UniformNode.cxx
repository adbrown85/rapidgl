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
#include "RapidGL/UniformNode.h"
namespace RapidGL {

/**
 * Constructs a uniform node from a name.
 *
 * @param name Name of the uniform in the shader
 * @param type Data type of uniform, e.g. `GL_FLOAT` or `GL_FLOAT_VEC2`
 * @throws invalid_argument if name is empty
 */
UniformNode::UniformNode(const std::string& name, const GLenum type) : name(name), type(type) {
    if (name.empty()) {
        throw std::invalid_argument("[UniformNode] Name is empty!");
    }
}

/**
 * Looks up the location of this uniform in a program.
 *
 * @return Location of this uniform in the program, or `-1` if it's not in the program
 * @throws std::runtime_error if uniform is in program but has the wrong type
 */
GLint UniformNode::findLocationInProgram(const Gloop::Program& program) const {

    // Get uniforms in program
    const std::map<std::string,Gloop::Uniform> uniforms = program.activeUniforms();

    // Lookup uniform by name
    const std::map<std::string,Gloop::Uniform>::const_iterator it = uniforms.find(name);
    if (it == uniforms.end()) {
        return -1;
    }

    // Store uniform
    const Gloop::Uniform uniform = it->second;

    // Check type
    if (uniform.type() != type) {
        throw std::runtime_error("[UniformNode] Uniform is of wrong type!");
    }

    // Return location
    return uniform.location();
}

/**
 * Returns the location of this uniform in a program.
 *
 * @param program Program to get location of this uniform in
 * @return Location of this uniform in the program, or `-1` if it's not in the program
 * @throws std::runtime_error if uniform is in the program but has the wrong type
 */
GLint UniformNode::getLocationInProgram(const Gloop::Program& program) {

    // Look in cache first
    const std::map<Gloop::Program,GLint>::const_iterator it = locations.find(program);
    if (it != locations.end()) {
        return it->second;
    }

    // If not in cache find it, store it for next time, and then return it
    const GLint location = findLocationInProgram(program);
    locations.insert(std::pair<Gloop::Program,GLint>(program, location));
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

} /* namespace RapidGL */
