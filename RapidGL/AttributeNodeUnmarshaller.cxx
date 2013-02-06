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
#include <Poco/String.h>
#include <stdexcept>
#include "RapidGL/AttributeNodeUnmarshaller.h"
namespace RapidGL {

/**
 * Constructs an attribute node unmarshaller.
 */
AttributeNodeUnmarshaller::AttributeNodeUnmarshaller() {
    // empty
}

/**
 * Destructs this attribute node unmarshaller.
 */
AttributeNodeUnmarshaller::~AttributeNodeUnmarshaller() {
    // empty
}

/**
 * Returns the value of _location_ attribute in a map.
 *
 * @param attributes Map of attributes to look in
 * @return Value of the attribute in map
 * @throws std::runtime_error if value is unspecified
 */
GLint AttributeNodeUnmarshaller::getLocation(const std::map<std::string,std::string>& attributes) {

    // Find value
    const std::string value = findValue(attributes, "location");

    // If unspecified let it be bound automatically
    if (value.empty()) {
        return -1;
    }

    // Otherwise parse the value
    GLint location;
    try {
        location = parseInt(value);
    } catch (std::invalid_argument& e) {
        throw std::runtime_error("[AttributeNodeUnmarshaller] Location is invalid!");
    }

    // Check that it's in range
    if ((location < 0) || (location >= getMaxVertexAttribs())) {
        throw std::runtime_error("[AttributeNodeUnmarshaller] Location is out of range!");
    }

    // Return the value
    return location;
}

/**
 * Returns the maximum number of attributes in a shader program.
 *
 * @return Maximum number of attributes in a shader program
 */
GLint AttributeNodeUnmarshaller::getMaxVertexAttribs() {
    GLint value;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &value);
    return value;
}

/**
 * Returns the value of the _name_ attribute in a map.
 *
 * @param attributes Map of attributes to look in
 * @return Value of _name_ attribute in map
 * @throws runtime_error if value is unspecified
 */
std::string AttributeNodeUnmarshaller::getName(const std::map<std::string,std::string>& attributes) {
    const std::string name = findValue(attributes, "name");
    if (name.empty()) {
        throw std::runtime_error("[AttributeNodeUnmarshaller] Name is unspecified!");
    }
    return name;
}

/**
 * Returns the value of the _usage_ attribute in a map.
 *
 * @param attributes Map of attributes to look in
 * @return Value of _usage_ attribute in map
 * @throws runtime_error if value is unspecified
 */
AttributeNode::Usage AttributeNodeUnmarshaller::getUsage(const std::map<std::string,std::string>& attributes) {

    // Get usage as string
    const std::string usage = findValue(attributes, "usage");
    if (usage.empty()) {
        throw std::runtime_error("[AttributeNodeUnmarshaller] Usage is unspecified!");
    }

    // Convert to enumeration
    try {
        return AttributeNode::parseUsage(usage);
    } catch (std::invalid_argument& e) {
        throw std::runtime_error("[AttributeNodeUnmarshaller] Usage is invalid!");
    }
}

Node* AttributeNodeUnmarshaller::unmarshal(const std::map<std::string,std::string>& attributes) {
    const std::string name = getName(attributes);
    const AttributeNode::Usage usage = getUsage(attributes);
    const GLint location = getLocation(attributes);
    return new AttributeNode(name, usage, location);
}

} /* namespace RapidGL */
