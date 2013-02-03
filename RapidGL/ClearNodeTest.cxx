/*
 * RapidGL - Rapid prototyping for OpenGL
 * Copyright (C) 2012  Andrew Brown
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
#include <cppunit/extensions/HelperMacros.h>
#include <GL/glfw.h>
#include <glycerin/Color.hxx>
#include "RapidGL/ClearNode.h"
#include "RapidGL/Node.h"
#include "RapidGL/State.h"
#include "RapidGL/Visitor.h"


/**
 * Test for ClearNode.
 */
class ClearNodeTest {
public:

    // Number of seconds to sleep after rendering
    static const double SLEEP_TIME_IN_SECONDS = 1.0;

    // Threshold for floating-point comparisons
    static const GLfloat TOLERANCE = 1e-6f;

    /**
     * Ensures `ClearNode::ClearNode()` initializes values properly.
     */
    void testClearNode() {
        const RapidGL::ClearNode node;
        const Glycerin::Color color = node.getColor();
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0f, color.r, TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0f, color.g, TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0f, color.b, TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0f, color.a, TOLERANCE);
    }

    /**
     * Ensures `ClearNode::ClearNode(Color)` initializes values properly.
     */
    void testClearNodeColor() {
        const RapidGL::ClearNode node(Glycerin::Color(0.1f, 0.2f, 0.3f, 0.4f));
        const Glycerin::Color color = node.getColor();
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.1f, color.r, TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.2f, color.g, TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.3f, color.b, TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.4f, color.a, TOLERANCE);
    }

    /**
     * Ensures `ClearNode::ClearNode(Color)` clamps high values.
     */
    void testClearNodeColorWithHighValues() {
        const RapidGL::ClearNode node(Glycerin::Color(2, 2, 2, 2));
        const Glycerin::Color color = node.getColor();
        CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0f, color.r, TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0f, color.g, TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0f, color.b, TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0f, color.a, TOLERANCE);
    }

    /**
     * Ensures `ClearNode::ClearNode(Color)` clamps low values.
     */
    void testClearNodeColorWithLowValues() {
        const RapidGL::ClearNode node(Glycerin::Color(-1, -1, -1, -1));
        const Glycerin::Color color = node.getColor();
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0f, color.r, TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0f, color.g, TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0f, color.b, TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0f, color.a, TOLERANCE);
    }

    /**
     * Ensures `ClearNode::visit` works correctly.
     */
    void testVisit() {

        // Create the node
        RapidGL::ClearNode clearNode(Glycerin::Color(0.1f, 0.2f, 0.3f, 0.4f));

        // Visit the node
        RapidGL::State state;
        RapidGL::Visitor visitor(&state);
        visitor.visit(&clearNode);

        // Refresh
        glfwSwapBuffers();
        glfwSleep(SLEEP_TIME_IN_SECONDS);
    }
};


int main(int argc, char* argv[]) {

    // Initialize GLFW
    if (!glfwInit()) {
        throw std::runtime_error("Could not initialize GLFW!");
    }

    // Open a window
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 2);
    glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    if (!glfwOpenWindow(512, 512, 0, 0, 0, 0, 0, 0, GLFW_WINDOW)) {
        throw std::runtime_error("Could not open window!");
    }

    // Run test
    try {
        ClearNodeTest test;
        test.testClearNode();
        test.testClearNodeColor();
        test.testClearNodeColorWithHighValues();
        test.testClearNodeColorWithLowValues();
        test.testVisit();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        throw;
    }

    // Exit
    glfwTerminate();
    return 0;
}
