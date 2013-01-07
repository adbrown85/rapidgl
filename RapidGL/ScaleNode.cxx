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
#include <m3d/Mat4.hxx>
#include "RapidGL/ScaleNode.hxx"
namespace RapidGL {

/**
 * Constructs a `ScaleNode`.
 */
ScaleNode::ScaleNode() : scale(M3d::Vec3(1)) {
    // empty
}

/**
 * Constructs a `ScaleNode` with an initial scale.
 *
 * @param scale Initial scale
 */
ScaleNode::ScaleNode(const M3d::Vec3& scale) : scale(scale) {
    // empty
}

/**
 * Destructs a `ScaleNode`.
 */
ScaleNode::~ScaleNode() {
    // empty
}

/**
 * Returns the scale that this node will apply when it is visited.
 *
 * @return Scale this node will apply when it is visited
 */
M3d::Vec3 ScaleNode::getScale() const {
    return scale;
}

/**
 * Changes the scale that this node will apply when it is visited.
 *
 * @param scale Scale this node will apply when it is visited
 */
void ScaleNode::setScale(const M3d::Vec3& scale) {
    this->scale = scale;
}

void ScaleNode::visit(State& state) {

    // Get model matrix from state
    M3d::Mat4 modelMatrix = state.getModelMatrix();

    // Make scale matrix
    M3d::Mat4 scaleMatrix(1);
    scaleMatrix[0][0] = scale.x;
    scaleMatrix[1][1] = scale.y;
    scaleMatrix[2][2] = scale.z;

    // Post-multiply model matrix with scale matrix
    modelMatrix = modelMatrix * scaleMatrix;

    // Update state
    state.setModelMatrix(modelMatrix);
}

} /* namespace RapidGL */
