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
#include <stdexcept>
#include <vector>
#include "RapidGL/UniformNodeUnmarshaller.hxx"
using std::map;
using std::runtime_error;
using std::string;
using std::vector;
namespace RapidGL {

// Map of delegates
map<string,Unmarshaller*> UniformNodeUnmarshaller::delegatesByType = createDelegatesByType();

/**
 * Constructs a uniform node unmarshaller.
 */
UniformNodeUnmarshaller::UniformNodeUnmarshaller() {
    // empty
}

/**
 * Destructs a uniform node unmarshaller.
 */
UniformNodeUnmarshaller::~UniformNodeUnmarshaller() {
    // empty
}

/**
 * Makes the map of delegate unmarshallers indexed by their types.
 *
 * @return Map of delegate unmarshallers indexed by their types
 */
map<string,Unmarshaller*> UniformNodeUnmarshaller::createDelegatesByType() {
    map<string,Unmarshaller*> delegatesByType;
    delegatesByType["float"] = new FloatUniformNodeUnmarshaller();
    delegatesByType["mat3"] = new Mat3UniformNodeUnmarshaller();
    delegatesByType["mat4"] = new Mat4UniformNodeUnmarshaller();
    delegatesByType["sampler2d"] = new Sampler2dUniformNodeUnmarshaller();
    delegatesByType["vec3"] = new Vec3UniformNodeUnmarshaller();
    delegatesByType["vec4"] = new Vec4UniformNodeUnmarshaller();
    return delegatesByType;
}

/**
 * Creates a `FloatUniformNode`.
 *
 * @param attributes Map of XML attributes
 * @return Pointer to the node
 */
Node* UniformNodeUnmarshaller::FloatUniformNodeUnmarshaller::unmarshal(const map<string,string>& attributes) {

    // Get name and value
    const std::string name = getName(attributes);
    const std::string value = getValue(attributes);

    // Make the node
    FloatUniformNode* node = new FloatUniformNode(name);
    if (value.empty()) {
        return node;
    }

    // Set value
    try {
        node->setValue(parseFloat(value));
    } catch (std::invalid_argument& e) {
        throw std::runtime_error("[UniformNodeUnmarshaller] Value is invalid!");
    }

    // Return the node
    return node;
}

/**
 * Finds the value of the _link_ attribute in a map.
 *
 * @param attributes Map of attribute keys and values
 * @return Value of the _link_ attribute
 * @throws runtime_error if value is unspecified or empty
 */
string UniformNodeUnmarshaller::getLink(const map<string,string>& attributes) {
    const string link = findValue(attributes, "link");
    if (link.empty()) {
        throw runtime_error("[UniformNodeUnmarshaller] Link is unspecified!");
    }
    return link;
}

/**
 * Finds the value of the _name_ attribute in a map.
 *
 * @param attributes Map of attribute keys and values
 * @return Value of the _name_ attribute
 * @throws runtime_error if value is unspecified or empty
 */
string UniformNodeUnmarshaller::getName(const map<string,string>& attributes) {
    const string name = findValue(attributes, "name");
    if (name.empty()) {
        throw runtime_error("[UniformNodeUnmarshaller] Name is unspecified!");
    }
    return name;
}

/**
 * Finds the value of the _type_ attribute in a map.
 *
 * @param attributes Map of attribute keys and values
 * @return Value of the _type_ attribute
 * @throws runtime_error if value is unspecified, empty, or invalid
 */
string UniformNodeUnmarshaller::getType(const map<string,string>& attributes) {
    const string type = findValue(attributes, "type");
    if (type.empty()) {
        throw runtime_error("[UniformNodeUnmarshaller] Type is unspecified!");
    } else if (!isValidType(type)) {
        throw runtime_error("[UniformNodeUnmarshaller] Type is unsupported!");
    }
    return type;
}

/**
 * Finds the value of the _usage_ attribute in a map.
 *
 * @param attributes Map of attribute keys and values
 * @return Value of the _usage_ attribute
 * @throws std::runtime_error if value is unspecified
 */
std::string UniformNodeUnmarshaller::getUsage(const map<string,string>& attributes) {
    const std::string value = findValue(attributes, "usage");
    if (value.empty()) {
        throw std::runtime_error("[UniformNodeUnmarshaller] Usage is unspecified!");
    } else {
        return value;
    }
}

/**
 * Finds the value of the _value_ attribute in a map.
 *
 * @param attributes Map of attribute keys and values
 * @return Value of the _value_ attribute
 */
string UniformNodeUnmarshaller::getValue(const map<string,string>& attributes) {
    return findValue(attributes, "value");
}

/**
 * Checks if a string represents a valid type.
 *
 * @param str String to check
 * @return `true` if string is a valid type
 */
bool UniformNodeUnmarshaller::isValidType(const string& str) {
    const map<string,Unmarshaller*>::const_iterator it = delegatesByType.find(str);
    return it != delegatesByType.end();
}

/**
 * Creates a `Mat3UniformNode`.
 *
 * @param attribute Map of XML attributes
 * @return Pointer to the node
 */
Node* UniformNodeUnmarshaller::Mat3UniformNodeUnmarshaller::unmarshal(const map<string,string>& attributes) {

    // Get name and value
    const std::string name = getName(attributes);
    const std::string value = getValue(attributes);

    // Make the node
    Mat3UniformNode* node = new Mat3UniformNode(name);
    if (value.empty()) {
        return node;
    }

    // Tokenize value
    const vector<string> tokens = tokenize(value);
    if (tokens.size() != 9) {
        throw std::runtime_error("[UniformNodeUnmarshaller] Value should have 9 tokens!");
    }

    // Parse tokens and set value
    try {
        GLfloat arr[9];
        for (int i = 0; i < 9; ++i) {
            arr[i] = parseFloat(tokens[i]);
        }
        node->setValue(M3d::Mat3::fromArrayInColumnMajor(arr));
    } catch (std::invalid_argument& e) {
        throw std::runtime_error("[UniformNodeUnmarshaller] Value is invalid!");
    }

    // Return the node
    return node;
}

/**
 * Creates a `Mat4UniformNode`.
 *
 * @param attributes Map of XML attributes
 * @return Pointer to the node
 */
Node* UniformNodeUnmarshaller::Mat4UniformNodeUnmarshaller::unmarshal(const map<string,string>& attributes) {
    try {
        const std::string name = getName(attributes);
        const Mat4UniformNode::Usage usage = Mat4UniformNode::parseUsage(getUsage(attributes));
        return new Mat4UniformNode(name, usage);
    } catch (std::invalid_argument& e) {
        throw std::runtime_error("[UniformNodeUnmarshaller] Unrecognized usage!");
    }
}

/**
 * Creates a `Sampler2dUniformNode`.
 *
 * @param attributes Map of XML attributes
 * @return Pointer to the node
 */
Node* UniformNodeUnmarshaller::Sampler2dUniformNodeUnmarshaller::unmarshal(const map<string,string>& attributes) {

    // Get name and link
    const std::string name = getName(attributes);
    const std::string link = getLink(attributes);

    // Make the node
    return new Sampler2dUniformNode(name, link);
}

Node* UniformNodeUnmarshaller::unmarshal(const map<string,string>& attributes) {
    const string type = getType(attributes);
    Unmarshaller* delegate = delegatesByType[type];
    return delegate->unmarshal(attributes);
}

/**
 * Creates a `Vec3UniformNode`.
 *
 * @param attributes Map of XML attributes
 * @return Pointer to the node
 */
Node* UniformNodeUnmarshaller::Vec3UniformNodeUnmarshaller::unmarshal(const map<string,string>& attributes) {

    // Get name and value
    const std::string name = getName(attributes);
    const std::string value = getValue(attributes);

    // Make the node
    Vec3UniformNode* node = new Vec3UniformNode(name);
    if (value.empty()) {
        return node;
    }

    // Tokenize value
    const vector<string> tokens = tokenize(value);
    if (tokens.size() != 3) {
        throw std::runtime_error("[UniformNodeUnmarshaller] Value should have 3 tokens!");
    }

    // Parse tokens and set value
    try {
        M3d::Vec3 vec;
        for (int i = 0; i < 3; ++i) {
            vec[i] = parseFloat(tokens[i]);
        }
        node->setValue(vec);
    } catch (std::invalid_argument& e) {
        throw std::runtime_error("[UniformNodeUnmarshaller] Component in value could not be parsed!");
    }

    // Return the node
    return node;
}

/**
 * Creates a `Vec4UniformNode`.
 *
 * @param attributes Map of XML attributes
 * @return Pointer to the node
 */
Node* UniformNodeUnmarshaller::Vec4UniformNodeUnmarshaller::unmarshal(const map<string,string>& attributes) {

    // Get name and value
    const std::string name = getName(attributes);
    const std::string value = getValue(attributes);

    // Make the node
    Vec4UniformNode* node = new Vec4UniformNode(name);
    if (value.empty()) {
        return node;
    }

    // Tokenize value
    const vector<string> tokens = tokenize(value);
    if (tokens.size() != 4) {
        throw std::runtime_error("[UniformNodeUnmarshaller] Value should have 4 tokens!");
    }

    // Parse tokens and set value
    try {
        M3d::Vec4 vec;
        for (int i = 0; i < 4; ++i) {
            vec[i] = parseFloat(tokens[i]);
        }
        node->setValue(vec);
    } catch (std::invalid_argument& e) {
        throw std::runtime_error("[UniformNodeUnmarshaller] Value is invalid!");
    }

    // Return the node
    return node;
}

} /* namespace RapidGL */
