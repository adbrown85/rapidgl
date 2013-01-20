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
#ifndef RAPIDGL_FRAMEBUFFER_NODE_H
#define RAPIDGL_FRAMEBUFFER_NODE_H
#include <map>
#include <vector>
#include <gloop/FramebufferObject.hxx>
#include <gloop/FramebufferTarget.hxx>
#include "RapidGL/common.h"
#include "RapidGL/AttachmentNode.h"
#include "RapidGL/Node.h"
#include "RapidGL/State.h"
namespace RapidGL {


/**
 * Node representing a framebuffer object.
 */
class FramebufferNode : public Node {
public:
// Methods
    FramebufferNode();
    virtual ~FramebufferNode();
    Gloop::FramebufferObject getFramebufferObject() const;
    virtual void postVisit(State& state);
    virtual void preVisit(State& state);
    virtual void visit(State& state);
private:
// Types
    class Attacher {
    public:
    // Methods
        Attacher();
        Attacher(GLenum base, size_t capacity);
        void add(AttachmentNode* node);
        void run();
    private:
    // Attributes
        GLenum base;
        int capacity;
        std::vector<AttachmentNode*> nodes;
    };
// Attributes
    bool ready;
    Gloop::FramebufferObject fbo;
    Gloop::FramebufferTarget drawFramebuffer;
// Methods
    static GLint getMaxColorAttachments();
};

} /* namespace RapidGL */
#endif
