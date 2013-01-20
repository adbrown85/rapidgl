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
#include <iostream>
#include <exception>
#include <stdexcept>
#include <cppunit/extensions/HelperMacros.h>
#include <GL/glfw.h>
#include <gloop/FramebufferTarget.hxx>
#include "RapidGL/AttachmentNode.h"
#include "RapidGL/ClearNode.h"
#include "RapidGL/FramebufferNode.h"
#include "RapidGL/Node.h"
#include "RapidGL/State.h"


/**
 * Unit test for `FramebufferNode`.
 */
class FramebufferNodeTest {
public:

    /**
     * Node that attaches a renderbuffer to the first color attachment.
     */
    class ColorAttachmentNode : public RapidGL::AttachmentNode {
    public:

        // Renderbuffer to attach
        GLuint renderbuffer;

        /**
         * Constructs a `ColorAttachmentNode`.
         */
        ColorAttachmentNode() : RapidGL::AttachmentNode(RapidGL::AttachmentNode::COLOR) {
            glGenRenderbuffers(1, &renderbuffer);
            glBindRenderbuffer(GL_RENDERBUFFER, renderbuffer);
            glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA, 8, 8);
        }

        /**
         * Attaches the renderbuffer to its parent.
         */
        void attach(GLenum attachment) {
            const Node* parent = getParent();
            const RapidGL::FramebufferNode* framebufferNode = dynamic_cast<const RapidGL::FramebufferNode*>(parent);
            if (framebufferNode == NULL) {
                throw std::runtime_error("[ColorAttachmentNode] Parent is not a framebuffer node!");
            } else {
                glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER, attachment, GL_RENDERBUFFER, renderbuffer);
            }
        }
    };

    // Handle to `GL_DRAWFRAMEBUFFER`
    const Gloop::FramebufferTarget drawFramebuffer;

    // Reusable state to pass since `FramebufferNode` doesn't use it
    RapidGL::State state;

    /**
     * Constructs the test.
     */
    FramebufferNodeTest() : drawFramebuffer(Gloop::FramebufferTarget::drawFramebuffer()) {
        // empty
    }

    /**
     * Ensures `FramebufferNode::preVisit` throws if it has no attachments.
     */
    void testPreVisitWithNoAttachment() {
        RapidGL::ClearNode clearNode;
        RapidGL::FramebufferNode framebufferNode;
        framebufferNode.addChild(&clearNode);
        CPPUNIT_ASSERT_THROW(framebufferNode.preVisit(state), std::runtime_error);
        drawFramebuffer.unbind();
    }

    /**
     * Ensures `FramebufferNode::postVisit` unbinds the framebuffer.
     */
    void testPostVisit() {
        RapidGL::FramebufferNode framebufferNode;
        framebufferNode.visit(state);
        framebufferNode.postVisit(state);
        CPPUNIT_ASSERT(!drawFramebuffer.bound());
        drawFramebuffer.unbind();
    }

    /**
     * Ensures `FramebufferNode::preVisit` does not throw if it has a valid color attachment.
     */
    void testPreVisitWithColorAttachment() {
        ColorAttachmentNode attachmentNode;
        RapidGL::FramebufferNode framebufferNode;
        framebufferNode.addChild(&attachmentNode);
        CPPUNIT_ASSERT_NO_THROW(framebufferNode.preVisit(state));
        drawFramebuffer.unbind();
    }

    /**
     * Ensures `FramebufferNode::visit` binds the framebuffer.
     */
    void testVisit() {
        RapidGL::FramebufferNode framebufferNode;
        framebufferNode.visit(state);
        CPPUNIT_ASSERT(drawFramebuffer.bound(framebufferNode.getFramebufferObject()));
        drawFramebuffer.unbind();
    }
};

int main(int argc, char* argv[]) {

    // Initialize GLFW
    if (!glfwInit()) {
        throw std::runtime_error("Could not initialize GLFW!");
    }

    // Open window
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 2);
    glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    if (!glfwOpenWindow(512, 512, 0, 0, 0, 0, 0, 0, GLFW_WINDOW)) {
        throw std::runtime_error("Could not open GLFW window!");
    }

    // Run the test
    FramebufferNodeTest test;
    try {
        test.testPreVisitWithNoAttachment();
        test.testPreVisitWithColorAttachment();
        test.testPostVisit();
        test.testVisit();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        throw;
    }

    // Exit
    glfwTerminate();
    return 0;
}
