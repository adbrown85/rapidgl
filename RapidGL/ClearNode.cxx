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

// Set of valid masks
const std::set<GLbitfield> ClearNode::MASKS = ClearNode::createMasks();

/**
 * Constructs a clear node from a color.
 *
 * @param mask Mask defining which buffers to clear
 * @param color Color to clear color buffer with
 * @param depth Depth to clear depth buffer with
 * @throws std::invalid_argument if mask is invalid
 */
ClearNode::ClearNode(const GLbitfield mask,
                     const Glycerin::Color& color,
                     const GLfloat depth) :
        mask(mask), color(clamp(color)), depth(clamp(depth)) {
    if (!isMask(mask)) {
        throw std::invalid_argument("[ClearNode] Mask is invalid!");
    }
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

/**
 * Creates the set of valid masks.
 *
 * @return Set of valid masks
 */
std::set<GLbitfield> ClearNode::createMasks() {
    std::set<GLbitfield> masks;
    masks.insert(GL_COLOR_BUFFER_BIT);
    masks.insert(GL_DEPTH_BUFFER_BIT);
    masks.insert(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    return masks;
}

/*
 * Returns a copy of the color this node clears the color buffer with.
 *
 * @return Copy of the color this node clears the color buffer with
 */
Glycerin::Color ClearNode::getColor() const {
    return color;
}

/**
 * Returns the depth this node clears the depth buffer with.
 *
 * @return Depth this node clears the depth buffer with
 */
GLfloat ClearNode::getDepth() const {
    return depth;
}

/**
 * Returns the mask that defines which buffers this node clears.
 *
 * @return Mask that defines which buffers this node clears
 */
GLbitfield ClearNode::getMask() const {
    return mask;
}

/**
 * Checks if a bitfield is a valid mask.
 *
 * @param bitfield Bitfield to check
 * @return `true` if bitfield is a valid mask
 */
bool ClearNode::isMask(const GLbitfield bitfield) {
    return MASKS.count(bitfield) > 0;
}

void ClearNode::visit(State& state) {
    if (mask & GL_COLOR_BUFFER_BIT) {
        glClearColor(color.r, color.g, color.b, color.a);
    }
    if (mask & GL_DEPTH_BUFFER_BIT) {
        glClearDepth(depth);
    }
    glClear(mask);
}

} /* namespace RapidGL */
