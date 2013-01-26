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
#ifndef RAPIDGL_STATE_H
#define RAPIDGL_STATE_H
#include <glycerin/MatrixStack.hxx>
#include <m3d/Mat4.h>
#include "RapidGL/common.h"
namespace RapidGL {


/**
 * Shared state for nodes.
 */
class State {
public:
// Methods
    State();
    virtual ~State();
    M3d::Mat4 getModelMatrix() const;
    size_t getModelMatrixStackSize() const;
    M3d::Mat4 getModelViewMatrix() const;
    M3d::Mat4 getModelViewProjectionMatrix() const;
    M3d::Mat4 getProjectionMatrix() const;
    size_t getProjectionMatrixStackSize() const;
    M3d::Mat4 getViewMatrix() const;
    size_t getViewMatrixStackSize() const;
    M3d::Mat4 getViewProjectionMatrix() const;
    void popModelMatrix();
    void popProjectionMatrix();
    void popViewMatrix();
    void pushModelMatrix();
    void pushProjectionMatrix();
    void pushViewMatrix();
    void setModelMatrix(const M3d::Mat4& mat);
    void setProjectionMatrix(const M3d::Mat4& mat);
    void setViewMatrix(const M3d::Mat4& mat);
private:
// Attributes
    Glycerin::MatrixStack modelMatrixStack;
    Glycerin::MatrixStack projectionMatrixStack;
    Glycerin::MatrixStack viewMatrixStack;
};

} /* namespace RapidGL */
#endif
