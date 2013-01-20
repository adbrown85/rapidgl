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
#include "RapidGL/Sampler2dUniformNode.h"
namespace RapidGL {

/**
 * Constructs a `Sampler2dUniformNode`.
 *
 * @param name Name of uniform as declared in shader
 * @param link Name of texture node to set uniform value to
 * @throws std::invalid_argument if name or link is empty
 */
Sampler2dUniformNode::Sampler2dUniformNode(const std::string& name, const std::string& link) :
        UniformNode(name, GL_SAMPLER_2D),
        link(link),
        unit(Gloop::TextureUnit::fromEnum(GL_TEXTURE0)),
        prepared(false) {
    if (link.empty()) {
        throw std::invalid_argument("[Sampler2dUniformNode] Link is empty!");
    }
}

/**
 * Destructs a `Sampler2dUniformNode`.
 */
Sampler2dUniformNode::~Sampler2dUniformNode() {
    // empty
}

/**
 * Returns the name of the texture node this node is linked to.
 *
 * @return Name of the texture node this node is linked to
 */
std::string Sampler2dUniformNode::getLink() const {
    return link;
}

/**
 * Returns the texture unit this node sets the uniform value to.
 *
 * @return Texture unit this node sets the uniform value to
 */
Gloop::TextureUnit Sampler2dUniformNode::getTextureUnit() const {
    return unit;
}

void Sampler2dUniformNode::preVisit(State& state) {

    UniformNode::preVisit(state);

    // Skip if already prepared
    if (prepared) {
        return;
    }

    // Find texture
    const TextureNode* textureNode = findAncestor<TextureNode>(this, link);
    if (textureNode == NULL) {
        throw std::runtime_error("[Sampler2dUniformNode] Could not find texture!");
    }

    // Check its texture type
    if (textureNode->getTextureTarget() != Gloop::TextureTarget::texture2d()) {
        throw std::runtime_error("[Sampler2dUniformNode] Texture is of wrong type!");
    }

    // Store its texture unit
    unit = textureNode->getTextureUnit();

    // Successfully prepared
    prepared = true;
}

void Sampler2dUniformNode::visit(State& state) {
    glUniform1i(getLocation(), unit.toOrdinal());
}

} /* namespace RapidGL */
