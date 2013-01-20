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
#include "RapidGL/FramebufferNode.h"
namespace RapidGL {
using std::map;

/**
 * Constructs a `FramebufferNode`.
 */
FramebufferNode::FramebufferNode() :
        ready(false),
        fbo(Gloop::FramebufferObject::generate()),
        drawFramebuffer(Gloop::FramebufferTarget::drawFramebuffer()) {
    // empty
}

/**
 * Destructs a `FramebufferNode`.
 */
FramebufferNode::~FramebufferNode() {
    // empty
}

/**
 * Constructs a default attacher.
 */
FramebufferNode::Attacher::Attacher() : base(0), capacity(0) {
    // empty
}

/**
 * Constructs an attacher from a base and a capacity.
 *
 * @param base First attachment for type, e.g. `GL_COLOR_ATTACHMENT0`
 * @param capacity Number of possible attachments for the type, e.g. value of `getMaxColorAttachments()`
 */
FramebufferNode::Attacher::Attacher(GLenum base, size_t capacity) : base(base), capacity(capacity) {
    // empty
}

/**
 * Adds an attachment node to this attacher.
 *
 * @param node Attachment node to attach
 * @throws std::runtime_error if there is too many attachments for this type
 */
void FramebufferNode::Attacher::add(AttachmentNode* node) {
    if ((nodes.size() + 1) > capacity) {
        throw std::runtime_error("[FramebufferNode] Too many attachments of type!");
    }
    nodes.push_back(node);
}

/**
 * Attaches all the attachments given to this attacher.
 */
void FramebufferNode::Attacher::run() {
    GLenum attachment = base;
    for (std::vector<AttachmentNode*>::const_iterator it = nodes.begin(); it != nodes.end(); ++it) {
        (*it)->attach(attachment++);
    }
}

/**
 * Returns the OpenGL framebuffer object represented by this node.
 *
 * @return OpenGL framebuffer object represented by this node
 */
Gloop::FramebufferObject FramebufferNode::getFramebufferObject() const {
    return fbo;
}

/**
 * Returns the maximum number of color attachments an FBO can have.
 *
 * @return Maximum number of color attachments an FBO can have
 */
GLint FramebufferNode::getMaxColorAttachments() {
    return Gloop::FramebufferTarget::getMaxColorAttachments();
}

/**
 * Unbinds the OpenGL framebuffer object represented by this node.
 */
void FramebufferNode::postVisit(State& state) {
    drawFramebuffer.unbind();
}

/**
 * Sets up the framebuffer object if it hasn't been already.
 */
void FramebufferNode::preVisit(State& state) {

    // Skip if already ready
    if (ready) {
        return;
    }

    // Initialize attachers
    map<AttachmentNode::Usage,Attacher> attachers;
    attachers[AttachmentNode::COLOR] = Attacher(GL_COLOR_ATTACHMENT0, getMaxColorAttachments());
    attachers[AttachmentNode::DEPTH] = Attacher(GL_DEPTH_ATTACHMENT, 1);
    attachers[AttachmentNode::STENCIL] = Attacher(GL_STENCIL_ATTACHMENT, 1);

    // Sort attachments into attachers
    node_range_t children = getChildren();
    for (node_iterator_t it = children.begin; it != children.end; ++it) {
        AttachmentNode* attachmentNode = dynamic_cast<AttachmentNode*>(*it);
        if (attachmentNode != NULL) {
            const AttachmentNode::Usage usage = attachmentNode->getUsage();
            if (attachers.count(usage) > 0) {
                attachers[usage].add(attachmentNode);
            }
        }
    }

    // Bind the FBO
    drawFramebuffer.bind(fbo);

    // Run each of the attachers
    for (map<AttachmentNode::Usage,Attacher>::iterator it = attachers.begin(); it != attachers.end(); ++it) {
        it->second.run();
    }

    // Check if complete
    const GLenum status = drawFramebuffer.checkStatus();
    if (status != GL_FRAMEBUFFER_COMPLETE) {
        throw std::runtime_error(Gloop::FramebufferTarget::formatStatus(status));
    }

    // Now ready
    ready = true;
}

/**
 * Binds the OpenGL framebuffer object represented by this node.
 */
void FramebufferNode::visit(State& state) {
    drawFramebuffer.bind(fbo);
}

} /* namespace RapidGL */
