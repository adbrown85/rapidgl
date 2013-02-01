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
#include "RapidGL/DepthFunctionNodeUnmarshaller.h"
using std::map;
using std::string;
namespace RapidGL {

const map<string,GLenum> DepthFunctionNodeUnmarshaller::FUNCTIONS = DepthFunctionNodeUnmarshaller::createFunctions();

/**
 * Constructs a `DepthFunctionNodeUnmarshaller`.
 */
DepthFunctionNodeUnmarshaller::DepthFunctionNodeUnmarshaller() {
    // empty
}

/**
 * Destructs a `DepthFunctionNodeUnmarshaller`.
 */
DepthFunctionNodeUnmarshaller::~DepthFunctionNodeUnmarshaller() {
    // empty
}

/**
 * Creates the map of functions indexed by name.
 *
 * @return Map of functions indexed by name
 */
map<string,GLenum> DepthFunctionNodeUnmarshaller::createFunctions() {
    map<string,GLenum> functions;
    functions["always"] = GL_ALWAYS;
    functions["equal"] = GL_EQUAL;
    functions["gequal"] = GL_GEQUAL;
    functions["greater"] = GL_GREATER;
    functions["less"] = GL_LESS;
    functions["lequal"] = GL_LEQUAL;
    functions["never"] = GL_NEVER;
    functions["notequal"] = GL_NOTEQUAL;
    return functions;
}

/**
 * Returns the value of the _function_ attribute in a map.
 *
 * @param attributes Map of attributes to look in
 * @throws std::runtime_error if function is unspecified or invalid
 */
GLenum DepthFunctionNodeUnmarshaller::getFunction(const map<string,string>& attributes) {

    // Get value
    const string value = findValue(attributes, "function");
    if (value.empty()) {
        throw std::runtime_error("[DepthFunctionNodeUnmarshaller] Function is unspecified!");
    }

    // Parse the value
    const string valueAsLower = Poco::toLower(value);
    map<string,GLenum>::const_iterator it = FUNCTIONS.find(valueAsLower);
    if (it == FUNCTIONS.end()) {
        throw std::runtime_error("[DepthFunctionNodeUnmarshaller] Function is invalid!");
    }

    // Return the enumeration
    return it->second;
}

Node* DepthFunctionNodeUnmarshaller::unmarshal(const map<string,string>& attributes) {
    const GLenum function = getFunction(attributes);
    return new DepthFunctionNode(function);
}

} /* namespace RapidGL */
