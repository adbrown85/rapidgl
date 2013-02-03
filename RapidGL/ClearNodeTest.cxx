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

    // Clear node
    RapidGL::ClearNode* const clearNode;

    /**
     * Constructs a ClearNodeTest.
     */
    ClearNodeTest() : clearNode(new RapidGL::ClearNode()) {
        // empty
    }

    /**
     * Ensures `ClearNode::ClearNode()` initializes values properly.
     */
    void testClearNode() {
        const RapidGL::ClearNode node;
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0f, node.getRed(), TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0f, node.getGreen(), TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0f, node.getBlue(), TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0f, node.getAlpha(), TOLERANCE);
    }

    /**
     * Ensures `ClearNode::ClearNode(GLfloat, GLfloat, GLfloat, GLfloat)` initializes values properly.
     */
    void testClearNodeFloatFloatFloatFloat() {
        const RapidGL::ClearNode node(0.1f, 0.2f, 0.3f, 0.4f);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.1f, node.getRed(), TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.2f, node.getGreen(), TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.3f, node.getBlue(), TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.4f, node.getAlpha(), TOLERANCE);
    }

    /**
     * Ensures `ClearNode::ClearNode(GLfloat, GLfloat, GLfloat, GLfloat)` clamps high values.
     */
    void testClearNodeFloatFloatFloatFloatWithHighValues() {
        const RapidGL::ClearNode node(2, 2, 2, 2);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0f, node.getRed(), TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0f, node.getGreen(), TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0f, node.getBlue(), TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0f, node.getAlpha(), TOLERANCE);
    }

    /**
     * Ensures `ClearNode::ClearNode(GLfloat, GLfloat, GLfloat, GLfloat)` clamps low values.
     */
    void testClearNodeFloatFloatFloatFloatWithLowValues() {
        const RapidGL::ClearNode node(-1, -1, -1, -1);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0f, node.getRed(), TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0f, node.getGreen(), TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0f, node.getBlue(), TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0f, node.getAlpha(), TOLERANCE);
    }

    /**
     * Ensures `ClearNode::visit` works correctly.
     */
    void testVisit() {
        RapidGL::State state;
        RapidGL::Visitor visitor(&state);
        visitor.visit(clearNode);
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
        test.testClearNodeFloatFloatFloatFloat();
        test.testClearNodeFloatFloatFloatFloatWithHighValues();
        test.testClearNodeFloatFloatFloatFloatWithLowValues();
        test.testVisit();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        throw;
    }

    // Exit
    glfwTerminate();
    return 0;
}
