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
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "RapidGL/ShaderNodeUnmarshaller.h"
namespace RapidGL {

/**
 * Constructs a ShaderNodeUnmarshaller.
 */
ShaderNodeUnmarshaller::ShaderNodeUnmarshaller() {
    // empty
}

/**
 * Copies a file to a string.
 *
 * @param path Path of file to copy
 * @return Contents of file as a string
 * @throws runtime_error if file could not be opened
 */
std::string ShaderNodeUnmarshaller::copyFile(const std::string& path) {

    // Open file
    std::ifstream file(path.c_str());
    if (!file) {
        throw std::runtime_error("[ShaderNodeUnmarshaller] Could not open file!");
    }

    // Copy file to a string
    std::stringstream copy;
    char buf[BUFFER_SIZE];
    while (file) {
        file.read(buf, BUFFER_SIZE);
        copy.write(buf, file.gcount());
    }

    // Return string
    return copy.str();
}

/**
 * Returns the value of the _file_ attribute in a map.
 *
 * @param attributes Map of attributes to look in
 * @return Value of _file_ attribute in the map
 * @throws runtime_error if _file_ attribute is unspecified
 */
std::string ShaderNodeUnmarshaller::getFile(const std::map<std::string,std::string>& attributes) {
    const std::string value = findValue(attributes, "file");
    if (value.empty()) {
        throw std::runtime_error("[ShaderNodeUnmarshaller] File is unspecified!");
    } else {
        return value;
    }
}

/**
 * Returns the value of the _type_ attribute in a map.
 *
 * @param attributes Map of attributes to look in
 * @return Value of _type_ attribute in the map
 * @throws runtime_error if _type_ attribute is unspecified
 */
GLenum ShaderNodeUnmarshaller::getType(const std::map<std::string,std::string>& attributes) {

    // Get the value
    const std::string value = findValue(attributes, "type");
    if (value.empty()) {
        throw std::runtime_error("[ShaderNodeUnmarshaller] Type is unspecified!");
    }

    // Convert to an enumeration
    if (value == "fragment") {
        return GL_FRAGMENT_SHADER;
    } else if (value == "geometry") {
        return GL_GEOMETRY_SHADER;
    } else if (value == "vertex") {
        return GL_VERTEX_SHADER;
    } else {
        throw std::runtime_error("[ShaderNodeUnmarshaller] Type is invalid!");
    }
}

Node* ShaderNodeUnmarshaller::unmarshal(const std::map<std::string,std::string>& attributes) {

    // Get type and file
    const GLenum type = getType(attributes);
    const std::string file = getFile(attributes);

    // Get source code from file
    const std::string source = copyFile(file);

    // Return the node
    return new RapidGL::ShaderNode(type, source);
}

} /* namespace RapidGL */
