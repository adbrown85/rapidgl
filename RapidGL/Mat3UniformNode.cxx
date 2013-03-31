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
#include "RapidGL/Mat3UniformNode.h"
namespace RapidGL {

/**
 * Constructs a `Mat3UniformNode` with the default value.
 *
 * @param name Name of uniform as declared in the shader
 * @throws invalid_argument if name is empty
 */
Mat3UniformNode::Mat3UniformNode(const std::string& name) : UniformNode(name, TYPE) {
    // empty
}

/**
 * Constructs a `Mat3UniformNode` with an initial value.
 *
 * @param name Name of uniform as declared in the shader
 * @param value Initial value of uniform
 * @throws invalid_argument if name is empty
 */
Mat3UniformNode::Mat3UniformNode(const std::string& name, const M3d::Mat3& value) :
        UniformNode(name, TYPE), value(value) {
    // empty
}

/**
 * Returns a copy of the uniform's value.
 *
 * @return Copy of the uniform's value
 */
M3d::Mat3 Mat3UniformNode::getValue() const {
    return value;
}

/**
 * Changes the value of the uniform.
 *
 * @param value New value of the uniform
 */
void Mat3UniformNode::setValue(const M3d::Mat3& value) {
    this->value = value;
    fireNodeChangedEvent();
}

void Mat3UniformNode::visit(State& state) {
    const GLint location = getLocationInProgram(Gloop::Program::current());
    if (location >= 0) {
        GLfloat arr[9];
        value.toArrayInColumnMajor(arr);
        glUniformMatrix3fv(location, 1, false, arr);
    }
}

} /* namespace RapidGL */
