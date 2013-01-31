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
#include <gloop/FramebufferTarget.hxx>
#include <gloop/RenderbufferTarget.hxx>
#include "RapidGL/RenderbufferAttachmentNode.h"
namespace RapidGL {

/**
 * Constructs a `RenderbufferAttachmentNode`.
 *
 * @param usage How the renderbuffer should be used, e.g. `COLOR` or `DEPTH`
 * @param link Identifier of the renderbuffer node to attach
 * @throws std::invalid_argument if link is empty
 */
RenderbufferAttachmentNode::RenderbufferAttachmentNode(const Usage usage, const std::string& link) :
        AttachmentNode(usage),
        ready(false),
        link(link) {

    // Check link
    if (link.empty()) {
        throw std::invalid_argument("[RenderbufferAttachmentNode] Link is empty!");
    }
}

/**
 * Destructs a `RenderbufferAttachmentNode`.
 */
RenderbufferAttachmentNode::~RenderbufferAttachmentNode() {
    // empty
}

void RenderbufferAttachmentNode::attach(const GLenum attachment) {

    // Find root
    const Node* root = findRoot(this);
    if (root == this) {
        throw std::runtime_error("[RenderbufferAttachmentNode] Renderbuffer attachment should not be root!");
    }

    // Find node
    const Node* node = findDescendant(root, link);
    if (node == NULL) {
        throw std::runtime_error("[RenderbufferAttachmentNode] Could not find node with requested ID!");
    }

    // Cast it to a renderbuffer node
    const RenderbufferNode* renderbufferNode = dynamic_cast<const RenderbufferNode*>(node);
    if (renderbufferNode == NULL) {
        throw std::runtime_error("[RenderbufferAttachmentNode] Node is not a renderbuffer node!");
    }

    // Attach its RBO
    const Gloop::RenderbufferObject rbo = renderbufferNode->getRenderbufferObject();
    const Gloop::FramebufferTarget drawFramebuffer = Gloop::FramebufferTarget::drawFramebuffer();
    drawFramebuffer.renderbuffer(attachment, rbo);
}

/**
 * Returns the identifier of the renderbuffer node this node is linked to.
 *
 * @return Identifier of the renderbuffer node this node is linked to
 */
std::string RenderbufferAttachmentNode::getLink() const {
    return link;
}

void RenderbufferAttachmentNode::preVisit(State& state) {

    // Skip if already ready
    if (ready) {
        return;
    }

    // Make sure this node's parent is a framebuffer node
    const Node* parent = getParent();
    if (dynamic_cast<const FramebufferNode*>(parent) == NULL) {
        throw std::runtime_error("[RenderbufferAttachmentNode] Parent must be a framebuffer node!");
    }

    // Now ready
    ready = true;
}

} /* namespace RapidGL */
