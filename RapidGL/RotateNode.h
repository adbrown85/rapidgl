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
#ifndef RAPIDGL_ROTATE_NODE_H
#define RAPIDGL_ROTATE_NODE_H
#include <m3d/Quat.h>
#include "RapidGL/common.h"
#include "RapidGL/Node.h"
#include "RapidGL/State.h"
#include "RapidGL/TransformNode.h"
namespace RapidGL {


/**
 * Node that post-multiplies the model matrix with a rotation.
 */
class RotateNode : public TransformNode {
public:
// Methods
    RotateNode();
    RotateNode(const M3d::Quat& rotation);
    virtual ~RotateNode();
    M3d::Quat getRotation() const;
    void setRotation(const M3d::Quat& rotation);
    virtual void visit(State& state);
private:
// Atttributes
    M3d::Quat rotation;
};

} /* namespace RapidGL */
#endif
