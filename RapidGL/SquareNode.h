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
#ifndef RAPIDGL_SQUARENODE_H
#define RAPIDGL_SQUARENODE_H
#include <gloop/BufferObject.hxx>
#include <gloop/BufferTarget.hxx>
#include <gloop/Program.hxx>
#include <gloop/VertexArrayObject.hxx>
#include <glycerin/AxisAlignedBoundingBox.hxx>
#include <glycerin/BufferLayout.hxx>
#include <glycerin/Ray.hxx>
#include "RapidGL/common.h"
#include "RapidGL/AttributeNode.h"
#include "RapidGL/Intersectable.h"
#include "RapidGL/Node.h"
#include "RapidGL/ProgramNode.h"
#include "RapidGL/State.h"
#include "RapidGL/UseNode.h"
namespace RapidGL {


/**
 * Node drawing a square.
 */
class SquareNode : public Node, public Intersectable {
public:
// Methods
    SquareNode();
    virtual ~SquareNode();
    virtual double intersect(const Glycerin::Ray& ray) const;
    virtual void preVisit(State& state);
    virtual void visit(State& state);
private:
// Constants
    static const int COUNT = 6;
    static Gloop::BufferTarget arrayBuffer;
    static Glycerin::BufferLayout bufferLayout;
// Attributes
    bool prepared;
    Glycerin::AxisAlignedBoundingBox boundingBox;
    Gloop::VertexArrayObject vao;
    Gloop::BufferObject vbo;
// Methods
    static Glycerin::AxisAlignedBoundingBox createBoundingBox();
    static Glycerin::BufferLayout createBufferLayout();
};

} /* namespace RapidGL */
#endif
