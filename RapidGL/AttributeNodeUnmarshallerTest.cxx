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

    // Unmarshaller to use for testing
    RapidGL::Unmarshaller* const unmarshaller;

    /**
     * Constructs the test.
     */
    AttributeNodeUnmarshallerTest() : unmarshaller(new RapidGL::AttributeNodeUnmarshaller()) {
        // empty
    }

    /**
     * Ensures `unmarshal` throws an exception if _name_ is empty.
     */
    void testUnmarshalWithEmptyName() {
        map<string,string> attributes;
        attributes["name"] = "";
        attributes["usage"] = "point";
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
        attributes["usage"] = "point";
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
