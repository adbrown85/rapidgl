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
#include "RapidGL/DepthFunctionNode.h"
#include "RapidGL/State.h"


/**
 * Unit test for `DepthFunctionNode`.
 */
class DepthFunctionNodeTest {
public:

    /**
     * Returns the current OpenGL depth function.
     */
    static GLenum getDepthFunc() {
        GLint value;
        glGetIntegerv(GL_DEPTH_FUNC, &value);
        return (GLenum) value;
    }

    // Reusable state since `DepthFunctionNode` doesn't use it
    RapidGL::State state;

    /**
     * Ensures constructor works with `GL_ALWAYS`.
     */
    void testDepthFunctionNodeWithAlways() {
        const RapidGL::DepthFunctionNode node(GL_ALWAYS);
        CPPUNIT_ASSERT_EQUAL((GLenum) GL_ALWAYS, node.getFunction());
    }

    /**
     * Ensures constructor works with `GL_EQUAL`.
     */
    void testDepthFunctionNodeWithEqual() {
        const RapidGL::DepthFunctionNode node(GL_EQUAL);
        CPPUNIT_ASSERT_EQUAL((GLenum) GL_EQUAL, node.getFunction());
    }

    /**
     * Ensures constructor works with `GL_GEQUAL`.
     */
    void testDepthFunctionNodeWithGequal() {
        const RapidGL::DepthFunctionNode node(GL_GEQUAL);
        CPPUNIT_ASSERT_EQUAL((GLenum) GL_GEQUAL, node.getFunction());
    }


    /**
     * Ensures constructor works with `GL_GREATER`.
     */
    void testDepthFunctionNodeWithGreater() {
        const RapidGL::DepthFunctionNode node(GL_GREATER);
        CPPUNIT_ASSERT_EQUAL((GLenum) GL_GREATER, node.getFunction());
    }

    /**
     * Ensures constructor works with `GL_LEQUAL`.
     */
    void testDepthFunctionNodeWithLequal() {
        const RapidGL::DepthFunctionNode node(GL_LEQUAL);
        CPPUNIT_ASSERT_EQUAL((GLenum) GL_LEQUAL, node.getFunction());
    }

    /**
     * Ensures constructor works with `GL_LESS`.
     */
    void testDepthFunctionNodeWithLess() {
        const RapidGL::DepthFunctionNode node(GL_LESS);
        CPPUNIT_ASSERT_EQUAL((GLenum) GL_LESS, node.getFunction());
    }

    /**
     * Ensures constructor works with `GL_NEVER`.
     */
    void testDepthFunctionNodeWithNever() {
        const RapidGL::DepthFunctionNode node(GL_NEVER);
        CPPUNIT_ASSERT_EQUAL((GLenum) GL_NEVER, node.getFunction());
    }

    /**
     * Ensures constructor works with `GL_NOTEQUAL`.
     */
    void testDepthFunctionNodeWithNotEqual() {
        const RapidGL::DepthFunctionNode node(GL_NOTEQUAL);
        CPPUNIT_ASSERT_EQUAL((GLenum) GL_NOTEQUAL, node.getFunction());
    }

    /**
     * Ensures `DepthFunctionNode::visit` works with `GL_ALWAYS`.
     */
    void testVisitWithAlways() {
        RapidGL::DepthFunctionNode node(GL_ALWAYS);
        node.visit(state);
        CPPUNIT_ASSERT_EQUAL((GLenum) GL_ALWAYS, node.getFunction());
    }

    /**
     * Ensures `DepthFunctionNode::visit` works with `GL_EQUAL`.
     */
    void testVisitWithEqual() {
        RapidGL::DepthFunctionNode node(GL_EQUAL);
        node.visit(state);
        CPPUNIT_ASSERT_EQUAL((GLenum) GL_EQUAL, getDepthFunc());
    }

    /**
     * Ensures `DepthFunctionNode::visit` works with `GL_GEQUAL`.
     */
    void testVisitWithGequal() {
        RapidGL::DepthFunctionNode node(GL_GEQUAL);
        node.visit(state);
        CPPUNIT_ASSERT_EQUAL((GLenum) GL_GEQUAL, getDepthFunc());
    }


    /**
     * Ensures `DepthFunctionNode::visit` works with `GL_GREATER`.
     */
    void testVisitWithGreater() {
        RapidGL::DepthFunctionNode node(GL_GREATER);
        node.visit(state);
        CPPUNIT_ASSERT_EQUAL((GLenum) GL_GREATER, getDepthFunc());
    }

    /**
     * Ensures `DepthFunctionNode::visit` works with `GL_LEQUAL`.
     */
    void testVisitWithLequal() {
        RapidGL::DepthFunctionNode node(GL_LEQUAL);
        node.visit(state);
        CPPUNIT_ASSERT_EQUAL((GLenum) GL_LEQUAL, getDepthFunc());
    }

    /**
     * Ensures `DepthFunctionNode::visit` works with `GL_LESS`.
     */
    void testVisitWithLess() {
        RapidGL::DepthFunctionNode node(GL_LESS);
        node.visit(state);
        CPPUNIT_ASSERT_EQUAL((GLenum) GL_LESS, getDepthFunc());
    }

    /**
     * Ensures `DepthFunctionNode::visit` works with `GL_NEVER`.
     */
    void testVisitWithNever() {
        RapidGL::DepthFunctionNode node(GL_NEVER);
        node.visit(state);
        CPPUNIT_ASSERT_EQUAL((GLenum) GL_NEVER, getDepthFunc());
    }

    /**
     * Ensures `DepthFunctionNode::visit` works with `GL_NOTEQUAL`.
     */
    void testVisitWithNotEqual() {
        RapidGL::DepthFunctionNode node(GL_NOTEQUAL);
        node.visit(state);
        CPPUNIT_ASSERT_EQUAL((GLenum) GL_NOTEQUAL, getDepthFunc());
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
        throw std::runtime_error("Could not open window!");
    }

    // Run test
    try {
        DepthFunctionNodeTest test;
        test.testDepthFunctionNodeWithAlways();
        test.testDepthFunctionNodeWithEqual();
        test.testDepthFunctionNodeWithGequal();
        test.testDepthFunctionNodeWithGreater();
        test.testDepthFunctionNodeWithLequal();
        test.testDepthFunctionNodeWithLess();
        test.testDepthFunctionNodeWithNever();
        test.testDepthFunctionNodeWithNotEqual();
        test.testVisitWithAlways();
        test.testVisitWithEqual();
        test.testVisitWithGequal();
        test.testVisitWithGreater();
        test.testVisitWithLequal();
        test.testVisitWithLess();
        test.testVisitWithNever();
        test.testVisitWithNotEqual();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        throw;
    }

    // Exit
    glfwTerminate();
    return 0;
}
