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
#include "RapidGL/Mat4UniformNode.hxx"
namespace RapidGL {

/**
 * Constructs a `Mat4UniformNode`.
 *
 * @param name Name of uniform as declared in the shader
 * @throws invalid_argument if name is empty
 */
Mat4UniformNode::Mat4UniformNode(const std::string& name) : UniformNode(name, GL_FLOAT_MAT4) {
    // empty
}

/**
 * Returns a copy of the uniform's value.
 *
 * @return Copy of the uniform's value
 */
M3d::Mat4 Mat4UniformNode::getValue() const {
    return value;
}

/**
 * Changes the value of the uniform.
 *
 * @param value New value of the uniform
 */
void Mat4UniformNode::setValue(const M3d::Mat4& value) {
    this->value = value;
}

void Mat4UniformNode::visit(State& state) {
    GLfloat arr[16];
    value.toArrayInColumnMajor(arr);
    glUniformMatrix4fv(getLocation(), 1, false, arr);
}

} /* namespace RapidGL */
