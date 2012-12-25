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
#include "RapidGL/ProgramNode.hxx"


/**
 * Unit test for Program.
 */
class ProgramNodeTest {
public:

    /**
     * Ensures ProgramNode::preVisit(State&) works correctly.
     */
    void testPreVisit() {

        // Create shader nodes
        RapidGL::ShaderNode vertexShaderNode(GL_VERTEX_SHADER, "RapidGL/basic.vert");
        RapidGL::ShaderNode fragmentShaderNode(GL_FRAGMENT_SHADER, "RapidGL/basic.frag");

        // Create program node and attach shader nodes
        RapidGL::ProgramNode programNode;
        programNode.addChild(&vertexShaderNode);
        programNode.addChild(&fragmentShaderNode);

        // Traverse nodes
        RapidGL::State state;
        programNode.preVisit(state);

        // Check
        Gloop::Program program = programNode.getProgram();
        CPPUNIT_ASSERT(program.linked());
    }
};

int main(int argc, char* argv[]) {

    // Capture the initial working directory before GLFW changes it
#ifdef __APPLE__
    const std::string cwd = Poco::Path::current();
#endif

    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Could not initialize GLFW!" << std::endl;
        return 1;
    }

    // Reset current directory
#ifdef __APPLE__
    chdir(cwd.c_str());
#endif

    // Open window
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 2);
    glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwOpenWindow(512, 512, 0, 0, 0, 0, 0, 0, GLFW_WINDOW);

    // Run test
    ProgramNodeTest test;
    try {
        test.testPreVisit();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        throw;
    }

    // Exit
    glfwTerminate();
    return 0;
}
