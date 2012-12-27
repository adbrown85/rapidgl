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
#include "RapidGL/AttributeNodeUnmarshaller.hxx"
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
    if (Poco::icompare(usage, "vertex") == 0) {
        return AttributeNode::VERTEX;
    } else if (Poco::icompare(usage, "normal") == 0) {
        return AttributeNode::NORMAL;
    } else if (Poco::icompare(usage, "coordinate") == 0) {
        return AttributeNode::COORDINATE;
    } else {
        throw std::runtime_error("[AttributeNodeUnmarshaller] Usage is invalid!");
    }
}

Node* AttributeNodeUnmarshaller::unmarshal(const std::map<std::string,std::string>& attributes) {
    const std::string name = getName(attributes);
    const AttributeNode::Usage usage = getUsage(attributes);
    return new AttributeNode(name, usage);
}

} /* namespace RapidGL */
