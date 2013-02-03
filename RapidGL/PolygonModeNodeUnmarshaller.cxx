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
#include <stdexcept>
#include <Poco/String.h>
#include "RapidGL/PolygonModeNodeUnmarshaller.h"
using std::map;
using std::string;
namespace RapidGL {

// Map of modes indexed by name
const map<string,GLenum> PolygonModeNodeUnmarshaller::MODES = PolygonModeNodeUnmarshaller::createModes();

/**
 * Constructs a `PolygonModeNodeUnmarshaller`.
 */
PolygonModeNodeUnmarshaller::PolygonModeNodeUnmarshaller() {
    // empty
}

/**
 * Destructs a `PolygonModeNodeUnmarshaller`.
 */
PolygonModeNodeUnmarshaller::~PolygonModeNodeUnmarshaller() {
    // empty
}

/**
 * Creates the map of modes indexed by name.
 *
 * @return Map of modes indexed by name
 */
map<string,GLenum> PolygonModeNodeUnmarshaller::createModes() {
    map<string,GLenum> modes;
    modes["fill"] = GL_FILL;
    modes["line"] = GL_LINE;
    modes["point"] = GL_POINT;
    return modes;
}

/**
 * Returns the value of the _mode_ attribute in a map.
 *
 * @param attributes Map of attributes to look in
 * @return Value of attribute
 * @throws std::runtime_error if mode is unspecified or invalid
 */
GLenum PolygonModeNodeUnmarshaller::getMode(const map<string,string>& attributes) {

    // Get the value
    const string value = findValue(attributes, "mode");
    if (value.empty()) {
        throw std::runtime_error("[PolygonModeNodeUnmarshaller] Mode is unspecified!");
    }

    // Parse the value
    const string valueAsLower = Poco::toLower(value);
    map<string,GLenum>::const_iterator it = MODES.find(valueAsLower);
    if (it == MODES.end()) {
        throw std::runtime_error("[PolygonModeNodeUnmarshaller] Mode is invalid!");
    } else {
        return it->second;
    }
}

Node* PolygonModeNodeUnmarshaller::unmarshal(const std::map<std::string,std::string>& attributes) {
    const GLenum mode = getMode(attributes);
    return new PolygonModeNode(mode);
}

} /* namespace RapidGL */
