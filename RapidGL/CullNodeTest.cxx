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
#include <cppunit/extensions/HelperMacros.h>
#include <GL/glfw.h>
#include "RapidGL/CullNode.hxx"
#include "RapidGL/State.hxx"


/**
 * Unit test for `CullNode`.
 */
class CullNodeTest {
public:

    /**
     * Returns the value of `GL_CULL_FACE_MODE`.
     *
     * @return Value of `GL_CULL_FACE_MODE`
     */
    static GLenum getCullFaceMode() {
        GLint value;
        glGetIntegerv(GL_CULL_FACE_MODE, &value);
        return value;
    }

    /**
     * Returns a random value for `GL_CULL_FACE_MODE`.
     *
     * @return Random value for `GL_CULL_FACE_MODE`
     */
    static GLenum getRandomCullFaceMode() {
        const GLenum modes[] = { GL_BACK, GL_FRONT, GL_FRONT_AND_BACK };
        return modes[rand() % 2];
    }

    /**
     * Checks if `GL_CULL_FACE` is enabled.
     *
     * @return `true` if `GL_CULL_FACE` is enabled
     */
    static bool isCullFaceEnabled() {
        return glIsEnabled(GL_CULL_FACE) == GL_TRUE;
    }

    // State to pass when visiting, since `CullNode` doesn't affect it
    RapidGL::State state;

    /**
     * Ensures `CullNode::CullNode` accepts `GL_BACK`.
     */
    void testCullNodeWithBack() {
        RapidGL::CullNode node(GL_BACK);
    }

    /**
     * Ensures `CullNode::CullNode` accepts `GL_FRONT`.
     */
    void testCullNodeWithFront() {
        RapidGL::CullNode node(GL_FRONT);
    }

    /**
     * Ensures `CullNode::CullNode` accepts `GL_FRONT_AND_BACK`.
     */
    void testCullNodeWithFrontAndBack() {
        RapidGL::CullNode node(GL_FRONT_AND_BACK);
    }

    /**
     * Ensures `CullNode::CullNode` accepts `GL_NONE`.
     */
    void testCullNodeWithNone() {
        RapidGL::CullNode node(GL_NONE);
    }

    /**
     * Ensures `CullNode::visit` works correctly with `GL_BACK`.
     */
    void testVisitWithBack() {

        // Make the node
        RapidGL::CullNode node(GL_BACK);

        // Set up OpenGL state
        glDisable(GL_CULL_FACE);
        glCullFace(GL_FRONT);

        // Visit the node
        node.visit(state);

        // Check OpenGL state
        CPPUNIT_ASSERT(isCullFaceEnabled());
        CPPUNIT_ASSERT_EQUAL((GLenum) GL_BACK, getCullFaceMode());
    }

    /**
     * Ensures `CullNode::visit` works correctly with `GL_FRONT`.
     */
    void testVisitWithFront() {

        // Make the node
        RapidGL::CullNode node(GL_FRONT);

        // Set up OpenGL state
        glDisable(GL_CULL_FACE);
        glCullFace(GL_BACK);

        // Visit the node
        node.visit(state);

        // Check OpenGL state
        CPPUNIT_ASSERT(isCullFaceEnabled());
        CPPUNIT_ASSERT_EQUAL((GLenum) GL_FRONT, getCullFaceMode());
    }

    /**
     * Ensures `CullNode::visit` works correctly with `GL_FRONT_AND_BACK`.
     */
    void testVisitWithFrontAndBack() {

        // Make the node
        RapidGL::CullNode node(GL_FRONT_AND_BACK);

        // Set up OpenGL state
        glDisable(GL_CULL_FACE);
        glCullFace(GL_BACK);

        // Visit the node
        node.visit(state);

        // Check OpenGL state
        CPPUNIT_ASSERT(isCullFaceEnabled());
        CPPUNIT_ASSERT_EQUAL((GLenum) GL_FRONT_AND_BACK, getCullFaceMode());
    }

    /**
     * Ensures `CullNode::visit` works correctly with `GL_NONE`.
     */
    void testVisitWithNone() {

        // Make the node
        RapidGL::CullNode node(GL_NONE);

        // Set up OpenGL state
        const GLenum mode = getRandomCullFaceMode();
        glEnable(GL_CULL_FACE);
        glCullFace(mode);

        // Visit the node
        node.visit(state);

        // Check OpenGL state
        CPPUNIT_ASSERT(!isCullFaceEnabled());
        CPPUNIT_ASSERT_EQUAL(mode, getCullFaceMode());
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

    // Run test
    try {
        CullNodeTest test;
        test.testCullNodeWithBack();
        test.testCullNodeWithFront();
        test.testCullNodeWithFrontAndBack();
        test.testCullNodeWithNone();
        test.testVisitWithBack();
        test.testVisitWithFront();
        test.testVisitWithFrontAndBack();
        test.testVisitWithNone();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        throw;
    }

    // Exit
    glfwTerminate();
    return 0;
}
