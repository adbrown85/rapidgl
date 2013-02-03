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
#include "RapidGL/ClearNode.h"
namespace RapidGL {

/**
 * Constructs a clear node with the default values.
 */
ClearNode::ClearNode() : red(DEFAULT_RED), green(DEFAULT_GREEN), blue(DEFAULT_BLUE), alpha(DEFAULT_ALPHA) {
    // empty
}

/**
 * Constructs a clear node from red, green, blue, and alpha values.
 *
 * @param red Value for red component
 * @param green Value for green component
 * @param blue Value for blue component
 * @param alpha Value for alpha component
 */
ClearNode::ClearNode(const GLfloat red, const GLfloat green, const GLfloat blue, const GLfloat alpha) :
        red(clamp(red)), green(clamp(green)), blue(clamp(blue)), alpha(clamp(alpha)) {
    // empty
}

/**
 * Destructs this clear node.
 */
ClearNode::~ClearNode() {
    // empty
}

/**
 * Clamps a value to between zero and one.
 *
 * @param value Value to clamp
 * @return Value clamped to between zero and one
 */
GLfloat ClearNode::clamp(GLfloat value) {
    return std::max(0.0f, std::min(value, 1.0f));
}

/**
 * Returns the alpha component of the clear color.
 *
 * @return Alpha component of the clear color, in the range [0, 1]
 */
GLfloat ClearNode::getAlpha() const {
    return alpha;
}

/**
 * Returns the blue component of the clear color.
 *
 * @return Blue component of the clear color, in the range [0, 1]
 */
GLfloat ClearNode::getBlue() const {
    return blue;
}

/**
 * Returns the green component of the clear color.
 *
 * @return Green component of the clear color, in the range [0, 1]
 */
GLfloat ClearNode::getGreen() const {
    return green;
}

/**
 * Returns the red component of the clear color.
 *
 * @return Red component of the clear color, in the range [0, 1]
 */
GLfloat ClearNode::getRed() const {
    return red;
}

void ClearNode::visit(State& state) {
    glClearColor(red, green, blue, alpha);
    glClear(GL_COLOR_BUFFER_BIT);
}

} /* namespace RapidGL */
