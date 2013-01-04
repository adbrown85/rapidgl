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
#include <algorithm>
#include <stdexcept>
#include "RapidGL/Node.hxx"
namespace RapidGL {

/**
 * Constructs a node with no identifier.
 */
Node::Node() : parent(NULL) {
    // empty
}

/**
 * Constructs a node with an identifer.
 *
 * @param id Identifier, which may be empty
 */
Node::Node(const std::string& id) : id(id), parent(NULL) {
    // empty
}

/**
 * Destructs this node.
 */
Node::~Node() {
    // empty
}

/**
 * Adds a node as a child of this node.
 *
 * @param node Pointer to the node to add as a child of this node
 * @throws invalid_argument if node is `NULL`
 */
void Node::addChild(Node* const node) {
    if (node == NULL) {
        throw std::invalid_argument("[Node] Child node is NULL!");
    }
    children.push_back(node);
    node->parent = this;
}

/**
 * Returns a pair of iterators for accessing this node's children.
 *
 * @return Pair of iterators for accessing this node's children
 */
Node::node_range_t Node::getChildren() const {
    return node_range_t(children.begin(), children.end());
}

/**
 * Returns a copy of this node's identifier.
 *
 * @return Copy of this node's identifier
 */
std::string Node::getId() const {
    return id;
}

/**
 * Returns a pointer to this node's parent.
 *
 * @return Pointer to this node's parent, which may be `NULL`
 */
Node* Node::getParent() const {
    return parent;
}

/**
 * Checks if this node has any children.
 *
 * @return `true` if this node has any children
 */
bool Node::hasChildren() const {
    return !children.empty();
}

/**
 * Checks if this node has a non-empty identifier.
 *
 * @return `true` if this node has a non-empty identifier
 */
bool Node::hasId() const {
    return !id.empty();
}

/**
 * Performs an action after this node and all its children have been visited.
 *
 * @param state State shared between nodes
 */
void Node::postVisit(State& state) {
    // empty
}

/**
 * Performs an action before this node is visited.
 *
 * @param state State shared between nodes
 */
void Node::preVisit(State& state) {
    // empty
}

/**
 * Removes a child from this node.
 *
 * @param node Child node to remove
 * @return `true` if child node was successfully removed
 */
bool Node::removeChild(Node* const node) {

    if (node == NULL) {
        throw std::invalid_argument("[Node] Child node is NULL!");
    }

    // Find the child node
    std::vector<Node*>::iterator it = std::find(children.begin(), children.end(), node);
    if (it == children.end()) {
        return false;
    }

    // Remove it
    children.erase(it);
    (*it)->parent = NULL;
    return true;
}

/**
 * Performs an action.
 *
 * @param state State shared between nodes
 */
void Node::visit(State& state) {
    // empty
}

} /* namespace RapidGL */

std::ostream& operator<<(std::ostream& stream, const RapidGL::Node& node) {
    stream << node.getId();
    return stream;
}
