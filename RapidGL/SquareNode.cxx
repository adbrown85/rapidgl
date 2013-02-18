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
#include <stdexcept>
#include <utility>
#include <glycerin/BufferLayoutBuilder.hxx>
#include <glycerin/BufferRegion.hxx>
#include "RapidGL/SquareNode.h"
using std::map;
using std::string;
namespace RapidGL {

const Gloop::BufferTarget SquareNode::arrayBuffer = Gloop::BufferTarget::arrayBuffer();
const Glycerin::BufferLayout SquareNode::bufferLayout = createBufferLayout();

/**
 * Constructs a square node.
 */
SquareNode::SquareNode() :
        prepared(false),
        boundingBox(createBoundingBox()),
        vbo(Gloop::BufferObject::generate()) {

    // Bind the VBO
    arrayBuffer.bind(vbo);

    // Allocate buffer
    arrayBuffer.data(bufferLayout.sizeInBytes(), NULL, GL_STATIC_DRAW);

    // Add vertices
    const Glycerin::BufferRegion vertexRegion = *(bufferLayout.find("POSITION"));
    GLfloat points[COUNT][2] = { { +0.5f, +0.5f },
                                 { -0.5f, +0.5f },
                                 { -0.5f, -0.5f },
                                 { +0.5f, +0.5f },
                                 { -0.5f, -0.5f },
                                 { +0.5f, -0.5f } };
    arrayBuffer.subData(vertexRegion.offset(), vertexRegion.sizeInBytes(), points);

    // Add coordinates
    const Glycerin::BufferRegion coordRegion = *(bufferLayout.find("TEXCOORD"));
    GLfloat coords[COUNT][2] = { { 1.0f, 1.0f },
                                 { 0.0f, 1.0f },
                                 { 0.0f, 0.0f },
                                 { 1.0f, 1.0f },
                                 { 0.0f, 0.0f },
                                 { 1.0f, 0.0f } };
    arrayBuffer.subData(coordRegion.offset(), coordRegion.sizeInBytes(), coords);

    // Unbind the VBO
    arrayBuffer.unbind(vbo);
}

/**
 * Destructs this square node.
 */
SquareNode::~SquareNode() {
    forEachValue(vaos, &disposeVertexArrayObject);
    vbo.dispose();
}

/**
 * Creates the bounding box that a square node delegates to for intersection tests.
 */
Glycerin::AxisAlignedBoundingBox SquareNode::createBoundingBox() {
    const M3d::Vec4 min(-0.5, -0.5, 0.0, 1.0);
    const M3d::Vec4 max(+0.5, +0.5, 0.0, 1.0);
    return Glycerin::AxisAlignedBoundingBox(min, max);
}

/**
 * Creates the buffer layout.
 */
Glycerin::BufferLayout SquareNode::createBufferLayout() {
    return Glycerin::BufferLayoutBuilder()
        .count(COUNT)
        .components(2)
        .region("POSITION")
        .region("TEXCOORD")
        .build();
}

Gloop::VertexArrayObject SquareNode::createVertexArrayObject(const Gloop::Program& program) {

    // Find the program node for the program
    const Node* root = findRoot(this);
    const ProgramNode* programNode = findProgramNode(root, program);
    if (programNode == NULL) {
        throw std::runtime_error("[SquareNode] Could not find program node for program!");
    }

    // Generate a VAO
    const Gloop::VertexArrayObject vao = Gloop::VertexArrayObject::generate();

    // Look for attributes
    map<string,string> namesByUsage;
    node_range_t programNodeChildren = programNode->getChildren();
    for (node_iterator_t it = programNodeChildren.begin; it != programNodeChildren.end; ++it) {
        const AttributeNode* attributeNode = dynamic_cast<const AttributeNode*>(*it);
        if (attributeNode != NULL) {
            const string name = attributeNode->getName();
            const string usage = AttributeNode::formatUsage(attributeNode->getUsage());
            namesByUsage[usage] = name;
        }
    }

    // Bind VAO and VBO
    vao.bind();
    arrayBuffer.bind(vbo);

    // Set up VAO
    for (Glycerin::BufferLayout::const_iterator it = bufferLayout.begin(); it != bufferLayout.end(); ++it) {
        const string usage = it->name();
        if (containsKey(namesByUsage, usage)) {
            const string name = getValueOfKey(namesByUsage, usage);
            const GLint location = program.attribLocation(name);
            if (location != -1) {
                vao.enableVertexAttribArray(location);
                vao.vertexAttribPointer(Gloop::VertexAttribPointer()
                        .index(location)
                        .size(it->components())
                        .type(it->type())
                        .normalized(it->normalized())
                        .stride(it->stride())
                        .offset(it->offset()));
            }
        }
    }

    // Unbind
    arrayBuffer.unbind(vbo);
    vao.unbind();

    // Return VAO
    return vao;
}

/**
 * Disposes of a vertex array object.
 *
 * @param vao Vertex array object to dispose of
 */
void SquareNode::disposeVertexArrayObject(const Gloop::VertexArrayObject& vao) {
    vao.dispose();
}

Gloop::VertexArrayObject SquareNode::getVertexArrayObject(const Gloop::Program& program) {

    // Check if already made VAO for program
    std::map<Gloop::Program,Gloop::VertexArrayObject>::const_iterator it = vaos.find(program);
    if (it != vaos.end()) {
        return it->second;
    }

    // Otherwise make VAO
    const Gloop::VertexArrayObject vao = createVertexArrayObject(program);

    // Store it for next time
    vaos.insert(std::pair<Gloop::Program,Gloop::VertexArrayObject>(program, vao));

    // Return it
    return vao;
}

double SquareNode::intersect(const Glycerin::Ray& ray) const {
    return boundingBox.intersect(ray);
}

void SquareNode::visit(State& state) {

    // Get current program
    const Gloop::Program program = Gloop::Program::current();

    // Get VAO for program and bind it
    const Gloop::VertexArrayObject vao = getVertexArrayObject(program);
    vao.bind();

    // Draw square
    glDrawArrays(GL_TRIANGLES, 0, COUNT);

    // Unbind VAO
    vao.unbind();
}

} /* namespace RapidGL */
