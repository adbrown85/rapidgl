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
     * Returns the maximum number of vertex attributes in a shader program.
     *
     * @return Maximum number of vertex attributes in a shader program
     */
    static GLint getMaxVertexAttribs() {
        GLint value;
        glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &value);
        return value;
    }

    // Maximum number of vertex attributes in a shader program
    const GLint maxVertexAttribs;

    /**
     * Constructs the test.
     */
    AttributeNodeTest() : maxVertexAttribs(getMaxVertexAttribs()) {
        // empty
    }

    /**
     * Ensures constructor works if passed the maximum location value.
     */
    void testAttributeNodeWhenLocationIsMax() {
        const AttributeNode node("foo", AttributeNode::POSITION, maxVertexAttribs - 1);
        CPPUNIT_ASSERT_EQUAL(maxVertexAttribs - 1, node.getLocation());
    }

    /**
     * Ensures constructor throws if passed one more than the maximum location value.
     */
    void testAttributeNodeWhenLocationIsMaxPlusOne() {
        CPPUNIT_ASSERT_THROW(AttributeNode("foo", AttributeNode::POSITION, maxVertexAttribs), std::invalid_argument);
    }

    /**
     * Ensures constructor works if passed the minimum location value.
     */
    void testAttributeNodeWhenLocationIsMin() {
        const AttributeNode node("foo", AttributeNode::POSITION, -1);
        CPPUNIT_ASSERT_EQUAL(-1, node.getLocation());
    }

    /**
     * Ensures constructor throws if passed one less than the minimum location.
     */
    void testAttributeNodeWhenLocationIsMinMinusOne() {
        CPPUNIT_ASSERT_THROW(AttributeNode("foo", AttributeNode::POSITION, -2), std::invalid_argument);
    }

    /**
     * Ensures AttributeNode constructor throws an exception if passed an empty string.
     */
    void testAttributeNodeWhenNameIsEmpty() {
        CPPUNIT_ASSERT_THROW(new AttributeNode("", AttributeNode::POSITION, -1), std::invalid_argument);
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
     * Ensures `AttributeNode::formatUsage` works for `POSITION`.
     */
    void testFormatUsageWithPosition() {
        CPPUNIT_ASSERT_EQUAL(std::string("POSITION"), AttributeNode::formatUsage(AttributeNode::POSITION));
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
     * Ensures `AttributeNode::parseUsage` works for 'POSITION'.
     */
    void testParseUsageWithVertex() {
        const AttributeNode::Usage expected = AttributeNode::POSITION;
        const AttributeNode::Usage actual = AttributeNode::parseUsage("POSITION");
        CPPUNIT_ASSERT_EQUAL(expected, actual);
    }

    /**
     * Ensures _preVisit_ throws an exception if called for first time when node does not have a parent.
     */
    void testPreVisitWithNoParent() {

        // Make node
        AttributeNode attributeNode("MCVertex", AttributeNode::POSITION, -1);

        // Check for throw
        RapidGL::State state;
        CPPUNIT_ASSERT_THROW(attributeNode.preVisit(state), std::runtime_error);
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
        test.testAttributeNodeWhenLocationIsMax();
        test.testAttributeNodeWhenLocationIsMaxPlusOne();
        test.testAttributeNodeWhenLocationIsMin();
        test.testAttributeNodeWhenLocationIsMinMinusOne();
        test.testAttributeNodeWhenNameIsEmpty();
        test.testFormatUsageWithCoordinate();
        test.testFormatUsageWithNormal();
        test.testFormatUsageWithPosition();
        test.testParseUsageWithCoordinate();
        test.testParseUsageWithInvalidString();
        test.testParseUsageWithNormal();
        test.testParseUsageWithVertex();
        test.testPreVisitWithNoParent();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    // Exit
    glfwTerminate();
    return 0;
}
