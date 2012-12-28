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
#ifndef RAPIDGL_NODE_HXX
#define RAPIDGL_NODE_HXX
#include <vector>
#include <string>
#include <stdexcept>
#include "RapidGL/common.h"
#include "RapidGL/State.hxx"
namespace RapidGL {


/**
 * Element in a RapidGL scene graph.
 */
class Node {
public:
// Types
    typedef std::vector<Node*>::const_iterator node_iterator_t; ///< Node iterator
    typedef Range<node_iterator_t> node_range_t; ///< Pair of node iterators
// Methods
    Node();
    Node(const std::string& id);
    virtual ~Node();
    void addChild(Node* node);
    node_range_t getChildren() const;
    std::string getId() const;
    Node* getParent() const;
    bool hasChildren() const;
    bool hasId() const;
    virtual void postVisit(State& state);
    virtual void preVisit(State& state);
    bool removeChild(Node* node);
    virtual void visit(State& state);
private:
// Attributes
    std::vector<Node*> children;
    std::string id;
    Node* parent;
// Methods
    Node(const Node& node);
    Node& operator=(const Node& node);
};

/**
 * Finds an ancestor of a particular type.
 *
 * @param node Node to find ancestor of
 * @return Ancestor of node, or `NULL` if one of appropriate type is not found
 * @throws invalid_argument if node is `NULL`
 */
template<typename T>
T* findAncestor(Node* node) {

    if (node == NULL) {
        throw std::invalid_argument("Node is null!");
    }

    node = node->getParent();
    while (node != NULL) {
        T* t = dynamic_cast<T*>(node);
        if (t != NULL) {
            return t;
        }
        node = node->getParent();
    }

    return NULL;
}

} /* namespace RapidGL */

std::ostream& operator<<(std::ostream& stream, const RapidGL::Node& node);
#endif
