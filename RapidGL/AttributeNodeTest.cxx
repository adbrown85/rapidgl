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
#include <stdexcept>
#include "RapidGL/AttributeNode.h"
#include "RapidGL/State.h"
#include "RapidGL/Visitor.h"
using RapidGL::AttributeNode;


/**
 * Unit test for AttributeNode.
 */
class AttributeNodeTest : public CppUnit::TestFixture {
public:

    /**
     * Fake node for testing.
     */
    class FakeNode : public RapidGL::Node {
    public:

        virtual void visit(RapidGL::State& state) {
            // empty
        }
    };

    /**
     * Ensures AttributeNode constructor throws an exception if passed an empty string.
     */
    void testAttributeNodeWhenNameIsEmpty() {
        CPPUNIT_ASSERT_THROW(new AttributeNode("", AttributeNode::POINT), std::invalid_argument);
    }

    /**
     * Ensures `AttributeNode::formatUsage` works for `COORDINATE`.
     */
    void testFormatUsageWithCoordinate() {
        CPPUNIT_ASSERT_EQUAL(std::string("COORDINATE"), AttributeNode::formatUsage(AttributeNode::COORDINATE));
    }

    /**
     * Ensures `AttributeNode::formatUsage` works for `NORMAL`.
     */
    void testFormatUsageWithNormal() {
        CPPUNIT_ASSERT_EQUAL(std::string("NORMAL"), AttributeNode::formatUsage(AttributeNode::NORMAL));
    }

    /**
     * Ensures `AttributeNode::formatUsage` works for `POINT`.
     */
    void testFormatUsageWithPoint() {
        CPPUNIT_ASSERT_EQUAL(std::string("POINT"), AttributeNode::formatUsage(AttributeNode::POINT));
    }

    /**
     * Ensures `AttributeNode::parseUsage` works for 'COORDINATE'.
     */
    void testParseUsageWithCoordinate() {
        const AttributeNode::Usage expected = AttributeNode::COORDINATE;
        const AttributeNode::Usage actual = AttributeNode::parseUsage("COORDINATE");
        CPPUNIT_ASSERT_EQUAL(expected, actual);
    }

    /**
     * Ensures `AttributeNode::parseUsage` throws an exception when passed an invalid string.
     */
    void testParseUsageWithInvalidString() {
        CPPUNIT_ASSERT_THROW(AttributeNode::parseUsage("foo"), std::invalid_argument);
    }

    /**
     * Ensures `AttributeNode::parseUsage` works for 'NORMAL'.
     */
    void testParseUsageWithNormal() {
        const AttributeNode::Usage expected = AttributeNode::NORMAL;
        const AttributeNode::Usage actual = AttributeNode::parseUsage("NORMAL");
        CPPUNIT_ASSERT_EQUAL(expected, actual);
    }

    /**
     * Ensures `AttributeNode::parseUsage` works for 'POINT'.
     */
    void testParseUsageWithVertex() {
        const AttributeNode::Usage expected = AttributeNode::POINT;
        const AttributeNode::Usage actual = AttributeNode::parseUsage("POINT");
        CPPUNIT_ASSERT_EQUAL(expected, actual);
    }

    /**
     * Ensures _preVisit_ throws an exception if called for first time when node has an invalid parent.
     */
    void testPreVisitWithInvalidParent() {

        // Make nodes
        FakeNode parentNode;
        AttributeNode attributeNode("MCVertex", AttributeNode::POINT);
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
        AttributeNode attributeNode("MCVertex", AttributeNode::POINT);

        // Check for throw
        RapidGL::State state;
        CPPUNIT_ASSERT_THROW(attributeNode.preVisit(state), std::runtime_error);
    }

    /**
     * Ensures _preVisit_ does not throw an exception when node has a valid parent.
     */
    void testPreVisitWithValidParent() {

        // Make vertex shader node
        RapidGL::ShaderNode vertexShaderNode(
                GL_VERTEX_SHADER,
                "#version 140\n"
                "in vec4 MCVertex;\n"
                "void main() {\n"
                "    gl_Position = MCVertex;\n"
                "}\n");

        // Make fragment shader node
        RapidGL::ShaderNode fragmentShaderNode(
                GL_FRAGMENT_SHADER,
                "#version 140\n"
                "out vec4 FragColor;\n"
                "void main() {\n"
                "    FragColor = vec4(1);\n"
                "}\n");

        // Make attribute node
        AttributeNode attributeNode("MCVertex", AttributeNode::POINT);

        // Make program node and add children
        RapidGL::ProgramNode programNode("foo");
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

    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Could not initialize GLFW!" << std::endl;
        return 1;
    }

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
        test.testAttributeNodeWhenNameIsEmpty();
        test.testFormatUsageWithCoordinate();
        test.testFormatUsageWithNormal();
        test.testFormatUsageWithPoint();
        test.testParseUsageWithCoordinate();
        test.testParseUsageWithInvalidString();
        test.testParseUsageWithNormal();
        test.testParseUsageWithVertex();
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
