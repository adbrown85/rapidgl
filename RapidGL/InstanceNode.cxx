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
#include <stdexcept>
#include "RapidGL/InstanceNode.h"
namespace RapidGL {

/**
 * Constructs an `InstanceNode`.
 *
 * @param link Identifier of group to instance
 * @throws std::invalid_argument if link is empty
 */
InstanceNode::InstanceNode(const std::string& link) : link(link), groupNode(NULL), ready(false) {
    if (link.empty()) {
        throw std::invalid_argument("[InstanceNode] Link is empty!");
    }
}

/**
 * Destructs an `InstanceNode`.
 */
InstanceNode::~InstanceNode() {
    // empty
}

/**
 * Returns the identifier of the group being instanced.
 *
 * @return Identifier of the group being instanced
 */
std::string InstanceNode::getLink() const {
    return link;
}

void InstanceNode::preVisit(State& state) {

    // Skip if already ready
    if (ready) {
        return;
    }

    // Find root
    const Node* root = findRoot(this);

    // Find node
    Node* node = findDescendant(root, link);
    if (node == NULL) {
        throw std::runtime_error("[InstanceNode] Could not find node with specified ID!");
    }

    // Cast to group node
    groupNode = dynamic_cast<GroupNode*>(node);
    if (groupNode == NULL) {
        throw std::runtime_error("[InstanceNode] Node with ID is not a group node!");
    }

    // Now ready
    ready = true;
}

void InstanceNode::visit(State& state) {
    Visitor visitor(&state);
    visitor.visit(groupNode);
}

} /* namespace RapidGL */
