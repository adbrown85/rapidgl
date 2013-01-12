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
#ifndef RAPIDGL_TEXTURE_ATTACHMENT_NODE_HXX
#define RAPIDGL_TEXTURE_ATTACHMENT_NODE_HXX
#include <string>
#include "RapidGL/common.h"
#include "RapidGL/AttachmentNode.hxx"
#include "RapidGL/FramebufferNode.hxx"
#include "RapidGL/Node.hxx"
#include "RapidGL/State.hxx"
#include "RapidGL/TextureNode.hxx"
namespace RapidGL {


/**
 * Node that attaches a texture to a framebuffer.
 */
class TextureAttachmentNode : public AttachmentNode {
public:
// Methods
    TextureAttachmentNode(Usage usage, const std::string& link);
    ~TextureAttachmentNode();
    std::string getLink() const;
    virtual void attach(GLenum attachment);
    virtual void preVisit(State& state);
private:
// Attributes
    bool ready;
    const std::string link;
};

} /* namespace RapidGL */
#endif
