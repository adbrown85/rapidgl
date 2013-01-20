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
#include "RapidGL/TextureNode.h"
namespace RapidGL {

/**
 * Constructs a texture node.
 *
 * @param id Unique identifier of texture node, e.g. _myTexture_
 * @param target Target to bind texture to
 * @param texture Texture object containing texture data
 * @throws std::invalid_argument if name is empty
 */
TextureNode::TextureNode(const std::string& id,
                         const Gloop::TextureTarget& target,
                         const Gloop::TextureObject& texture) :
        Node(id),
        target(target),
        texture(texture),
        unit(Gloop::TextureUnit::fromEnum(GL_TEXTURE0)),
        prepared(false) {
    if (id.empty()) {
        throw std::invalid_argument("[TextureNode] Unique identifier is empty!");
    }
}

/**
 * Destructs a texture node.
 */
TextureNode::~TextureNode() {
    texture.dispose();
}

/**
 * Returns the target the texture gets bound to.
 *
 * @return Target the texture gets bound to
 */
Gloop::TextureTarget TextureNode::getTextureTarget() const {
    return target;
}

/**
 * Returns the texture object this texture node represents.
 *
 * @return Texture object this texture node represents
 */
Gloop::TextureObject TextureNode::getTextureObject() const {
    return texture;
}

/**
 * Returns the texture unit this texture gets loaded on.
 *
 * @return Texture unit this texture gets loaded on
 */
Gloop::TextureUnit TextureNode::getTextureUnit() const {
    return unit;
}

void TextureNode::preVisit(State& state) {

    // Skip if already prepared
    if (prepared) {
        return;
    }

    // Find unit
    const TextureNode* textureNode = findAncestor<TextureNode>(this);
    if (textureNode != NULL) {
        const GLint ordinal = textureNode->getTextureUnit().toOrdinal();
        unit = Gloop::TextureUnit::fromOrdinal(ordinal + 1);
    }

    // Successfully prepared
    prepared = true;
}

void TextureNode::visit(State& state) {
    unit.activate();
    target.bind(texture);
}

} /* namespace RapidGL */
