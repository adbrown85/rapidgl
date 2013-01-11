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
#include "Poco/String.h"
#include "RapidGL/AttachmentNodeUnmarshaller.hxx"
using std::map;
using std::string;
namespace RapidGL {

// Map of delegates indexed by their type
const map<string,Unmarshaller*> AttachmentNodeUnmarshaller::DELEGATES = createDelegates();

/**
 * Constructs an `AttachmentNodeUnmarshaller`.
 */
AttachmentNodeUnmarshaller::AttachmentNodeUnmarshaller() {
    // empty
}

/**
 * Destructs an `AttachmentNodeUnmarshaller`.
 */
AttachmentNodeUnmarshaller::~AttachmentNodeUnmarshaller() {
    // empty
}

/**
 * Creates the map of delegates indexed by their type.
 *
 * @return Map of delegates indexed by their type
 */
map<string,Unmarshaller*> AttachmentNodeUnmarshaller::createDelegates() {
    map<string,Unmarshaller*> delegates;
    return delegates;
}

/**
 * Returns a pointer to a delegate for a type.
 *
 * @param type Type to find delegate for, which may be of mixed case
 * @return Pointer to the delegate, or `NULL` if could not be found
 */
Unmarshaller* AttachmentNodeUnmarshaller::findDelegate(const string& type) {
    map<string,Unmarshaller*>::const_iterator it = DELEGATES.find(Poco::toLower(type));
    if (it == DELEGATES.end()) {
        return NULL;
    } else {
        return it->second;
    }
}

/**
 * Returns the value of the _type_ attribute in a map.
 *
 * @param attributes Map to get value from
 * @return Value of _type_ attribute
 * @throws std::runtime_error if type is unspecified
 */
string AttachmentNodeUnmarshaller::getType(const map<string,string>& attributes) {
    const string type = findValue(attributes, "type");
    if (type.empty()) {
        throw std::runtime_error("[AttachmentNodeUnmarshaller] Type is unspecified!");
    } else {
        return type;
    }
}

/**
 * Returns the value of the _usage_ attribute in a map.
 *
 * @param attributes Map to get value from
 * @return Value of the attribute
 * @throws std::runtime_error if value is unspecified
 */
AttachmentNode::Usage AttachmentNodeUnmarshaller::getUsage(const map<string,string>& attributes) {

    // Find value
    const string value = findValue(attributes, "usage");
    if (value.empty()) {
        throw std::runtime_error("[AttachmentNodeUnmarshaller] Usage is unspecified!");
    }

    // Return value
    try {
        return AttachmentNode::parseUsage(value);
    } catch (std::invalid_argument& e) {
        throw std::runtime_error("[AttachmentNodeUnmarshaller] Usage is invalid!");
    }
}

Node* AttachmentNodeUnmarshaller::unmarshal(const map<std::string,std::string>& attributes) {

    // Get the type
    const string type = getType(attributes);

    // Find the delegate for the type
    Unmarshaller* delegate = findDelegate(type);
    if (delegate == NULL) {
        throw std::runtime_error("AttachmentNodeUnmarshaller] Type is unsupported!");
    }

    // Unmarshal the node
    return delegate->unmarshal(attributes);
}

} /* namespace RapidGL */
