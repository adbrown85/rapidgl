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
#include "RapidGL/Vec4UniformNode.h"
namespace RapidGL {

/**
 * Constructs a `Vec4UniformNode`.
 *
 * @param name Name of the uniform as declared in the shader
 * @throws invalid_argument if name is empty
 */
Vec4UniformNode::Vec4UniformNode(const std::string& name) : UniformNode(name, GL_FLOAT_VEC4) {
    // empty
}

/**
 * Returns the value of this uniform node.
 *
 * @return Value of this uniform node
 */
M3d::Vec4 Vec4UniformNode::getValue() const {
    return value;
}

/**
 * Changes the value of this uniform node.
 *
 * @param value New value of uniform node
 */
void Vec4UniformNode::setValue(const M3d::Vec4& value) {
    this->value = value;
}

void Vec4UniformNode::visit(State& state) {
    const GLint location = getLocationInProgram(getCurrentProgram());
    if (location >= 0) {
        glUniform4f(location, value.x, value.y, value.z, value.w);
    }
}

} /* namespace RapidGL */
