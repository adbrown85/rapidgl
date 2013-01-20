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
#include <gloop/FramebufferObject.hxx>
#include <gloop/FramebufferTarget.hxx>
#include <gloop/TextureObject.hxx>
#include "RapidGL/TextureAttachmentNode.h"
namespace RapidGL {

/**
 * Constructs a `TextureAttachmentNode`.
 *
 * @param usage How the attachment should be used, e.g. `COLOR` or `DEPTH`
 * @param link Identifier of the texture node to attach
 * @throws std::invalid_argument if link is empty
 */
TextureAttachmentNode::TextureAttachmentNode(const Usage usage, const std::string& link) :
        AttachmentNode(usage), ready(false), link(link) {
    if (link.empty()) {
        throw std::invalid_argument("[TextureAttachmentNode] Link is empty!");
    }
}

/**
 * Destructs a `TextureAttachmentNode`.
 */
TextureAttachmentNode::~TextureAttachmentNode() {
    // empty
}

/**
 * Attaches the texture linked to by this node to the currently bound framebuffer.
 *
 * @param attachment Framebuffer attachment point to attach to
 * @throws std::runtime_error if could not make the attachment
 */
void TextureAttachmentNode::attach(const GLenum attachment) {

    // Get parent
    Node* parent = getParent();
    if (parent == NULL) {
        throw std::runtime_error("[TextureAttachmentNode] Must have a parent to attach to!");
    }

    // Cast to a framebuffer node
    const FramebufferNode* framebufferNode = dynamic_cast<FramebufferNode*>(parent);
    if (framebufferNode == NULL) {
        throw std::runtime_error("[TextureAttachmentNode] Can only attach to a framebuffer node!");
    }

    // Find texture node
    const TextureNode* textureNode = findAncestor<TextureNode>(this, link);
    if (textureNode == NULL) {
        throw std::runtime_error("[TextureAttachmentNode] Could not find texture to attach!");
    }

    // Get texture
    const Gloop::TextureTarget textureTarget = Gloop::TextureTarget::texture2d();
    const Gloop::TextureObject texture = textureNode->getTextureObject();

    // Attach texture to framebuffer
    const Gloop::FramebufferTarget drawFramebuffer = Gloop::FramebufferTarget::drawFramebuffer();
    if (textureTarget == Gloop::TextureTarget::texture2d()) {
        drawFramebuffer.texture2d(attachment, textureTarget, texture, 0);
    }
}

/**
 * Returns the identifier of the texture this node should attach.
 *
 * @return Identifier of the texture this node should attach
 */
std::string TextureAttachmentNode::getLink() const {
    return link;
}

/**
 * Ensures this node's parent is a @ref FramebufferNode.
 */
void TextureAttachmentNode::preVisit(State& state) {

    // Skip if already ready
    if (ready) {
        return;
    }

    // Check parent
    const Node* parent = getParent();
    if ((parent == NULL) || (dynamic_cast<const FramebufferNode*>(parent) == NULL)) {
        throw std::runtime_error("[TextureAttachmentNode] Parent must be a framebuffer node!");
    }

    // Now ready
    ready = true;
}

void TextureAttachmentNode::visit(State& state) {
    // empty
}

} /* namespace RapidGL */
