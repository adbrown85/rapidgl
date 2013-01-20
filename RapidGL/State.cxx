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
#include "RapidGL/State.h"
namespace RapidGL {

/**
 * Constructs a state.
 */
State::State() {
    // empty
}

/**
 * Destructs a state.
 */
State::~State() {
    // empty
}

/**
 * Returns a copy of the matrix at the top of the model matrix stack.
 *
 * @return Copy of the matrix at the top of the model matrix stack
 */
M3d::Mat4 State::getModelMatrix() const {
    return modelMatrixStack.top();
}

/**
 * Returns the number of matrices on the model matrix stack.
 *
 * @return Number of matrices on the model matrix stack
 */
size_t State::getModelMatrixStackSize() const {
    return modelMatrixStack.size();
}

/**
 * Returns the result of concatenating the model and view matrices.
 *
 * @return Concatenation of the model and view matrices
 */
M3d::Mat4 State::getModelViewMatrix() const {
    return viewMatrixStack.top() * modelMatrixStack.top();
}

/**
 * Returns the result of concatenating the model, view, and projection matrices.
 *
 * @return Concatenation of the model, view, and projection matrices
 */
M3d::Mat4 State::getModelViewProjectionMatrix() const {
    return projectionMatrixStack.top() * viewMatrixStack.top() * modelMatrixStack.top();
}

/**
 * Returns a copy of the matrix at the top of the projection matrix stack.
 *
 * @return Copy of the matrix at the top of the projection matrix stack
 */
M3d::Mat4 State::getProjectionMatrix() const {
    return projectionMatrixStack.top();
}

/**
 * Returns the number of matrices on the projection matrix stack.
 *
 * @return Number of matrices on the projection matrix stack
 */
size_t State::getProjectionMatrixStackSize() const {
    return projectionMatrixStack.size();
}

/**
 * Returns a copy of the matrix at the top of the view matrix stack.
 *
 * @return Copy of the matrix at the top of the view matrix stack
 */
M3d::Mat4 State::getViewMatrix() const {
    return viewMatrixStack.top();
}

/**
 * Returns the number of matrices on the view matrix stack.
 *
 * @return Number of matrices on the view matrix stack
 */
size_t State::getViewMatrixStackSize() const {
    return viewMatrixStack.size();
}

/**
 * Returns the result of concatenating the view and projection matrices.
 *
 * @return Concatenation of the view and projection matrices
 */
M3d::Mat4 State::getViewProjectionMatrix() const {
    return projectionMatrixStack.top() * viewMatrixStack.top();
}

/**
 * Removes the matrix at the top of the model matrix stack.
 *
 * @throws std::runtime_error if model matrix stack only has one element
 */
void State::popModelMatrix() {
    modelMatrixStack.pop();
}

/**
 * Removes the matrix at the top of the projection matrix stack.
 *
 * @throws std::runtime_error if projection matrix stack only has one element
 */
void State::popProjectionMatrix() {
    projectionMatrixStack.pop();
}

/**
 * Removes the matrix at the top of the view matrix stack.
 *
 * @throws std::runtime_error if view matrix stack only has one element
 */
void State::popViewMatrix() {
    viewMatrixStack.pop();
}

/**
 * Copies the top of the model matrix stack and adds it.
 */
void State::pushModelMatrix() {
    modelMatrixStack.push();
}

/**
 * Copies the top of the projection matrix stack and adds it.
 */
void State::pushProjectionMatrix() {
    projectionMatrixStack.push();
}

/**
 * Copies the top of the view matrix stack and adds it.
 */
void State::pushViewMatrix() {
    viewMatrixStack.push();
}

/**
 * Modifies the top of the model matrix stack.
 *
 * @param mat Matrix to copy
 */
void State::setModelMatrix(const M3d::Mat4& mat) {
    modelMatrixStack.top() = mat;
}

/**
 * Modifies the top of the projection matrix stack.
 *
 * @param mat Matrix to copy
 */
void State::setProjectionMatrix(const M3d::Mat4& mat) {
    projectionMatrixStack.top() = mat;
}

/**
 * Modifies the top of the view matrix stack.
 *
 * @param mat Matrix to copy
 */
void State::setViewMatrix(const M3d::Mat4& mat) {
    viewMatrixStack.top() = mat;
}

} /* namespace RapidGL */
