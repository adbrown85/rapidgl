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
#ifndef RAPIDGL_NODE_LISTENER_H
#define RAPIDGL_NODE_LISTENER_H
#include "RapidGL/common.h"
namespace RapidGL {


// Forward declaration of `Node`
class Node;


/**
 * Observer of a `Node`.
 */
class NodeListener {
public:
// Methods
    virtual void nodeChanged(Node* node) = 0;
protected:
// Methods
    NodeListener();
    virtual ~NodeListener();
private:
// Methods
    NodeListener(const NodeListener& nodeListener);
    NodeListener& operator=(const NodeListener& nodeListener);
};

} /* namespace RapidGL */
#endif
