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
#ifndef RAPIDGL_RENDERBUFFER_ATTACHMENT_NODE_H
#define RAPIDGL_RENDERBUFFER_ATTACHMENT_NODE_H
#include <gloop/RenderbufferObject.hxx>
#include "RapidGL/common.h"
#include "RapidGL/AttachmentNode.h"
#include "RapidGL/FramebufferNode.h"
#include "RapidGL/RenderbufferNode.h"
#include "RapidGL/State.h"
namespace RapidGL {


/**
 * Node attaching a renderbuffer to a framebuffer.
 */
class RenderbufferAttachmentNode : public AttachmentNode {
public:
// Methods
    RenderbufferAttachmentNode(Usage usage, const std::string& link);
    virtual ~RenderbufferAttachmentNode();
    virtual void attach(GLenum attachment);
    std::string getLink() const;
    virtual void preVisit(State& state);
private:
// Attributes
    bool ready;
    const std::string link;
};

} /* namespace RapidGL */
#endif
