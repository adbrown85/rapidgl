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
ClearNode::ClearNode() : color(DEFAULT_RED, DEFAULT_GREEN, DEFAULT_BLUE, DEFAULT_ALPHA) {
    // empty
}

/**
 * Constructs a clear node from a color.
 *
 * @param color Color to clear color buffer with
 */
ClearNode::ClearNode(const Glycerin::Color& color) : color(clamp(color)) {
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
 * Creates a copy of a color, clamping all its components to between zero and one.
 *
 * @param color Color to copy
 * @return Copy of color with all its components clamped to between zero and one
 */
Glycerin::Color ClearNode::clamp(const Glycerin::Color& color) {
    return Glycerin::Color(clamp(color.r), clamp(color.g), clamp(color.b), clamp(color.a));
}

/*
 * Returns a copy of the color this node clears the color buffer with.
 *
 * @return Copy of the color this node clears the color buffer with
 */
Glycerin::Color ClearNode::getColor() const {
    return color;
}

void ClearNode::visit(State& state) {
    glClearColor(color.r, color.g, color.b, color.a);
    glClear(GL_COLOR_BUFFER_BIT);
}

} /* namespace RapidGL */
