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
#include "RapidGL/DepthFunctionNode.h"
namespace RapidGL {

/**
 * Constructs a `DepthFunctionNode`.
 *
 * @param function Function to apply when visited
 * @throws std::invalid_argument if enumeration is not a valid depth function
 */
DepthFunctionNode::DepthFunctionNode(const GLenum function) : function(function) {
    if (!isFunction(function)) {
        throw std::invalid_argument("Enumeration is not a valid depth function!");
    }
}

/**
 * Destructs a `DepthFunctionNode`.
 */
DepthFunctionNode::~DepthFunctionNode() {
    // empty
}

/**
 * Returns the depth function this node applies when it's visited.
 *
 * @return Depth function this node applies when it's visited
 */
GLenum DepthFunctionNode::getFunction() const {
    return function;
}

/**
 * Checks if an OpenGL enumeration is a valid depth function.
 *
 * @param enumeration Enumeration to check
 * @return `true` if enumeration is a valid depth function
 */
bool DepthFunctionNode::isFunction(const GLenum enumeration) {
    switch (enumeration) {
    case GL_NEVER:
    case GL_LESS:
    case GL_EQUAL:
    case GL_LEQUAL:
    case GL_GREATER:
    case GL_NOTEQUAL:
    case GL_GEQUAL:
    case GL_ALWAYS:
        return true;
    default:
        return false;
    }
}

void DepthFunctionNode::visit(State& state) {
    glDepthFunc(function);
}

} /* namespace RapidGL */
