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
#include "RapidGL/Mat3UniformNode.hxx"
namespace RapidGL {

/**
 * Constructs a `Mat3UniformNode`.
 *
 * @param name Name of uniform as declared in the shader
 * @throws invalid_argument if name is empty
 */
Mat3UniformNode::Mat3UniformNode(const std::string& name) : UniformNode(name, GL_FLOAT_MAT3) {
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
}

void Mat3UniformNode::visit(State& state) {
    GLfloat arr[9];
    value.toArrayInColumnMajor(arr);
    glUniformMatrix3fv(getLocation(), 1, false, arr);
}

} /* namespace RapidGL */