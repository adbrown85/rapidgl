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
#include "RapidGL/RenderbufferNodeUnmarshaller.h"
namespace RapidGL {

// Map of formats indexed by name
const std::map<std::string,GLenum> RenderbufferNodeUnmarshaller::FORMATS = createFormats();

/**
 * Constructs a `RenderbufferNodeUnmarshaller`.
 */
RenderbufferNodeUnmarshaller::RenderbufferNodeUnmarshaller() {
    // empty
}

/**
 * Destructs a `RenderbufferNodeUnmarshaller`.
 */
RenderbufferNodeUnmarshaller::~RenderbufferNodeUnmarshaller() {
    // empty
}

/**
 * Creates the map of formats indexed by name.
 *
 * @return Map of formats indexed by name
 */
std::map<std::string,GLenum> RenderbufferNodeUnmarshaller::createFormats() {
    std::map<std::string,GLenum> formats;
    formats["red"] = GL_RED;
    formats["rg"] = GL_RG;
    formats["rgb"] = GL_RGB;
    formats["rgba"] = GL_RGBA;
    formats["depth"] = GL_DEPTH_COMPONENT;
    return formats;
}

/**
 * Returns the value of the _format_ attribute in a map.
 *
 * @param attributes Map of attributes to look in
 * @return Value of the attribute
 * @throws std::runtime_error if format is unspecified
 */
GLenum RenderbufferNodeUnmarshaller::getFormat(const std::map<std::string,std::string>& attributes) {

    // Get value
    const std::string value = findValue(attributes, "format");
    if (value.empty()) {
        throw std::runtime_error("[RenderbufferNodeUnmarshaller] Format is unspecified!");
    }

    // Parse value
    const std::string valueAsLower = Poco::toLower(value);
    std::map<std::string,GLenum>::const_iterator it = FORMATS.find(value);
    if (it == FORMATS.end()) {
        throw std::runtime_error("[RenderbufferNodeUnmarshaller] Format is invalid!");
    }

    // Return value
    return it->second;
}

/**
 * Returns the value of the _height_ attribute in a map.
 *
 * @param attributes Map of attributes to look in
 * @return Value of the attribute
 * @throws std::runtime_error if format is unspecified, invalid, or out of range
 */
GLsizei RenderbufferNodeUnmarshaller::getHeight(const std::map<std::string,std::string>& attributes) {

    // Get value
    const std::string value = findValue(attributes, "height");
    if (value.empty()) {
        throw std::runtime_error("[RenderbufferNodeUnmarshaller] Height is unspecified!");
    }

    // Parse value
    GLsizei height;
    try {
        height = parseInt(value);
    } catch (std::invalid_argument& e) {
        throw std::runtime_error("[RenderbufferNodeUnmarshaller] Height is not a valid integer!");
    }

    // Check value
    if ((height <= 0) || (height > getMaxRenderbufferSize())) {
        throw std::runtime_error("[RenderbufferNodeUnmarshaller] Height is out of range!");
    }

    // Return value
    return height;
}

/**
 * Returns the value of the _height_ attribute in a map.
 *
 * @param attributes Map of attributes to look in
 * @return Value of the attribute
 * @throws std::runtime_error if format is unspecified, invalid, or out of range
 */
std::string RenderbufferNodeUnmarshaller::getId(const std::map<std::string,std::string>& attributes) {
    const std::string value = findValue(attributes, "id");
    if (value.empty()) {
        throw std::runtime_error("[RenderbufferNodeUnmarshaller] Id is unspecified!");
    }
    return value;
}

/**
 * Returns the maximum size of a renderbuffer.
 *
 * @return Maximum size of a renderbuffer
 */
GLsizei RenderbufferNodeUnmarshaller::getMaxRenderbufferSize() {
    GLint value;
    glGetIntegerv(GL_MAX_RENDERBUFFER_SIZE, &value);
    return value;
}

/**
 * Returns the value of the _width_ attribute in a map.
 *
 * @param attributes Map of attributes to look in
 * @return Value of the attribute
 * @throws std::runtime_error if format is unspecified, invalid, or out of range
 */
GLsizei RenderbufferNodeUnmarshaller::getWidth(const std::map<std::string,std::string>& attributes) {

    // Get value
    const std::string value = findValue(attributes, "width");
    if (value.empty()) {
        throw std::runtime_error("[RenderbufferNodeUnmarshaller] Width is unspecified!");
    }

    // Parse value
    GLsizei width;
    try {
        width = parseInt(value);
    } catch (std::invalid_argument& e) {
        throw std::runtime_error("[RenderbufferNodeUnmarshaller] Width is not a valid integer!");
    }

    // Check value
    if ((width <= 0) || (width > getMaxRenderbufferSize())) {
        throw std::runtime_error("[RenderbufferNodeUnmarshaller] Width is out of range!");
    }

    // Return value
    return width;
}

Node* RenderbufferNodeUnmarshaller::unmarshal(const std::map<std::string,std::string>& attributes) {
    const std::string id = getId(attributes);
    const GLenum format = getFormat(attributes);
    const GLsizei width = getWidth(attributes);
    const GLsizei height = getHeight(attributes);
    return new RenderbufferNode(id, format, width, height);
}

} /* namespace RapidGL */
