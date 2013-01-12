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
#include "RapidGL/ClearNode.hxx"
namespace RapidGL {

/**
 * Constructs a clear node with the default values.
 */
ClearNode::ClearNode() {
    this->red = DEFAULT_RED;
    this->green = DEFAULT_GREEN;
    this->blue = DEFAULT_BLUE;
    this->alpha = DEFAULT_ALPHA;
}

/**
 * Destructs this clear node.
 */
ClearNode::~ClearNode() {
    // empty
}

/**
 * Returns the alpha component of the clear color.
 *
 * @return Alpha component of the clear color, in the range [0 .. 1]
 */
GLfloat ClearNode::getAlpha() const {
    return alpha;
}

/**
 * Returns the blue component of the clear color.
 *
 * @return Blue component of the clear color, in the range [0 .. 1]
 */
GLfloat ClearNode::getBlue() const {
    return blue;
}

/**
 * Returns the green component of the clear color.
 *
 * @return Green component of the clear color, in the range [0 .. 1]
 */
GLfloat ClearNode::getGreen() const {
    return green;
}

/**
 * Returns the red component of the clear color.
 *
 * @return Red component of the clear color, in the range [0 .. 1]
 */
GLfloat ClearNode::getRed() const {
    return red;
}

/**
 * Checks if a value is in the range zero to one inclusive.
 *
 * @param value Value to check
 * @return `true` if value is in the range [0, 1]
 */
bool ClearNode::isNormalized(const GLfloat value) {
    return (value >= 0.0f) && (value <= 1.0f);
}

/**
 * Ensures that a value is in the range zero to one inclusive.
 *
 * @param value Value to check
 * @param message Message of exception if value is not normalized
 * @throws invalid_argument if value is not in the range [0, 1]
 */
void ClearNode::requireNormalized(const GLfloat value, const std::string& message) {
    if (!isNormalized(value)) {
        throw std::invalid_argument(message);
    }
}

/**
 * Changes the alpha component of the clear color.
 *
 * @param alpha Alpha component of the clear color, in the range [0 .. 1]
 * @throws invalid_argument if alpha component is out of range
 */
void ClearNode::setAlpha(const GLfloat alpha) {
    requireNormalized(alpha, "[ClearNode] Alpha component is out of range!");
    this->alpha = alpha;
}

/**
 * Changes the blue component of the clear color.
 *
 * @param blue Blue component of the clear color, in the range [0 .. 1]
 * @throws invalid_argument if blue component is out of range
 */
void ClearNode::setBlue(const GLfloat blue) {
    requireNormalized(blue, "[ClearNode] Blue component is out of range!");
    this->blue = blue;
}

/**
 * Changes the green component of the clear color.
 *
 * @param green Green component of the clear color, in the range [0 .. 1]
 * @throws invalid_argument if green component is out of range
 */
void ClearNode::setGreen(const GLfloat green) {
    requireNormalized(green, "[ClearNode] Green component is out of range!");
    this->green = green;
}

/**
 * Changes the red component of the clear color.
 *
 * @param red Red component of the clear color, in the range [0 .. 1]
 * @throws invalid_argument if red component is out of range
 */
void ClearNode::setRed(const GLfloat red) {
    requireNormalized(red, "[ClearNode] Red component is out of range!");
    this->red = red;
}

void ClearNode::visit(State& state) {
    glClearColor(red, green, blue, alpha);
    glClear(GL_COLOR_BUFFER_BIT);
}

} /* namespace RapidGL */
