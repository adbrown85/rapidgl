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
#include <stdexcept>
#include <cppunit/extensions/HelperMacros.h>
#include <GL/glfw.h>
#include "RapidGL/Node.h"
#include "RapidGL/AttributeNode.h"
#include "RapidGL/AttributeNodeUnmarshaller.h"
using std::runtime_error;
using std::map;
using std::string;


/**
 * Unit test for `AttributeNodeUnmarshaller`.
 */
class AttributeNodeUnmarshallerTest {
public:

    /**
     * Formats an integer as a string.
     *
     * @param i Integer to format
     * @return Formatted string
     */
    static std::string formatInt(const GLint i) {
        std::stringstream stream;
        stream << i;
        return stream.str();
    }

    /**
     * Returns the maximum number of attributes in a shader program.
     */
    static GLint getMaxVertexAttribs() {
        GLint value;
        glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &value);
        return value;
    }

    // Unmarshaller to use for testing
    RapidGL::Unmarshaller* const unmarshaller;

    /**
     * Constructs the test.
     */
    AttributeNodeUnmarshallerTest() : unmarshaller(new RapidGL::AttributeNodeUnmarshaller()) {
        // empty
    }

    /**
     * Ensures `unmarshal` returns `-1` when location is empty.
     */
    void testUnmarshalWhenLocationIsEmpty() {

        // Make map
        map<string,string> attributes;
        attributes["name"] = "location";
        attributes["usage"] = "position";
        attributes["location"] = "";

        // Unmarshal node
        const RapidGL::Node* node = unmarshaller->unmarshal(attributes);
        const RapidGL::AttributeNode* attributeNode = dynamic_cast<const RapidGL::AttributeNode*>(node);
        CPPUNIT_ASSERT(attributeNode != NULL);

        // Check location
        CPPUNIT_ASSERT_EQUAL(-1, attributeNode->getLocation());
    }

    /**
     * Ensures `unmarshal` throws when location is the maximum value.
     */
    void testUnmarshalWhenLocationIsMax() {

        // Make map
        map<string,string> attributes;
        attributes["name"] = "location";
        attributes["usage"] = "position";
        attributes["location"] = formatInt(getMaxVertexAttribs() - 1);

        // Unmarshal node
        const RapidGL::Node* node = unmarshaller->unmarshal(attributes);
        const RapidGL::AttributeNode* attributeNode = dynamic_cast<const RapidGL::AttributeNode*>(node);
        CPPUNIT_ASSERT(attributeNode != NULL);

        // Check location
        CPPUNIT_ASSERT_EQUAL(getMaxVertexAttribs() - 1, attributeNode->getLocation());
    }

    /**
     * Ensures `unmarshal` throws when location is one more than the maximum value.
     */
    void testUnmarshalWhenLocationIsMaxPlusOne() {
        map<string,string> attributes;
        attributes["name"] = "location";
        attributes["usage"] = "position";
        attributes["location"] = formatInt(getMaxVertexAttribs());
        CPPUNIT_ASSERT_THROW(unmarshaller->unmarshal(attributes), std::runtime_error);
    }

    /**
     * Ensures `unmarshal` throws when location is the minimum value.
     */
    void testUnmarshalWhenLocationIsMin() {

        // Make map
        map<string,string> attributes;
        attributes["name"] = "location";
        attributes["usage"] = "position";
        attributes["location"] = "0";

        // Unmarshal node
        const RapidGL::Node* node = unmarshaller->unmarshal(attributes);
        const RapidGL::AttributeNode* attributeNode = dynamic_cast<const RapidGL::AttributeNode*>(node);
        CPPUNIT_ASSERT(attributeNode != NULL);

        // Check location
        CPPUNIT_ASSERT_EQUAL(0, attributeNode->getLocation());
    }

    /**
     * Ensures `unmarshal` throws when location is one less than the minimum value.
     */
    void testUnmarshalWhenLocationIsMinMinusOne() {
        map<string,string> attributes;
        attributes["name"] = "location";
        attributes["usage"] = "position";
        attributes["location"] = "-1";
        CPPUNIT_ASSERT_THROW(unmarshaller->unmarshal(attributes), std::runtime_error);
    }

    /**
     * Ensures `unmarshal` returns `-1` when location is missing.
     */
    void testUnmarshalWhenLocationIsMissing() {

        // Make map
        map<string,string> attributes;
        attributes["name"] = "location";
        attributes["usage"] = "position";

        // Unmarshal node
        const RapidGL::Node* node = unmarshaller->unmarshal(attributes);
        const RapidGL::AttributeNode* attributeNode = dynamic_cast<const RapidGL::AttributeNode*>(node);
        CPPUNIT_ASSERT(attributeNode != NULL);

        // Check location
        CPPUNIT_ASSERT_EQUAL(-1, attributeNode->getLocation());
    }

    /**
     * Ensures `unmarshal` throws an exception if _name_ is empty.
     */
    void testUnmarshalWithEmptyName() {
        map<string,string> attributes;
        attributes["name"] = "";
        attributes["usage"] = "position";
        CPPUNIT_ASSERT_THROW(unmarshaller->unmarshal(attributes), runtime_error);
    }

    /**
     * Ensures `unmarshal` throws an exception if _usage_ is empty.
     */
    void testUnmarshalWithEmptyUsage() {
        map<string,string> attributes;
        attributes["name"] = "MCVertex";
        attributes["usage"] = "";
        CPPUNIT_ASSERT_THROW(unmarshaller->unmarshal(attributes), runtime_error);
    }

    /**
     * Ensures `unmarshal` throws an exception if _usage_ is invalid.
     */
    void testUnmarshalWithInvalidUsage() {
        map<string,string> attributes;
        attributes["name"] = "MCVertex";
        attributes["usage"] = "foo";
        CPPUNIT_ASSERT_THROW(unmarshaller->unmarshal(attributes), runtime_error);
    }

    /**
     * Ensures `unmarshal` throws an exception if _name_ is unspecified.
     */
    void testUnmarshalWithUnspecifiedName() {
        map<string,string> attributes;
        attributes["usage"] = "position";
        CPPUNIT_ASSERT_THROW(unmarshaller->unmarshal(attributes), runtime_error);
    }

    /**
     * Ensures `unmarshal` throws an exception if _usage_ is unspecified.
     */
    void testUnmarshalWithUnspecifiedUsage() {
        map<string,string> attributes;
        attributes["name"] = "MCVertex";
        CPPUNIT_ASSERT_THROW(unmarshaller->unmarshal(attributes), runtime_error);
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

    // Run the test
    try {
        AttributeNodeUnmarshallerTest test;
        test.testUnmarshalWhenLocationIsEmpty();
        test.testUnmarshalWhenLocationIsMax();
        test.testUnmarshalWhenLocationIsMaxPlusOne();
        test.testUnmarshalWhenLocationIsMin();
        test.testUnmarshalWhenLocationIsMinMinusOne();
        test.testUnmarshalWhenLocationIsMissing();
        test.testUnmarshalWithEmptyName();
        test.testUnmarshalWithEmptyUsage();
        test.testUnmarshalWithInvalidUsage();
        test.testUnmarshalWithUnspecifiedName();
        test.testUnmarshalWithUnspecifiedUsage();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        throw;
    }

    // Exit
    glfwTerminate();
    return 0;
}
