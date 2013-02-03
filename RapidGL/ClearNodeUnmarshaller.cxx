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
#include "RapidGL/ClearNodeUnmarshaller.h"
using namespace std;
namespace RapidGL {

/**
 * Constructs a ClearNodeUnmarshaller.
 */
ClearNodeUnmarshaller::ClearNodeUnmarshaller() {
    // empty
}

/**
 * Destructs this ClearNodeUnmarshaller.
 */
ClearNodeUnmarshaller::~ClearNodeUnmarshaller() {
    // empty
}

/**
 * Returns the value of the _color_ attribute in a map.
 *
 * @param attributes Map of attributes to look in
 * @return Value of the attribute
 * @throws std::runtime_error if value is unspecifed or invalid
 */
Glycerin::Color ClearNodeUnmarshaller::getColor(const map<string,string>& attributes) {

    // Get value
    const string value = findValue(attributes, "color");
    if (value.empty()) {
        throw std::runtime_error("[ClearNodeUnmarshaller] Color is unspecifed!");
    }

    // Tokenize the value
    const vector<string> tokens = tokenize(value);
    if (tokens.size() != 4) {
        throw std::runtime_error("[ClearNodeUnmarshaller] Color must have four components!");
    }

    // Parse the tokens
    vector<GLfloat> components;
    try {
        for (vector<string>::const_iterator it = tokens.begin(); it != tokens.end(); ++it) {
            components.push_back(parseFloat(*it));
        }
    } catch (std::invalid_argument& e) {
        throw std::runtime_error("[ClearNodeUnmarshaller] Color component is invalid!");
    }

    // Return the color
    return Glycerin::Color(components[0], components[1], components[2], components[3]);
}

/**
 * Creates a node from a map of XML attributes.
 *
 * @param attributes Map of XML attributes
 * @return Resulting ClearNode instance
 */
Node* ClearNodeUnmarshaller::unmarshal(const std::map<std::string,std::string>& attributes) {
    const Glycerin::Color color = getColor(attributes);
    return new ClearNode(color);
}

} /* namespace RapidGL */
