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
#include <glycerin/BufferLayoutBuilder.hxx>
#include <glycerin/BufferRegion.hxx>
#include "RapidGL/SquareNode.hxx"
using std::map;
using std::string;
namespace RapidGL {

Gloop::BufferTarget SquareNode::arrayBuffer = Gloop::BufferTarget::arrayBuffer();
Glycerin::BufferLayout SquareNode::bufferLayout = createBufferLayout();

/**
 * Constructs a square node.
 */
SquareNode::SquareNode() :
        prepared(false),
        vao(Gloop::VertexArrayObject::generate()),
        vbo(Gloop::BufferObject::generate()) {

    // Bind the VBO
    arrayBuffer.bind(vbo);

    // Allocate buffer
    arrayBuffer.data(bufferLayout.sizeInBytes(), NULL, GL_STATIC_DRAW);

    // Add vertices
    const Glycerin::BufferRegion vertexRegion = *(bufferLayout.find("POINT"));
    GLfloat points[COUNT][2] = { { +0.5f, +0.5f },
                                 { -0.5f, +0.5f },
                                 { -0.5f, -0.5f },
                                 { +0.5f, +0.5f },
                                 { -0.5f, -0.5f },
                                 { +0.5f, -0.5f } };
    arrayBuffer.subData(vertexRegion.offset(), vertexRegion.sizeInBytes(), points);

    // Add coordinates
    const Glycerin::BufferRegion coordRegion = *(bufferLayout.find("COORDINATE"));
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
    vao.dispose();
    vbo.dispose();
}

/**
 * Creates the buffer layout.
 */
Glycerin::BufferLayout SquareNode::createBufferLayout() {
    return Glycerin::BufferLayoutBuilder()
        .count(COUNT)
        .components(2)
        .region("POINT")
        .region("COORDINATE")
        .build();
}

void SquareNode::preVisit(State& state) {

    // Skip if already prepared
    if (prepared) {
        return;
    }

    // Find the program
    const ProgramNode* programNode = findAncestor<ProgramNode>(this);
    if (programNode == NULL) {
        throw std::runtime_error("[SquareNode] Could not find program!");
    }
    Gloop::Program program = programNode->getProgram();

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

    // Successfully prepared
    prepared = true;
}

void SquareNode::visit(State& state) {
    vao.bind();
    glDrawArrays(GL_TRIANGLES, 0, COUNT);
}

} /* namespace RapidGL */
