/*
 * RapidGL - Rapid prototyping for OpenGL
 * Copyright (C) 2013  Andrew Brown
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
#include "RapidGL/PolygonModeNode.h"
namespace RapidGL {

/**
 * Constructs a `PolygonModeNode`.
 *
 * @param mode How to draw polygons, i.e. `GL_POINT`, `GL_LINE`, or `GL_FILL`
 * @throws std::invalid_argument if mode is invalid
 */
PolygonModeNode::PolygonModeNode(const GLenum mode) : mode(mode) {
    if (!isMode(mode)) {
        throw std::invalid_argument("[PolygonModeNode] Mode is invalid!");
    }
}

/**
 * Destructs a `PolygonModeNode`.
 */
PolygonModeNode::~PolygonModeNode() {
    // empty
}

/**
 * Returns the mode this node applies.
 *
 * @return Mode this node applies
 */
GLenum PolygonModeNode::getMode() const {
    return mode;
}

/**
 * Checks if an enumeration is a valid mode.
 *
 * @param enumeration Enumeration to check
 * @return `true` if enumeration is a valid mode
 */
bool PolygonModeNode::isMode(const GLenum enumeration) {
    switch (enumeration) {
    case GL_FILL:
    case GL_LINE:
    case GL_POINT:
        return true;
    default:
        return false;
    }
}

/**
 * Applies this node's polygon mode.
 */
void PolygonModeNode::visit(State& state) {
    glPolygonMode(GL_FRONT_AND_BACK, mode);
}

} /* namespace RapidGL */
