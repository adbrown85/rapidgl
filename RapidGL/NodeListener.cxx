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
#include "RapidGL/NodeListener.h"
namespace RapidGL {

/**
 * Constructs a `NodeListener`.
 */
NodeListener::NodeListener() {
    // empty
}

/**
 * Destructs a `NodeListener`.
 */
NodeListener::~NodeListener() {
    // empty
}

/**
 * Responds to a node being changed.
 *
 * @param node Node that changed
 */
void NodeListener::nodeChanged(Node* node) {
    // empty
}

} /* namespace RapidGL */
