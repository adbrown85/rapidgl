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
#include <exception>
#include <iostream>
#include <stdexcept>
#include <cppunit/extensions/HelperMacros.h>
#include <GL/glfw.h>
#include "RapidGL/AttachmentNode.h"
#include "RapidGL/FramebufferNode.h"
#include "RapidGL/RenderbufferAttachmentNode.h"
#include "RapidGL/RenderbufferNode.h"
#include "RapidGL/SceneNode.h"
#include "RapidGL/State.h"
#include "RapidGL/Visitor.h"


/**
 * Unit test for `RenderbufferAttachmentNodeTest`.
 */
class RenderbufferAttachmentNodeTest {
public:

    /**
     * Fake node used for testing.
     */
    class FakeNode : public RapidGL::Node {
    public:
        FakeNode(const std::string& id) : RapidGL::Node(id) { }
        virtual void visit(RapidGL::State& state) { }
    };

    // Reusable state since `RenderbufferAttachmentNode` doesn't use it
    RapidGL::State state;

    /**
     * Ensures `RenderbufferAttachmentNode::attach` throws if the link is missing.
     */
    void testAttachWhenLinkIsMissing() {

        // Create nodes
        RapidGL::SceneNode sceneNode;
        RapidGL::FramebufferNode framebufferNode;
        RapidGL::RenderbufferAttachmentNode attachmentNode(RapidGL::AttachmentNode::COLOR, "foo");

        // Connect nodes
        sceneNode.addChild(&framebufferNode);
        framebufferNode.addChild(&attachmentNode);

        // Attach attachment by visiting framebuffer node
        CPPUNIT_ASSERT_THROW(framebufferNode.preVisit(state), std::runtime_error);
    }

    /**
     * Ensures `RenderbufferAttachmentNode::attach` works correctly when its link is valid.
     */
    void testAttachWhenLinkIsValid() {

        // Create nodes
        RapidGL::SceneNode sceneNode;
        RapidGL::RenderbufferNode renderbufferNode("foo", GL_RED, 16, 9);
        RapidGL::FramebufferNode framebufferNode;
        RapidGL::RenderbufferAttachmentNode attachmentNode(RapidGL::AttachmentNode::COLOR, "foo");

        // Connect nodes
        sceneNode.addChild(&renderbufferNode);
        sceneNode.addChild(&framebufferNode);
        framebufferNode.addChild(&attachmentNode);

        // Attach attachment by visiting framebuffer node
        CPPUNIT_ASSERT_NO_THROW(framebufferNode.preVisit(state));
    }

    /**
     * Ensures `RenderbufferAttachmentNode::attach` throws if the link is the wrong type.
     */
    void testAttachWhenLinkIsWrongType() {

        // Create nodes
        RapidGL::SceneNode sceneNode;
        FakeNode fakeNode("foo");
        RapidGL::FramebufferNode framebufferNode;
        RapidGL::RenderbufferAttachmentNode attachmentNode(RapidGL::AttachmentNode::COLOR, "foo");

        // Connect nodes
        sceneNode.addChild(&fakeNode);
        sceneNode.addChild(&framebufferNode);
        framebufferNode.addChild(&attachmentNode);

        // Attach attachment by visiting framebuffer node
        CPPUNIT_ASSERT_THROW(framebufferNode.preVisit(state), std::runtime_error);
    }

    /**
     * Ensures `RenderbufferAttachmentNode::attach` throws if the node is the root node.
     */
    void testAttachWhenNodeIsRoot() {
        RapidGL::RenderbufferAttachmentNode attachmentNode(RapidGL::AttachmentNode::COLOR, "foo");
        CPPUNIT_ASSERT_THROW(attachmentNode.attach(GL_COLOR_ATTACHMENT0), std::runtime_error);
    }

    /**
     * Checks that `RenderbufferAttachmentNode::preVisit` works when its parent is a framebuffer node.
     */
    void testPreVisitWhenParentIsFramebufferNode() {
        RapidGL::FramebufferNode framebufferNode;
        RapidGL::RenderbufferAttachmentNode attachmentNode(RapidGL::AttachmentNode::COLOR, "foo");
        framebufferNode.addChild(&attachmentNode);
        CPPUNIT_ASSERT_NO_THROW(attachmentNode.preVisit(state));
    }

    /**
     * Checks that `RenderbufferAttachmentNode::preVisit` throws when its parent is not a framebuffer node.
     */
    void testPreVisitWhenParentIsNotFramebufferNode() {
        RapidGL::SceneNode sceneNode;
        RapidGL::RenderbufferAttachmentNode attachmentNode(RapidGL::AttachmentNode::COLOR, "foo");
        sceneNode.addChild(&attachmentNode);
        CPPUNIT_ASSERT_THROW(attachmentNode.preVisit(state), std::runtime_error);
    }

    /**
     * Checks that `RenderbufferAttachmentNode::preVisit` throws when its parent is `NULL`.
     */
    void testPreVisitWhenParentIsNull() {
        RapidGL::RenderbufferAttachmentNode attachmentNode(RapidGL::AttachmentNode::COLOR, "foo");
        CPPUNIT_ASSERT_THROW(attachmentNode.preVisit(state), std::runtime_error);
    }
};

int main(int argc, char* argv[]) {

    // Initialize
    if (!glfwInit()) {
        throw std::runtime_error("Could not initialize GLFW!");
    }

    // Open window
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 2);
    glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    if (!glfwOpenWindow(512, 512, 0, 0, 0, 0, 24, 0, GLFW_WINDOW)) {
        throw std::runtime_error("Could not open window!");
    }

    try {
        RenderbufferAttachmentNodeTest test;
        test.testAttachWhenLinkIsMissing();
        test.testAttachWhenLinkIsValid();
        test.testAttachWhenLinkIsWrongType();
        test.testAttachWhenNodeIsRoot();
        test.testPreVisitWhenParentIsFramebufferNode();
        test.testPreVisitWhenParentIsNotFramebufferNode();
        test.testPreVisitWhenParentIsNull();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        throw;
    }

    // Exit
    glfwTerminate();
    return 0;
}
