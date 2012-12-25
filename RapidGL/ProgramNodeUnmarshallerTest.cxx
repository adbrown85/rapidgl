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
#include "RapidGL/Node.hxx"
#include "RapidGL/ProgramNode.hxx"
#include "RapidGL/ProgramNodeUnmarshaller.hxx"


/**
 * Unit test for ProgramNodeUnmarshaller.
 */
class ProgramUnmarshallerTest {
public:

    // Unmarshaller to use for testing
    RapidGL::ProgramNodeUnmarshaller unmarshaller;

    /**
     * Ensures ProgramNodeUnmarshaller::unmarshal(const map<string,string>&) works correctly.
     */
    void testUnmarshal() {
        std::map<std::string,std::string> attributes;
        RapidGL::Node* node = unmarshaller.unmarshal(attributes);
        RapidGL::ProgramNode* programNode = dynamic_cast<RapidGL::ProgramNode*>(node);
        CPPUNIT_ASSERT(programNode != NULL);
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
    glfwOpenWindow(512, 512, 0, 0, 0, 0, 0, 0, GLFW_WINDOW);

    // Run test
    ProgramUnmarshallerTest test;
    try {
        test.testUnmarshal();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        throw;
    }

    // Exit
    glfwTerminate();
    return 0;
}
