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
#include <cppunit/extensions/HelperMacros.h>
#include <GL/glfw.h>
#include <Poco/Path.h>
#include <stdexcept>
#include "RapidGL/AttributeNode.hxx"
#include "RapidGL/State.hxx"
#include "RapidGL/Visitor.hxx"


/**
 * Unit test for AttributeNode.
 */
class AttributeNodeTest : public CppUnit::TestFixture {
public:

    /**
     * Ensures AttributeNode constructor throws an exception if passed an empty string.
     */
    void testConstructorWithEmptyName() {
        CPPUNIT_ASSERT_THROW(new RapidGL::AttributeNode("", RapidGL::AttributeNode::VERTEX), std::invalid_argument);
    }

    /**
     * Ensures _preVisit_ throws an exception if called for first time when node has an invalid parent.
     */
    void testPreVisitWithInvalidParent() {

        // Make nodes
        RapidGL::Node parentNode;
        RapidGL::AttributeNode attributeNode("MCVertex", RapidGL::AttributeNode::VERTEX);
        parentNode.addChild(&attributeNode);

        // Check for throw
        RapidGL::State state;
        CPPUNIT_ASSERT_THROW(attributeNode.preVisit(state), std::runtime_error);
    }

    /**
     * Ensures _preVisit_ throws an exception if called for first time when node does not have a parent.
     */
    void testPreVisitWithNoParent() {

        // Make node
        RapidGL::AttributeNode attributeNode("MCVertex", RapidGL::AttributeNode::VERTEX);

        // Check for throw
        RapidGL::State state;
        CPPUNIT_ASSERT_THROW(attributeNode.preVisit(state), std::runtime_error);
    }

    /**
     * Ensures _preVisit_ does not throw an exception when node has a valid parent.
     */
    void testPreVisitWithValidParent() {

        // Make nodes
        RapidGL::ProgramNode programNode;
        RapidGL::ShaderNode vertexShaderNode(GL_VERTEX_SHADER, "RapidGL/basic.vert");
        RapidGL::ShaderNode fragmentShaderNode(GL_FRAGMENT_SHADER, "RapidGL/basic.frag");
        RapidGL::AttributeNode attributeNode("MCVertex", RapidGL::AttributeNode::VERTEX);

        // Arrange nodes
        programNode.addChild(&vertexShaderNode);
        programNode.addChild(&fragmentShaderNode);
        programNode.addChild(&attributeNode);

        // Visit nodes
        RapidGL::State state;
        RapidGL::Visitor visitor(&state);
        visitor.visit(&programNode);
    }
};

int main(int argc, char* argv[]) {

    // Capture current working directory before GLFW changes it
#ifdef __APPLE__
    const std::string cwd = Poco::Path::current();
#endif

    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Could not initialize GLFW!" << std::endl;
        return 1;
    }

    // Change the working directory back
#ifdef __APPLE__
    chdir(cwd.c_str());
#endif

    // Open window
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 2);
    glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    if (!glfwOpenWindow(512, 512, 0, 0, 0, 0, 0, 0, GLFW_WINDOW)) {
        std::cerr << "Could not open GLFW window!" << std::endl;
        return 1;
    }

    // Run test
    try {
        AttributeNodeTest test;
        test.testConstructorWithEmptyName();
        test.testPreVisitWithInvalidParent();
        test.testPreVisitWithNoParent();
        test.testPreVisitWithValidParent();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    // Exit
    glfwTerminate();
    return 0;
}
