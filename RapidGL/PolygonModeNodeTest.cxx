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
#include <cassert>
#include <exception>
#include <iostream>
#include <stdexcept>
#include <cppunit/extensions/HelperMacros.h>
#include <GL/glfw.h>
#include "RapidGL/PolygonModeNode.h"
#include "RapidGL/State.h"


/**
 * Unit test for `PolygonModeNode`.
 */
class PolygonModeNodeTest {
public:

    /**
     * Returns the current value of `GL_POLYGON_MODE`.
     */
    static GLenum getPolygonMode() {
        GLint value[2];
        glGetIntegerv(GL_POLYGON_MODE, value);
        assert (value[0] == value[1]);
        return value[0];
    }

    // Reusable state since `PolygonMode` doesn't use it
    RapidGL::State state;

    /**
     * Ensures `PolgyonModeNode` constructor works with `GL_FILL`.
     */
    void testPolygonModeNodeWithFill() {
        const GLenum expected = GL_FILL;
        const RapidGL::PolygonModeNode node(expected);
        CPPUNIT_ASSERT_EQUAL(expected, node.getMode());
    }

    /**
     * Ensures `PolgyonModeNode` constructor works with `GL_LINE`.
     */
    void testPolygonModeNodeWithLine() {
        const GLenum expected = GL_LINE;
        const RapidGL::PolygonModeNode node(expected);
        CPPUNIT_ASSERT_EQUAL(expected, node.getMode());
    }

    /**
     * Ensures `PolgyonModeNode` constructor works with `GL_POINT`.
     */ void testPolygonModeNodeWithPoint() { const GLenum expected = GL_POINT;
        const RapidGL::PolygonModeNode node(expected);
        CPPUNIT_ASSERT_EQUAL(expected, node.getMode());
    }

    /**
     * Ensures `PolygonModeNode` constructor throws if passed `GL_VERSION`.
     */
    void testPolygonModeNodeWithVersion() {
        CPPUNIT_ASSERT_THROW(RapidGL::PolygonModeNode(GL_VERSION), std::invalid_argument);
    }

    /**
     * Ensures `PolygonModeNode` throws if passed `GL_FILL`.
     */
    void testVisitWithFill() {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        RapidGL::PolygonModeNode node(GL_FILL);
        node.visit(state);
        CPPUNIT_ASSERT_EQUAL((GLenum) GL_FILL, getPolygonMode());
    }

    /**
     * Ensures `PolygonModeNode` throws if passed `GL_LINE`.
     */
    void testVisitWithLine() {
        glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
        RapidGL::PolygonModeNode node(GL_LINE);
        node.visit(state);
        CPPUNIT_ASSERT_EQUAL((GLenum) GL_LINE, getPolygonMode());
    }

    /**
     * Ensures `PolygonModeNode` throws if passed `GL_POINT`.
     */
    void testVisitWithPoint() {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        RapidGL::PolygonModeNode node(GL_POINT);
        node.visit(state);
        CPPUNIT_ASSERT_EQUAL((GLenum) GL_POINT, getPolygonMode());
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
    if (!glfwOpenWindow(512, 512, 0, 0, 0, 0, 0, 0, GLFW_WINDOW)) {
        throw std::runtime_error("Could not open window!");
    }

    // Run test
    try {
        PolygonModeNodeTest test;
        test.testPolygonModeNodeWithFill();
        test.testPolygonModeNodeWithLine();
        test.testPolygonModeNodeWithPoint();
        test.testPolygonModeNodeWithVersion();
        test.testVisitWithFill();
        test.testVisitWithLine();
        test.testVisitWithPoint();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        throw;
    }

    // Exit
    glfwTerminate();
    return 0;
}
