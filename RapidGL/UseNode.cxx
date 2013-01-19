/*
 * RapidGL - Rapid prototyping for OpenGL
 * Copyright (C) 2013  Andrew Brown
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
#include "RapidGL/UseNode.h"
namespace RapidGL {

/**
 * Constructs a `UseNode` with the identifier of a program node.
 *
 * @param programNodeId Identifier of the program node to use
 * @throws std::invalid_argument if identifier is empty
 */
UseNode::UseNode(const std::string& programNodeId) :
        programNodeId(programNodeId), programNode(NULL), lastUseNode(NULL) {
    if (programNodeId.empty()) {
        throw std::invalid_argument("[UseNode] Program node ID is empty!");
    }
}

/**
 * Destructs a `UseNode`.
 */
UseNode::~UseNode() {
    // empty
}

/**
 * Returns the program node that this node uses.
 *
 * @return Program node that this node uses, or `NULL` if it hasn't been found yet
 */
ProgramNode* UseNode::getProgramNode() const {
    return programNode;
}

/**
 * Activates the program that was in use before this node.
 */
void UseNode::postVisit(State& state) {
    if (lastUseNode == NULL) {
        glUseProgram(0);
    } else {
        lastUseNode->programNode->getProgram().use();
    }
}

/**
 * Finds the program node to use and the `UseNode` above this one in the scene if any.
 */
void UseNode::preVisit(State& state) {
    
    // Skip if already found program node
    if (programNode != NULL) {
        return;
    }

    // Find the root of the scene
    Node* root = findRoot(this);
    if (root == this) {
        throw std::runtime_error("[UseNode] Use node should not be root of scene!");
    }

    // Find a node with the ID
    Node* node = findDescendant(root, programNodeId);
    if (node == NULL) {
        throw std::runtime_error("[UseNode] Could not find node with specified identifier!");
    }

    // Store it as the program node
    programNode = dynamic_cast<ProgramNode*>(node);
    if (programNode == NULL) {
        throw std::runtime_error("[UseNode] Node is not a program node!");
    }

    // Find the last use node
    lastUseNode = findAncestor<UseNode>(this);
}

/**
 * Activates the program of the specified `ProgramNode`.
 */
void UseNode::visit(State& state) {
    programNode->getProgram().use();
}

} /* namespace RapidGL */
