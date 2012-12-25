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
#include <GL/glfw.h>
#include <cppunit/extensions/HelperMacros.h>
#include <iostream>
#include "RapidGL/ClearNode.hxx"
#include "RapidGL/Node.hxx"
#include "RapidGL/State.hxx"
#include "RapidGL/Visitor.hxx"
using namespace std;


/**
 * Test for ClearNode.
 */
class ClearNodeTest {
public:

    // Threshold for floating-point comparisons
    static const GLfloat TOLERANCE = 1e-6f;

    // Clear node
    RapidGL::ClearNode* clearNode;

    /**
     * Constructs a ClearNodeTest.
     */
    ClearNodeTest() {

        // Create the clear node
        clearNode = new RapidGL::ClearNode();

        // Check its initial values
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0f, clearNode->getRed(), TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0f, clearNode->getGreen(), TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0f, clearNode->getBlue(), TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0f, clearNode->getAlpha(), TOLERANCE);

        // Set the values
        clearNode->setRed(0.1f);
        clearNode->setGreen(0.2f);
        clearNode->setBlue(0.3f);
        clearNode->setAlpha(0.4f);

        // Check its new values
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.1f, clearNode->getRed(), TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.2f, clearNode->getGreen(), TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.3f, clearNode->getBlue(), TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.4f, clearNode->getAlpha(), TOLERANCE);
    }

    /**
     * Renders the test.
     */
    void render() {
        RapidGL::State state;
        RapidGL::Visitor visitor(&state);
        visitor.visit(clearNode);
    }
};


int main(int argc, char* argv[]) {

    // Initialize GLFW
    if (!glfwInit()) {
        cerr << "Could not initialize GLFW!" << endl;
        return 1;
    }

    // Open a window
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 2);
    glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    int open = glfwOpenWindow(512, 512, 0, 0, 0, 0, 0, 0, GLFW_WINDOW);
    if (!open) {
        cerr << "Could not open window!" << endl;
        return 1;
    }

    // Run test
    ClearNodeTest clearNodeTest;
    while (open) {
        glfwWaitEvents();
        clearNodeTest.render();
        glfwSwapBuffers();
        open = glfwGetWindowParam(GLFW_OPENED);
    }

    // Exit
    glfwTerminate();
    return 0;
}
