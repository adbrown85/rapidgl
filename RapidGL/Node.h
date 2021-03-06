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
#ifndef RAPIDGL_NODE_H
#define RAPIDGL_NODE_H
#include <queue>
#include <string>
#include <stdexcept>
#include <vector>
#include "RapidGL/common.h"
#include "RapidGL/NodeListener.h"
#include "RapidGL/State.h"
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
    Node(const std::string& id = "");
    virtual ~Node();
    void addChild(Node* node);
    void addNodeListener(NodeListener* nodeListener);
    node_range_t getChildren() const;
    std::string getId() const;
    Node* getParent() const;
    bool hasChildren() const;
    bool hasId() const;
    virtual void postVisit(State& state);
    virtual void preVisit(State& state);
    bool removeChild(Node* node);
    bool removeNodeListener(NodeListener* nodeListener);
    virtual void visit(State& state) = 0;
protected:
// Methods
    void fireNodeChangedEvent();
private:
// Attributes
    std::vector<Node*> children;
    std::string id;
    Node* parent;
    std::vector<NodeListener*> nodeListeners;
// Methods
    Node(const Node& node);
    Node& operator=(const Node& node);
};

/**
 * Adds a range of nodes to a queue.
 *
 * @param q Queue to add to
 * @param nodes Range of nodes to add to queue
 */
template<typename T>
void addToQueue(std::queue<T>& q, const Node::node_range_t& nodes) {
    for (Node::node_iterator_t it = nodes.begin; it != nodes.end; ++it) {
        q.push(*it);
    }
}

/**
 * Finds an ancestor of a particular type.
 *
 * @param node Node to find ancestor of
 * @return Ancestor of node, or `NULL` if one of appropriate type is not found
 * @throws invalid_argument if node is `NULL`
 */
template<typename T>
T* findAncestor(const Node* node) {

    if (node == NULL) {
        throw std::invalid_argument("Node is null!");
    }

    Node* ptr = node->getParent();
    while (ptr != NULL) {
        T* t = dynamic_cast<T*>(ptr);
        if (t != NULL) {
            return t;
        }
        ptr = ptr->getParent();
    }

    return NULL;
}

/**
 * Finds an ancestor of a particular type and identifier.
 *
 * @param node Node to find ancestor of
 * @param id Identifier of ancestor node to find
 * @return Ancestor of node, or `NULL` if one of appropriate type and identifier is not found
 * @throws invalid_argument if node is `NULL` or identifier is empty
 */
template<typename T>
T* findAncestor(const Node* node, const std::string& id) {

    if (node == NULL) {
        throw std::invalid_argument("Node is null!");
    } else if (id.empty()) {
        throw std::invalid_argument("Identifier is empty!");
    }

    Node* ptr = node->getParent();
    while (ptr != NULL) {
        if (ptr->getId() == id) {
            T* t = dynamic_cast<T*>(ptr);
            if (t != NULL) {
                return t;
            }
        }
        ptr = ptr->getParent();
    }

    return NULL;
}

Node* findDescendant(const Node* root, const std::string& id);

Node* findRoot(Node* node);

} /* namespace RapidGL */

std::ostream& operator<<(std::ostream& stream, const RapidGL::Node& node);
#endif
