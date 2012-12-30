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
#include <sstream>
#include "RapidGL/UniformNodeUnmarshaller.hxx"
using std::map;
using std::runtime_error;
using std::string;
using std::stringstream;
using std::vector;
namespace RapidGL {

// Map of creators
map<string,UniformNodeUnmarshaller::Creator*> UniformNodeUnmarshaller::creatorsByType = createCreatorsByType();

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
 * Makes the map of node creator functors indexed by their types.
 *
 * @return Map of node creator functors indexed by their types
 */
map<string,UniformNodeUnmarshaller::Creator*> UniformNodeUnmarshaller::createCreatorsByType() {
    map<string,Creator*> creatorsByType;
    creatorsByType["float"] = new FloatUniformNodeCreator();
    creatorsByType["mat3"] = new Mat3UniformNodeCreator();
    creatorsByType["mat4"] = new Mat4UniformNodeCreator();
    creatorsByType["vec3"] = new Vec3UniformNodeCreator();
    creatorsByType["vec4"] = new Vec4UniformNodeCreator();
    return creatorsByType;
}

/**
 * Creates a `FloatUniformNode`.
 *
 * @param name Name of the uniform as declared in the shader
 * @param value Initial value of uniform as a string
 * @return Pointer to the node
 */
Node* UniformNodeUnmarshaller::FloatUniformNodeCreator::create(const string& name, const string& value) const {

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
    const map<string,Creator*>::const_iterator it = creatorsByType.find(str);
    return it != creatorsByType.end();
}

/**
 * Creates a `Mat3UniformNode`.
 *
 * @param name Name of the uniform as declared in the shader
 * @param value Initial value of uniform as a string
 * @return Pointer to the node
 */
Node* UniformNodeUnmarshaller::Mat3UniformNodeCreator::create(const string& name, const string& value) const {

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
 * @param name Name of the uniform as declared in the shader
 * @param value Initial value of uniform as a string
 * @return Pointer to the node
 */
Node* UniformNodeUnmarshaller::Mat4UniformNodeCreator::create(const string& name, const string& value) const {

    // Make the node
    Mat4UniformNode* node = new Mat4UniformNode(name);
    if (value.empty()) {
        return node;
    }

    // Tokenize value
    const vector<string> tokens = tokenize(value);
    if (tokens.size() != 16) {
        throw std::runtime_error("[UniformNodeUnmarshaller] Value should have 16 tokens!");
    }

    // Parse tokens and set value
    try {
        GLfloat arr[16];
        for (int i = 0; i < 16; ++i) {
            arr[i] = parseFloat(tokens[i]);
        }
        node->setValue(M3d::Mat4::fromArrayInColumnMajor(arr));
    } catch (std::invalid_argument& e) {
        throw std::runtime_error("[UniformNodeUnmarshaller] Value is invalid!");
    }

    // Return the node
    return node;
}

/**
 * Parses a float from a string.
 *
 * @param str String to parse
 * @return Float parsed from string
 * @throws invalid_argument if string cannot be parsed as a valid float
 */
GLfloat UniformNodeUnmarshaller::parseFloat(const string& str) {
    stringstream stream(str);
    GLfloat value;
    stream >> value;
    if (stream.fail()) {
        throw std::invalid_argument("[UniformNodeUnmarshaller] String is not a valid float!");
    } else {
        return value;
    }
}

/**
 * Breaks up a string into tokens.
 *
 * @param str String to break up into tokens
 * @return Vector of tokens
 */
vector<string> UniformNodeUnmarshaller::tokenize(const string& str) {
    vector<string> tokens;
    stringstream stream(str);
    string token;
    stream >> token;
    while (stream) {
        tokens.push_back(token);
        stream >> token;
    }
    return tokens;
}

Node* UniformNodeUnmarshaller::unmarshal(const map<string,string>& attributes) {
    const string type = getType(attributes);
    const string name = getName(attributes);
    const string value = getValue(attributes);
    const Creator* creator = creatorsByType[type];
    return creator->create(name, value);
}

/**
 * Creates a `Vec3UniformNode`.
 *
 * @param name Name of the uniform as declared in the shader
 * @param value Initial value of uniform as a string
 * @return Pointer to the node
 */
Node* UniformNodeUnmarshaller::Vec3UniformNodeCreator::create(const string& name, const string& value) const {

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
 * @param name Name of the uniform as declared in the shader
 * @param value Initial value of uniform as a string
 * @return Pointer to the node
 */
Node* UniformNodeUnmarshaller::Vec4UniformNodeCreator::create(const string& name, const string& value) const {

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
