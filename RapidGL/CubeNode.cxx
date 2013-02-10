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
#include <map>
#include <string>
#include <gloop/VertexAttribPointer.hxx>
#include <glycerin/BufferLayoutBuilder.hxx>
#include <glycerin/BufferRegion.hxx>
#include "RapidGL/CubeNode.h"
namespace RapidGL {

// Array buffer target
const Gloop::BufferTarget CubeNode::arrayBuffer = Gloop::BufferTarget::arrayBuffer();

// Indices determining which triangle vertices correspond to which corners
const std::vector<int> CubeNode::INDICES = createIndices();

// Points for each corner
const std::vector<M3d::Vec3> CubeNode::POINTS = createPoints();

// Texture coordinates for each corner
const std::vector<M3d::Vec3> CubeNode::COORDS = createCoords();

/**
 * Constructs a `CubeNode`.
 *
 * @param id Identifier of node, which may be empty
 */
CubeNode::CubeNode(const std::string& id) :
        Node(id),
        ready(false),
        boundingBox(createBoundingBox()),
        layout(createBufferLayout()),
        vao(Gloop::VertexArrayObject::generate()),
        vbo(Gloop::BufferObject::generate()) {

    // Bind buffer
    arrayBuffer.bind(vbo);

    // Create data
    const int len = layout.sizeInBytes() / sizeof(GLfloat);
    GLfloat data[len];
    GLfloat* ptr = data;
    for (int i = 0; i < VERTEX_COUNT; ++i) {
        const int corner = INDICES[i];
        *(ptr++) = POINTS[corner].x;
        *(ptr++) = POINTS[corner].y;
        *(ptr++) = POINTS[corner].z;
        *(ptr++) = COORDS[corner].x;
        *(ptr++) = COORDS[corner].y;
        *(ptr++) = COORDS[corner].z;
    }

    // Load data
    arrayBuffer.data(layout.sizeInBytes(), data, GL_STATIC_DRAW);

    // Unbind buffer
    arrayBuffer.unbind(vbo);
}

/**
 * Destructs a `CubeNode`.
 */
CubeNode::~CubeNode() {
    vao.dispose();
    vbo.dispose();
}

/**
 * Creates the bounding box the cube delegates to for intersection testing.
 */
Glycerin::AxisAlignedBoundingBox CubeNode::createBoundingBox() {
    const M3d::Vec4 min(-0.5, -0.5, -0.5, 1.0);
    const M3d::Vec4 max(+0.5, +0.5, +0.5, 1.0);
    return Glycerin::AxisAlignedBoundingBox(min, max);
}

/**
 * Creates the buffer layout keeping track of where data is in the VBO.
 */
Glycerin::BufferLayout CubeNode::createBufferLayout() {
    return Glycerin::BufferLayoutBuilder()
            .count(VERTEX_COUNT)
            .interleaved(true)
            .components(3)
            .region("POINT")
            .region("COORDINATE")
            .build();
}

/**
 * Creates the list of texture coordinates for each corner.
 */
std::vector<M3d::Vec3> CubeNode::createCoords() {
    std::vector<M3d::Vec3> coords;
    coords.push_back(M3d::Vec3(0, 0, 1));
    coords.push_back(M3d::Vec3(1, 0, 1));
    coords.push_back(M3d::Vec3(0, 1, 1));
    coords.push_back(M3d::Vec3(1, 1, 1));
    coords.push_back(M3d::Vec3(0, 0, 0));
    coords.push_back(M3d::Vec3(1, 0, 0));
    coords.push_back(M3d::Vec3(0, 1, 0));
    coords.push_back(M3d::Vec3(1, 1, 0));
    return coords;
}

/**
 * Creates the list of indices determining which triangle vertices correspond to which corners.
 */
std::vector<int> CubeNode::createIndices() {

    int arr[] = {
            3, 2, 0,
            0, 1, 3,
            2, 6, 4,
            4, 0, 2,
            7, 3, 1,
            1, 5, 7,
            6, 7, 5,
            5, 4, 6,
            7, 6, 2,
            2, 3, 7,
            1, 0, 4,
            4, 5, 1 };


    std::vector<int> indices;
    for (int i = 0; i < VERTEX_COUNT; ++i) {
        indices.push_back(arr[i]);
    }
    return indices;
}

/**
 * Creates the list of points for each corner.
 */
std::vector<M3d::Vec3> CubeNode::createPoints() {
    std::vector<M3d::Vec3> points;
    points.push_back(M3d::Vec3(-0.5, -0.5, +0.5));
    points.push_back(M3d::Vec3(+0.5, -0.5, +0.5));
    points.push_back(M3d::Vec3(-0.5, +0.5, +0.5));
    points.push_back(M3d::Vec3(+0.5, +0.5, +0.5));
    points.push_back(M3d::Vec3(-0.5, -0.5, -0.5));
    points.push_back(M3d::Vec3(+0.5, -0.5, -0.5));
    points.push_back(M3d::Vec3(-0.5, +0.5, -0.5));
    points.push_back(M3d::Vec3(+0.5, +0.5, -0.5));
    return points;
}

double CubeNode::intersect(const Glycerin::Ray& ray) const {
    return boundingBox.intersect(ray);
}

void CubeNode::preVisit(State& state) {

    // Skip if already ready
    if (ready) {
        return;
    }

    // Find use node
    const UseNode* useNode = findAncestor<UseNode>(this);
    if (useNode == NULL) {
        throw std::runtime_error("[CubeNode] Could not find use node!");
    }

    // Get program
    const ProgramNode* programNode = useNode->getProgramNode();
    if (programNode == NULL) {
        throw std::runtime_error("[CubeNode] Use node has not been visited yet!");
    }
    const Gloop::Program program = programNode->getProgram();

    // Find attribute locations by usage
    std::map<AttributeNode::Usage,GLint> locationsByUsage;
    const node_range_t children = programNode->getChildren();
    for (node_iterator_t it = children.begin; it != children.end; ++it) {
        const AttributeNode* attributeNode = dynamic_cast<AttributeNode*>(*it);
        if (attributeNode != NULL) {
            const GLint location = program.attribLocation(attributeNode->getName());
            if (location != -1) {
                locationsByUsage[attributeNode->getUsage()] = location;
            }
        }
    }

    // Bind VAO
    vao.bind();

    // Bind buffer
    arrayBuffer.bind(vbo);

    // Bind attributes
    for (Glycerin::BufferLayout::const_iterator it = layout.begin(); it != layout.end(); ++it) {
        const AttributeNode::Usage usage = AttributeNode::parseUsage(it->name());
        if (containsKey(locationsByUsage, usage)) {
            const GLint location = getValueOfKey(locationsByUsage, usage);
            vao.enableVertexAttribArray(location);
            vao.vertexAttribPointer(Gloop::VertexAttribPointer()
                    .index(location)
                    .size(it->components())
                    .offset(it->offset())
                    .stride(it->stride()));
        }
    }

    // Unbind buffer
    arrayBuffer.unbind(vbo);

    // Unbind VAO
    vao.unbind();

    // Ready
    ready = true;
}

void CubeNode::visit(State& state) {
    vao.bind();
    glDrawArrays(GL_TRIANGLES, 0, VERTEX_COUNT);
    vao.unbind();
}

} /* namespace RapidGL */
