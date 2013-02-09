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
#include "RapidGL/FloatUniformNode.h"
namespace RapidGL {

/**
 * Constructs a `FloatUniformNode`.
 *
 * @param name Name of the uniform as declared in the shader
 * @throws invalid_argument if name is empty
 */
FloatUniformNode::FloatUniformNode(const std::string& name) : UniformNode(name, GL_FLOAT) {
    // empty
}

/**
 * Returns the value of the uniform.
 *
 * @return Value of the uniform
 */
GLfloat FloatUniformNode::getValue() const {
    return value;
}

/**
 * Changes the value of the uniform.
 *
 * @param value New value of uniform
 */
void FloatUniformNode::setValue(const GLfloat value) {
    this->value = value;
}

void FloatUniformNode::visit(State& state) {
    const GLint location = getLocationInProgram(getCurrentProgram());
    if (location >= 0) {
        glUniform1f(location, value);
    }
}

} /* namespace RapidGL */
