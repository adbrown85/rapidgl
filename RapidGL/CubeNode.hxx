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
#ifndef RAPIDGL_CUBE_NODE_HXX
#define RAPIDGL_CUBE_NODE_HXX
#include <vector>
#include <gloop/BufferObject.hxx>
#include <gloop/BufferTarget.hxx>
#include <gloop/VertexArrayObject.hxx>
#include <glycerin/BufferLayout.hxx>
#include <m3d/Vec3.hxx>
#include "RapidGL/common.h"
#include "RapidGL/AttributeNode.hxx"
#include "RapidGL/Node.hxx"
#include "RapidGL/ProgramNode.hxx"
#include "RapidGL/State.hxx"
namespace RapidGL {


/**
 * Node that draws a cube.
 */
class CubeNode : public Node {
public:
// Methods
    CubeNode();
    virtual ~CubeNode();
    virtual void preVisit(State& state);
    virtual void visit(State& state);
private:
// Constants
    static const int VERTEX_COUNT = 36;
    static Gloop::BufferTarget arrayBuffer;
    static std::vector<int> INDICES;
    static std::vector<M3d::Vec3> POINTS;
    static std::vector<M3d::Vec3> COORDS;
// Attributes
    bool ready;
    const Gloop::BufferObject vbo;
    const Glycerin::BufferLayout layout;
    const Gloop::VertexArrayObject vao;
// Methods
    static Glycerin::BufferLayout createBufferLayout();
    static std::vector<M3d::Vec3> createCoords();
    static std::vector<int> createIndices();
    static std::vector<M3d::Vec3> createPoints();
};

} /* namespace RapidGL */
#endif
