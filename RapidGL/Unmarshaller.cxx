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
#include <sstream>
#include <stdexcept>
#include "RapidGL/Unmarshaller.hxx"
namespace RapidGL {

/**
 * Constructs an unmarshaller.
 */
Unmarshaller::Unmarshaller() {
    // empty
}

/**
 * Destructs an umarshaller.
 */
Unmarshaller::~Unmarshaller() {
    // empty
}

/**
 * Unmarshals a node from XML attributes.
 *
 * @param attributes Map of attribute keys and values
 * @return New node instance for attributes, or `NULL` if could not be unmarshalled
 */
Node* Unmarshaller::unmarshal(const std::map<std::string,std::string>& attributes) {
    return NULL;
}

/**
 * Returns the value of a key in a map.
 *
 * @param map Map of keys to values
 * @param key Key to get value for
 * @return Value of the key in the map, or the empty string if could not be found
 */
std::string Unmarshaller::findValue(const std::map<std::string,std::string>& map, const std::string& key) {
    const std::map<std::string,std::string>::const_iterator it = map.find(key);
    return (it == map.end()) ? "" : it->second;
}

/**
 * Parses a float from a string.
 *
 * @param str String to parse
 * @return Float parsed from string
 * @throws invalid_argument if string cannot be parsed as a valid float
 */
GLfloat Unmarshaller::parseFloat(const std::string& str) {
    std::stringstream stream(str);
    stream.unsetf(std::ios_base::skipws);
    GLfloat value;
    stream >> value;
    if (stream.fail() || !stream.eof()) {
        throw std::invalid_argument("[Unmarshaller] String is not a valid float!");
    } else {
        return value;
    }
}

/**
 * Parses an integer from a string.
 *
 * @param str String to parse
 * @return Integer parsed from string
 * @throws invalid_argument if string cannot be parsed as a valid integer
 */
GLint Unmarshaller::parseInt(const std::string& str) {
    std::stringstream stream(str);
    stream.unsetf(std::ios_base::skipws);
    GLint value;
    stream >> value;
    if (stream.fail() || !stream.eof()) {
        throw std::invalid_argument("[Unmarshaller] String is not a valid integer!");
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
std::vector<std::string> Unmarshaller::tokenize(const std::string& str) {
    std::vector<std::string> tokens;
    std::stringstream stream(str);
    std::string token;
    stream >> token;
    while (stream) {
        tokens.push_back(token);
        stream >> token;
    }
    return tokens;
}

} /* namespace RapidGL */
