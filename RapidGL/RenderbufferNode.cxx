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
#include <gloop/RenderbufferTarget.hxx>
#include "RapidGL/RenderbufferNode.h"
namespace RapidGL {

// Set of supported formats
const std::set<GLenum> RenderbufferNode::FORMATS = RenderbufferNode::createFormats();

/**
 * Constructs a `RenderbufferNode`.
 *
 * @param id Identifier of node
 * @param format Internal format of renderbuffer
 * @param width Width of renderbuffer
 * @param height Height of renderbuffer
 * @throws std::invalid_argument
 *         if identifier is empty,
 *         if format is unsupported, or
 *         if width or height is out of range
 */
RenderbufferNode::RenderbufferNode(const std::string& id,
                                   const GLenum format,
                                   const GLsizei width,
                                   const GLsizei height) :
        Node(id),
        rbo(Gloop::RenderbufferObject::generate()) {

    // Check id
    if (id.empty()) {
        throw std::invalid_argument("[RenderbufferNode] Identifier is empty!");
    }

    // Check format
    if (!isFormat(format)) {
        throw std::invalid_argument("[RenderbufferNode] Format is invalid!");
    }

    // Check width
    if ((width < 1) || (width > getMaxRenderbufferSize())) {
        throw std::invalid_argument("[RenderbufferNode] Width is out of range!");
    }

    // Check height
    if ((height < 1) || (height > getMaxRenderbufferSize())) {
        throw std::invalid_argument("[RenderbufferNode] Height is out of range!");
    }

    // Create storage for renderbuffer
    const Gloop::RenderbufferTarget renderbuffer;
    renderbuffer.bind(rbo);
    renderbuffer.storage(format, width, height);
    renderbuffer.unbind();
}

/**
 * Destructs a `RenderbufferNode`.
 */
RenderbufferNode::~RenderbufferNode() {
    rbo.dispose();
}

/**
 * Creates the set of valid formats.
 *
 * @return Set of valid formats
 */
std::set<GLenum> RenderbufferNode::createFormats() {
    std::set<GLenum> formats;
    formats.insert(GL_RED);
    formats.insert(GL_RG);
    formats.insert(GL_RGB);
    formats.insert(GL_RGBA);
    formats.insert(GL_DEPTH_COMPONENT);
    return formats;
}

/**
 * Returns the maximum renderbuffer size.
 *
 * @return Maximum renderbuffer size
 */
GLsizei RenderbufferNode::getMaxRenderbufferSize() {
    GLint value;
    glGetIntegerv(GL_MAX_RENDERBUFFER_SIZE, &value);
    return (GLsizei) value;
}

/**
 * Returns a handle for this node's renderbuffer object.
 *
 * @return Handle for this node's renderbuffer object
 */
Gloop::RenderbufferObject RenderbufferNode::getRenderbufferObject() const {
    return rbo;
}

/**
 * Checks if an OpenGL enumeration is a supported format.
 *
 * @param enumeration Enumeration to check
 * @return `true` if enumeration is a supported format
 */
bool RenderbufferNode::isFormat(const GLenum enumeration) {
    return FORMATS.count(enumeration) > 0;
}

void RenderbufferNode::visit(State& state) {
    // empty
}

} /* namespace RapidGL */
