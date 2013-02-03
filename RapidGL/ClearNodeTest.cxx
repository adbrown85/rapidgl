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
     * Returns the current OpenGL clear color.
     */
    static Glycerin::Color getClearColor() {
        GLfloat arr[4];
        glGetFloatv(GL_COLOR_CLEAR_VALUE, arr);
        return Glycerin::Color::fromArray(arr);
    }

    /**
     * Returns the current OpenGL clear depth.
     */
    static GLfloat getClearDepth() {
        GLfloat value;
        glGetFloatv(GL_DEPTH_CLEAR_VALUE, &value);
        return value;
    }

    // Reusable state since `ClearNode` doesn't modify it
    RapidGL::State state;

    // Pre-defined colors
    const Glycerin::Color BLACK;
    const Glycerin::Color WHITE;

    /**
     * Constructs the test.
     */
    ClearNodeTest() : BLACK(0, 0, 0, 1), WHITE(1, 1, 1, 1) {
        // empty
    }

    /**
     * Ensures `ClearNode::ClearNode(Bitfield, Color, Float)` initializes color value properly.
     */
    void testClearNodeBitfieldColorFloatWhenColorIsValid() {
        const RapidGL::ClearNode node(GL_COLOR_BUFFER_BIT, Glycerin::Color(0.1f, 0.2f, 0.3f, 0.4f), 0.5f);
        const Glycerin::Color color = node.getColor();
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.1f, color.r, TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.2f, color.g, TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.3f, color.b, TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.4f, color.a, TOLERANCE);
    }

    /**
     * Ensures `ClearNode::ClearNode(Bitfield, Color, Float)` initializes depth value properly.
     */
    void testClearNodeBitfieldColorFloatWhenDepthIsValid() {
        const RapidGL::ClearNode node(GL_COLOR_BUFFER_BIT, Glycerin::Color(0.1f, 0.2f, 0.3f, 0.4f), 0.5f);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.5f, node.getDepth(), TOLERANCE);
    }

    /**
     * Ensures `ClearNode::ClearNode(Bitfield, Color, Float)` works with color buffer bit.
     */
    void testClearNodeBitfieldColorFloatWhenMaskIsColorBufferBit() {
        const GLbitfield expected = GL_COLOR_BUFFER_BIT;
        const RapidGL::ClearNode node(expected, BLACK, 0.0f);
        CPPUNIT_ASSERT_EQUAL(expected, node.getMask());
    }

    /**
     * Ensures `ClearNode::ClearNode(Bitfield, Color, Float)` works with both color and depth buffer bits.
     */
    void testClearNodeBitfieldColorFloatWhenMaskIsColorDepthBufferBits() {
        const GLbitfield expected = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT;
        const RapidGL::ClearNode node(expected, BLACK, 0.0f);
        CPPUNIT_ASSERT_EQUAL(expected, node.getMask());
    }

    /**
     * Ensures `ClearNode::ClearNode(Bitfield, Color, Float)` works with depth buffer bit.
     */
    void testClearNodeBitfieldColorFloatWhenMaskIsDepthBufferBit() {
        const GLbitfield expected = GL_DEPTH_BUFFER_BIT;
        const RapidGL::ClearNode node(expected, BLACK, 0.0f);
        CPPUNIT_ASSERT_EQUAL(expected, node.getMask());
    }

    /**
     * Ensures `ClearNode::ClearNode(Bitfield, Color, Float)` throws if passed an invalid mask.
     */
    void testClearNodeBitfieldColorFloatWhenMaskIsInvalid() {
        CPPUNIT_ASSERT_THROW(RapidGL::ClearNode(GL_VERSION, BLACK, 0.0f), std::invalid_argument);
    }

    /**
     * Ensures `ClearNode::ClearNode(Bitfield, Color, Float)` clamps high values.
     */
    void testClearNodeBitfieldColorFloatWithHighValues() {
        const RapidGL::ClearNode node(GL_COLOR_BUFFER_BIT, Glycerin::Color(2, 2, 2, 2), 2);
        const Glycerin::Color color = node.getColor();
        CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0f, color.r, TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0f, color.g, TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0f, color.b, TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0f, color.a, TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0f, node.getDepth(), TOLERANCE);
    }

    /**
     * Ensures `ClearNode::ClearNode(Bitfield, Color, Float)` clamps low values.
     */
    void testClearNodeBitfieldColorFloatWithLowValues() {
        const RapidGL::ClearNode node(GL_COLOR_BUFFER_BIT, Glycerin::Color(-1, -1, -1, -1), -1);
        const Glycerin::Color color = node.getColor();
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0f, color.r, TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0f, color.g, TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0f, color.b, TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0f, color.a, TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0f, node.getDepth(), TOLERANCE);
    }

    /**
     * Ensures `ClearNode::visit` works for color.
     */
    void testVisitWithColor() {

        // Create the node
        const GLbitfield mask = GL_COLOR_BUFFER_BIT;
        RapidGL::ClearNode clearNode(mask, Glycerin::Color(0.1f, 0.2f, 0.3f, 0.4f), 0.0f);

        // Visit the node
        RapidGL::Visitor visitor(&state);
        visitor.visit(&clearNode);

        // Check the clear values
        CPPUNIT_ASSERT_EQUAL(Glycerin::Color(0.1f, 0.2f, 0.3f, 0.4f), getClearColor());
        CPPUNIT_ASSERT_EQUAL(1.0f, getClearDepth());

        // Reset the clear color
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    }

    /**
     * Ensures `ClearNode::visit` works for color and depth.
     */
    void testVisitWithColorAndDepth() {

        // Create the node
        const GLbitfield mask = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT;
        RapidGL::ClearNode clearNode(mask, Glycerin::Color(0.1f, 0.2f, 0.3f, 0.4f), 0.5f);

        // Visit the node
        RapidGL::Visitor visitor(&state);
        visitor.visit(&clearNode);

        // Check the clear depth
        CPPUNIT_ASSERT_EQUAL(Glycerin::Color(0.1f, 0.2f, 0.3f, 0.4f), getClearColor());
        CPPUNIT_ASSERT_EQUAL(0.5f, getClearDepth());

        // Reset the clear values
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClearDepth(1.0f);
    }

    /**
     * Ensures `ClearNode::visit` works for depth.
     */
    void testVisitWithDepth() {

        // Create the node
        const GLbitfield mask = GL_DEPTH_BUFFER_BIT;
        RapidGL::ClearNode clearNode(mask, Glycerin::Color(0.1f, 0.2f, 0.3f, 0.4f), 0.5f);

        // Visit the node
        RapidGL::Visitor visitor(&state);
        visitor.visit(&clearNode);

        // Check the clear depth
        CPPUNIT_ASSERT_EQUAL(Glycerin::Color(0.0f, 0.0f, 0.0f, 0.0f), getClearColor());
        CPPUNIT_ASSERT_EQUAL(0.5f, getClearDepth());

        // Reset the clear depth
        glClearDepth(1.0f);
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
        test.testClearNodeBitfieldColorFloatWhenColorIsValid();
        test.testClearNodeBitfieldColorFloatWhenDepthIsValid();
        test.testClearNodeBitfieldColorFloatWhenMaskIsColorBufferBit();
        test.testClearNodeBitfieldColorFloatWhenMaskIsColorDepthBufferBits();
        test.testClearNodeBitfieldColorFloatWhenMaskIsDepthBufferBit();
        test.testClearNodeBitfieldColorFloatWhenMaskIsInvalid();
        test.testClearNodeBitfieldColorFloatWithHighValues();
        test.testClearNodeBitfieldColorFloatWithLowValues();
        test.testVisitWithColor();
        test.testVisitWithDepth();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        throw;
    }

    // Exit
    glfwTerminate();
    return 0;
}
