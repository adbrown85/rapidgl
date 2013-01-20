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
#include <gloop/Program.hxx>
#include <iostream>
#include <Poco/String.h>
#include <stdexcept>
#include "RapidGL/AttributeNode.h"
namespace RapidGL {

// Usages indexed by name
std::map<std::string,AttributeNode::Usage> AttributeNode::usagesByName = createUsagesByName();

/**
 * Constructs an attribute node from a name and usage.
 *
 * @param name Name of the attribute as declared in the shader
 * @param usage How the attribute is used, i.e. as a point, normal, or texture coordinate
 * @throws invalid_argument if name is empty
 */
AttributeNode::AttributeNode(const std::string& name, const Usage usage) : name(name), usage(usage), prepared(false) {
    if (name.empty()) {
        throw std::invalid_argument("[AttributeNode] Name is empty!");
    }
}

/**
 * Destructs this attribute node.
 */
AttributeNode::~AttributeNode() {
    // empty
}

/**
 * Makes the map of usages indexed by name.
 */
std::map<std::string,AttributeNode::Usage> AttributeNode::createUsagesByName() {
    std::map<std::string,AttributeNode::Usage> usagesByName;
    usagesByName["POINT"] = POINT;
    usagesByName["NORMAL"] = NORMAL;
    usagesByName["COORDINATE"] = COORDINATE;
    return usagesByName;
}

/**
 * Converts a usage to a string.
 *
 * @param usage Usage to convert
 * @return String corresponding to usage
 */
std::string AttributeNode::formatUsage(const Usage usage) {
    switch (usage) {
    case POINT:
        return "POINT";
    case NORMAL:
        return "NORMAL";
    case COORDINATE:
        return "COORDINATE";
    default:
        throw std::runtime_error("[AttributeNode] Unexpected enumeration!");
    }
}

/**
 * Returns the name of the attribute as declared in the shader.
 *
 * @return Name of the attribute as declared in the shader
 */
std::string AttributeNode::getName() const {
    return name;
}

/**
 * Returns how the attribute should be used, either for vertices, normals, or texture coordinates.
 *
 * @return How the attribute should be used, either for vertices, normals, or texture coordianates
 */
AttributeNode::Usage AttributeNode::getUsage() const {
    return usage;
}

/**
 * Parses a usage from a string.
 *
 * @param str String to parse
 * @return Corresponding usage for string
 * @throws std::invalid_argument if string could not be parsed as a valid usage
 */
AttributeNode::Usage AttributeNode::parseUsage(const std::string& str) {
    const std::string strAsUpper = Poco::toUpper(str);
    const std::map<std::string,Usage>::const_iterator it = usagesByName.find(strAsUpper);
    if (it == usagesByName.end()) {
        throw std::invalid_argument("[AttributeNode] Could not parse string as a valid usage!");
    } else {
        return it->second;
    }
}

void AttributeNode::preVisit(State& state) {

    // Skip if already prepared
    if (prepared) {
        return;
    }

    // Get parent
    const Node* parent = getParent();
    if (parent == NULL) {
        throw std::runtime_error("[AttributeNode] Attribute node does not have a parent!");
    }

    // Cast parent to program node
    const ProgramNode* parentAsProgramNode = dynamic_cast<const ProgramNode*>(parent);
    if (parentAsProgramNode == NULL) {
        throw std::runtime_error("[AttributeNode] Parent of attribute node is not a program node!");
    }

    // Check if attribute is in program
    const Gloop::Program program = parentAsProgramNode->getProgram();
    const GLint location = program.attribLocation(name);
    if (location == -1) {
        throw std::runtime_error("[AttributeNode] Attribute is not in program!");
    }

    // Sucessfully prepared
    prepared = true;
}

void AttributeNode::visit(State& state) {
    // empty
}

} /* namespace RapidGL */
