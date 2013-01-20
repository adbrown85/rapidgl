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
#include <Poco/String.h>
#include "RapidGL/CullNodeUnmarshaller.h"
namespace RapidGL {

/**
 * Constructs a `CullNodeUnmarshaller`.
 */
CullNodeUnmarshaller::CullNodeUnmarshaller() : modesByValue(createModesByValue()) {
    // empty
}

/**
 * Destructs a `CullNodeUnmarshaller`.
 */
CullNodeUnmarshaller::~CullNodeUnmarshaller() {
    // empty
}

/**
 * Creates the map of modes by their attribute values.
 *
 * @return Map of modes by their attribute values
 */
std::map<std::string,GLenum> CullNodeUnmarshaller::createModesByValue() {
    std::map<std::string,GLenum> modesByValue;
    modesByValue["back"] = GL_BACK;
    modesByValue["both"] = GL_FRONT_AND_BACK;
    modesByValue["front"] = GL_FRONT;
    modesByValue["none"] = GL_NONE;
    return modesByValue;
}

/**
 * Returns the value of the _mode_ attribute in a map.
 *
 * @param attributes Map of attributes to look in
 * @return Value of the _mode_ attribute in the given map
 * @throws std::runtime_error if value is unspecified or invalid
 */
GLenum CullNodeUnmarshaller::getMode(const std::map<std::string,std::string>& attributes) {

    // Find the value
    const std::string value = findValue(attributes, "mode");
    if (value.empty()) {
        throw std::runtime_error("[CullNodeUnmarshaller] Mode is unspecified!");
    }

    // Convert to enumeration
    const std::string valueAsLower = Poco::toLower(value);
    std::map<std::string,GLenum>::const_iterator it = modesByValue.find(valueAsLower);
    if (it == modesByValue.end()) {
        throw std::runtime_error("[CullNodeUnmarshaller] Mode is invalid!");
    } else {
        return it->second;
    }
}

Node* CullNodeUnmarshaller::unmarshal(const std::map<std::string,std::string>& attributes) {
    const GLenum mode = getMode(attributes);
    return new CullNode(mode);
}

} /* namespace RapidGL */
