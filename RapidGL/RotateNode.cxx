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
#include "RapidGL/RotateNode.hxx"
namespace RapidGL {

/**
 * Constructs a `RotateNode`.
 */
RotateNode::RotateNode() : rotation(M3d::Quat(0, 0, 0, 1)) {
    // empty
}

/**
 * Constructs a `RotateNode` with an initial rotation.
 *
 * @param rotation Initial rotation
 */
RotateNode::RotateNode(const M3d::Quat& rotation) : rotation(rotation) {
    // empty
}

/**
 * Destructs a `RotateNode`.
 */
RotateNode::~RotateNode() {
    // empty
}

/**
 * Returns the rotation this node applies.
 *
 * @return Rotation this node applies
 */
M3d::Quat RotateNode::getRotation() const {
    return rotation;
}

/**
 * Changes the rotation this node applies.
 *
 * @param rotation Rotation this node applies
 */
void RotateNode::setRotation(const M3d::Quat& rotation) {
    this->rotation = rotation;
}

void RotateNode::visit(State& state) {

    // Get model matrix
    M3d::Mat4 modelMatrix = state.getModelMatrix();

    // Make rotation matrix
    const M3d::Mat4 rotationMatrix = rotation.toMat4();

    // Post-multiply with model matrix
    modelMatrix = modelMatrix * rotationMatrix;

    // Store model matrix in state
    state.setModelMatrix(modelMatrix);
}

} /* namespace RapidGL */
