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
#include "RapidGL/ProgramNode.h"
namespace RapidGL {

/**
 * Constructs a program node.
 *
 * @param id Identifier of node, which may be empty
 * @throws std::invalid_argument if identifier is empty
 */
ProgramNode::ProgramNode(const std::string& id) : Node(id), program(Gloop::Program::create()) {
    prepared = false;
    if (id.empty()) {
        throw std::invalid_argument("[ProgramNode] Identifier is empty!");
    }
}

/**
 * Destructs this program node.
 */
ProgramNode::~ProgramNode() {
    program.dispose();
}

/**
 * Finds a program node for a program.
 *
 * @param root Root of tree to look in
 * @param program Program to look for
 * @return Program node with program, or `NULL` if not found
 */
const ProgramNode* findProgramNode(const Node* root, const Gloop::Program& program) {

    // Create a queue and push the root into it
    std::queue<const Node*> q;
    q.push(root);

    // Look for program node with program
    while (!q.empty()) {
        const Node* node = q.front();
        const ProgramNode* programNode = dynamic_cast<const ProgramNode*>(node);
        if ((programNode != NULL) && (programNode->getProgram() == program)) {
            return programNode;
        }
        addToQueue(q, node->getChildren());
        q.pop();
    }

    // Not found
    return NULL;
}

/**
 * Returns the underlying OpenGL shader program.
 *
 * @return Underlying OpenGL shader program
 */
Gloop::Program ProgramNode::getProgram() const {
    return program;
}

void ProgramNode::preVisit(State& state) {

    // Skip if already prepared
    if (prepared) {
        return;
    }

    // Get children
    const node_range_t children = getChildren();

    // Find and attach shaders
    for (node_iterator_t it = children.begin; it != children.end; ++it) {
        ShaderNode* const shaderNode = dynamic_cast<ShaderNode*>(*it);
        if (shaderNode != NULL) {
            program.attachShader(shaderNode->getShader());
        }
    }

    // Find and bind attributes
    for (node_iterator_t it = children.begin; it != children.end; ++it) {
        AttributeNode* const attributeNode = dynamic_cast<AttributeNode*>(*it);
        if (attributeNode != NULL) {
            const GLint location = attributeNode->getLocation();
            if (location != -1) {
                program.attribLocation(attributeNode->getName(), location);
            }
        }
    }

    // Link
    program.link();
    if (!program.linked()) {
        throw std::runtime_error("[ProgramNode] Program could not be linked!");
    }

    // Check for invalid attributes
    for (node_iterator_t it = children.begin; it != children.end; ++it) {
        AttributeNode* const attributeNode = dynamic_cast<AttributeNode*>(*it);
        if (attributeNode != NULL) {
            const GLint location = program.attribLocation(attributeNode->getName());
            if (location == -1) {
                throw std::runtime_error("[ProgramNode] Attribute is not in program!");
            } else {
                attributeNode->location = location;
            }
        }
    }

    // Successfully prepared
    prepared = true;
}

void ProgramNode::visit(State& state) {
    // empty
}

} /* namespace RapidGL */
