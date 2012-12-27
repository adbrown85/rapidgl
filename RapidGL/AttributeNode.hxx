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
#ifndef RAPIDGL_ATTRIBUTENODE_HXX
#define RAPIDGL_ATTRIBUTENODE_HXX
#include <set>
#include <string>
#include "RapidGL/common.h"
#include "RapidGL/Node.hxx"
#include "RapidGL/ProgramNode.hxx"
#include "RapidGL/State.hxx"
namespace RapidGL {


/**
 * Description of a shader attribute and how it should be used.
 */
class AttributeNode : public Node {
public:
// Types
    /// How an attribute should be used.
    enum Usage {
        VERTEX, ///< As a vertex
        NORMAL, ///< As a normal
        COORDINATE ///< As a texture coordinate
    };
// Methods
    AttributeNode(const std::string& name, Usage usage);
    virtual ~AttributeNode();
    std::string getName() const;
    Usage getUsage() const;
    virtual void preVisit(State& state);
private:
// Attributes
    bool prepared;
    Usage usage;
    std::string name;
};

} /* namespace RapidGL */
#endif
