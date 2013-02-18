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
 * @param location Desired location to bind the attribute to, or `-1` to have it be bound automatically
 * @throws invalid_argument if name is empty or location is out of range
 */
AttributeNode::AttributeNode(const std::string& name, const Usage usage, const GLint location) :
        name(name), usage(usage), location(location), prepared(false) {

    // Check name
    if (name.empty()) {
        throw std::invalid_argument("[AttributeNode] Name is empty!");
    }

    // Check location
    if ((location < -1) || (location >= getMaxVertexAttribs())) {
        throw std::invalid_argument("[AttributeNode] Location is out of range!");
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
    usagesByName["POSITION"] = POSITION;
    usagesByName["NORMAL"] = NORMAL;
    usagesByName["COLOR"] = COLOR;
    usagesByName["TEXCOORD"] = TEXCOORD;
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
    case POSITION:
        return "POSITION";
    case NORMAL:
        return "NORMAL";
    case COLOR:
        return "COLOR";
    case TEXCOORD:
        return "TEXCOORD";
    default:
        throw std::runtime_error("[AttributeNode] Unexpected enumeration!");
    }
}

/**
 * Returns the location of the attribute in the shader program.
 *
 * @return Location of the attribute in the shader program
 */
GLint AttributeNode::getLocation() const {
    return location;
}

/**
 * Returns the maximum number of vertex attributes in a shader program.
 *
 * @return Maximum number of vertex attributes in a shader program
 */
GLint AttributeNode::getMaxVertexAttribs() {
    GLint value;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &value);
    return value;
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

    // Sucessfully prepared
    prepared = true;
}

void AttributeNode::visit(State& state) {
    // empty
}

} /* namespace RapidGL */
