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
#ifndef RAPIDGL_CUBE_NODE_H
#define RAPIDGL_CUBE_NODE_H
#include <map>
#include <vector>
#include <gloop/BufferObject.hxx>
#include <gloop/BufferTarget.hxx>
#include <gloop/VertexArrayObject.hxx>
#include <glycerin/AxisAlignedBoundingBox.hxx>
#include <glycerin/BufferLayout.hxx>
#include <glycerin/Ray.hxx>
#include <m3d/Vec3.h>
#include "RapidGL/common.h"
#include "RapidGL/AttributeNode.h"
#include "RapidGL/Intersectable.h"
#include "RapidGL/Node.h"
#include "RapidGL/ProgramNode.h"
#include "RapidGL/State.h"
#include "RapidGL/UseNode.h"
namespace RapidGL {


/**
 * Node that draws a cube.
 */
class CubeNode : public Node, public Intersectable {
public:
// Methods
    CubeNode(const std::string& id = "");
    virtual ~CubeNode();
    virtual double intersect(const Glycerin::Ray& ray) const;
    virtual void visit(State& state);
private:
// Constants
    static const int VERTEX_COUNT = 36;
    static const Gloop::BufferTarget arrayBuffer;
    static const std::vector<int> INDICES;
    static const std::vector<M3d::Vec3> POINTS;
    static const std::vector<M3d::Vec3> COORDS;
// Attributes
    bool ready;
    const Glycerin::AxisAlignedBoundingBox boundingBox;
    const Gloop::BufferObject vbo;
    const Glycerin::BufferLayout layout;
    std::map<Gloop::Program,Gloop::VertexArrayObject> vaos;
// Methods
    static Glycerin::AxisAlignedBoundingBox createBoundingBox();
    static Glycerin::BufferLayout createBufferLayout();
    static std::vector<M3d::Vec3> createCoords();
    static std::vector<int> createIndices();
    static std::vector<M3d::Vec3> createPoints();
    Gloop::VertexArrayObject createVertexArrayObject(const Gloop::Program& program);
    static void disposeVertexArrayObject(const Gloop::VertexArrayObject& vao);
    Gloop::VertexArrayObject getVertexArrayObject(const Gloop::Program& program);
};

} /* namespace RapidGL */
#endif
