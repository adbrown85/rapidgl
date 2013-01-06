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
#include <m3d/Vec4.hxx>
#include "RapidGL/TranslateNode.hxx"
namespace RapidGL {

/**
 * Constructs a `TranslateNode`.
 */
TranslateNode::TranslateNode() {
    // empty
}

/**
 * Constructs a `TranslateNode` with an initial translation.
 *
 * @param translation Initial translation
 */
TranslateNode::TranslateNode(const M3d::Vec3& translation) : translation(translation) {
    // empty
}

/**
 * Destructs a `TranslateNode`.
 */
TranslateNode::~TranslateNode() {
    // empty
}

/**
 * Returns the translation that this node applies.
 *
 * @return Translation this node applies
 */
M3d::Vec3 TranslateNode::getTranslation() const {
    return translation;
}

void TranslateNode::postVisit(State& state) {
    state.popModelMatrix();
}

void TranslateNode::preVisit(State& state) {
    state.pushModelMatrix();
}

/**
 * Changes the translation that this node applies.
 *
 * @param translation Translation node will apply
 */
void TranslateNode::setTranslation(const M3d::Vec3& translation) {
    this->translation = translation;
}

void TranslateNode::visit(State& state) {

    // Get the model matrix
    M3d::Mat4 modelMatrix = state.getModelMatrix();

    // Make a translation matrix
    M3d::Mat4 translationMatrix = M3d::Mat4(1);
    translationMatrix[3] = M3d::Vec4(translation, 1);

    // Multiply it with the model matrix and store it
    modelMatrix = modelMatrix * translationMatrix;
    state.setModelMatrix(modelMatrix);
}

} /* namespace RapidGL */
