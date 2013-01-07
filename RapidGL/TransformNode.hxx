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
#ifndef RAPIDGL_TRANSFORM_NODE_HXX
#define RAPIDGL_TRANSFORM_NODE_HXX
#include "RapidGL/common.h"
#include "RapidGL/Node.hxx"
#include "RapidGL/State.hxx"
namespace RapidGL {


/**
 * Node that applies a transformation to the model matrix.
 */
class TransformNode : public Node {
public:
// Methods
    TransformNode();
    virtual ~TransformNode();
    virtual void postVisit(State& state);
    virtual void preVisit(State& state);
    virtual void visit(State& state) = 0;
};

} /* namespace RapidGL */
#endif
