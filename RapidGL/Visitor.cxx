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
#include "RapidGL/Visitor.h"
namespace RapidGL {

/**
 * Constructs a node visitor from a state.
 *
 * @param state State shared between nodes
 * @throws invalid_argument if state is `NULL`
 */
Visitor::Visitor(State* state) {
    if (state == NULL) {
        throw std::invalid_argument("State is NULL!");
    }
    this->state = state;
}

/**
 * Traverses a tree of nodes calling each of their hooks in the correct order.
 *
 * @param node Root of subtree to visit
 * @throws invalid_argument if node is `NULL`
 */
void Visitor::visit(Node* node) {

    if (node == NULL) {
        throw std::invalid_argument("Node is NULL!");
    }

    // Perform actions before being visited
    node->preVisit(*state);

    // Visit the node and all its children
    node->visit(*state);
    const Node::node_range_t children = node->getChildren();
    for (Node::node_iterator_t it = children.begin; it != children.end; ++it) {
        visit(*it);
    }

    // Perform actions after being visited
    node->postVisit(*state);
}

} /* namespace RapidGL */
