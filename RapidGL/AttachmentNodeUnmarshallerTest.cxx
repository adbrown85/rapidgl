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
#include <exception>
#include <iostream>
#include <map>
#include <stdexcept>
#include <string>
#include <cppunit/extensions/HelperMacros.h>
#include <GL/glfw.h>
#include "RapidGL/AttachmentNodeUnmarshaller.hxx"
#include "RapidGL/Node.hxx"


/**
 * Unit test for `AttachmentNodeUnmarshaller`.
 */
class AttachmentNodeUnmarshallerTest {
public:

    // Instance to use for testing
    RapidGL::AttachmentNodeUnmarshaller unmarshaller;

    /**
     * Ensures `AttachmentNodeUnmarshaller::unmarshal` throws when _type_ is the empty string.
     */
    void testUnmarshalWhenTypeIsEmpty() {
        std::map<std::string,std::string> attributes;
        attributes["type"] = "";
        CPPUNIT_ASSERT_THROW(unmarshaller.unmarshal(attributes), std::runtime_error);
    }

    /**
     * Ensures `AttachmentNodeUnmarshaller::unmarshal` throws when _type_ is _foo_.
     */
    void testUnmarshalWhenTypeIsFoo() {
        std::map<std::string,std::string> attributes;
        attributes["type"] = "foo";
        CPPUNIT_ASSERT_THROW(unmarshaller.unmarshal(attributes), std::runtime_error);
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
        throw std::runtime_error("Could not open GLFW window!");
    }

    // Run test
    try {
        AttachmentNodeUnmarshallerTest test;
        test.testUnmarshalWhenTypeIsEmpty();
        test.testUnmarshalWhenTypeIsFoo();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        throw;
    }

    // Exit
    glfwTerminate();
    return 0;
}
