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
#include "RapidGL/GroupNode.h"
namespace RapidGL {

/**
 * Constructs a `GroupNode`.
 *
 * @param id Identifier of the group
 * @throws std::invalid_argument if identifier is empty
 */
GroupNode::GroupNode(const std::string& id) : Node(id) {
    if (id.empty()) {
        throw std::invalid_argument("[GroupNode] Identifier is empty!");
    }
}

/**
 * Destructs a `GroupNode`.
 */
GroupNode::~GroupNode() {
    // empty
}

void GroupNode::visit(State& state) {
    // empty
}

} /* namespace RapidGL */
