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
#include "RapidGL/CullNode.h"
namespace RapidGL {

/**
 * Constructs a `CullNode`.
 *
 * The resulting node will enable front, back, or both front and back culling, or
 * disable all culling, depending on the value for `mode`.  Valid values for `mode`
 * are listed below.
 *
 *  - `GL_BACK`
 *  - `GL_FRONT`
 *  - `GL_FRONT_AND_BACK`
 *  - `GL_NONE`
 *
 * Note that `GL_NONE` is not a valid value for `glCullFace`, but we use it here to
 * indicate culling will be completely disabled using `glDisable`.
 *
 * @param mode Mode determining which, if any faces are culled, e.g. `GL_BACK`
 * @throws std::invalid_argument if mode is invalid
 */
CullNode::CullNode(const GLenum mode) : mode(mode) {
    if (!isMode(mode)) {
        throw std::invalid_argument("[CullNode] Mode is not valid!");
    }
}

/**
 * Destructs a `CullNode`.
 */
CullNode::~CullNode() {
    // empty
}

/**
 * Returns the mode determining which, if any faces are culled.
 *
 * The value returned by `getMode` will be
 *
 *  - `GL_BACK`,
 *  - `GL_FRONT`,
 *  - `GL_FRONT_AND_BACK`, or
 *  - `GL_NONE`.
 *
 * Note that `GL_NONE` is not a valid value for `glCullFace`, but we use it here to
 * indicate culling will be completely disabled using `glDisable`.
 *
 * @return Mode determining which, if any faces are culled
 */
GLenum CullNode::getMode() const {
    return mode;
}

/**
 * Checks if an enumeration is a valid value for `mode`.
 *
 * @param enumeration Enumeration to check
 * @return `true` if enumeration is a valid value for `mode`
 */
bool CullNode::isMode(const GLenum enumeration) {
    switch (enumeration) {
    case GL_BACK:
    case GL_FRONT:
    case GL_FRONT_AND_BACK:
    case GL_NONE:
        return true;
    default:
        return false;
    }
}

void CullNode::visit(State& state) {
    if (mode == GL_NONE) {
        glDisable(GL_CULL_FACE);
    } else {
        glEnable(GL_CULL_FACE);
        glCullFace(mode);
    }
}

} /* namespace RapidGL */
