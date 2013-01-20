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
#ifndef RAPIDGL_SCALE_NODE_H
#define RAPIDGL_SCALE_NODE_H
#include <m3d/Vec3.hxx>
#include "RapidGL/common.h"
#include "RapidGL/TransformNode.h"
#include "RapidGL/State.h"
namespace RapidGL {


/**
 * Node that post-multiplies the model matrix with a scale matrix.
 */
class ScaleNode : public TransformNode {
public:
// Methods
    ScaleNode();
    ScaleNode(const M3d::Vec3& scale);
    virtual ~ScaleNode();
    M3d::Vec3 getScale() const;
    void setScale(const M3d::Vec3& scale);
    virtual void visit(State& state);
private:
// Attributes
    M3d::Vec3 scale;
};

} /* namespace RapidGL */
#endif
