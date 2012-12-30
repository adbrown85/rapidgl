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
#include "RapidGL/ShaderNode.hxx"


/**
 * Unit test for ShaderNode.
 */
class ShaderNodeTest {
public:

    /**
     * Ensures ShaderNode(GLenum, const string&) throws an exception if passed a bad type.
     */
    void testConstructorWithBadType() {
        CPPUNIT_ASSERT_THROW(new RapidGL::ShaderNode(GL_TEXTURE_2D, ""), std::invalid_argument);
    }

    /**
     * Ensures ShaderNode(GLenum, const string&) throws an exception if passed a bad file.
     */
    void testConstructorWithEmptyString() {
        CPPUNIT_ASSERT_THROW(new RapidGL::ShaderNode(GL_FRAGMENT_SHADER, ""), std::invalid_argument);
    }

    /**
     * Ensures ShaderNode(GLenum, const string&) works with a fragment shader.
     */
    void testConstructorWithGoodFragmentShader() {
        RapidGL::ShaderNode node(
                GL_FRAGMENT_SHADER,
                "#version 140\n"
                "out vec4 FragColor;\n"
                "void main() {\n"
                "    FragColor = vec4(1);\n"
                "}\n");
        Gloop::Shader shader = node.getShader();
        CPPUNIT_ASSERT(shader.compiled());
    }

    /**
     * Ensures ShaderNode(GLenum, const string&) works with a vertex shader.
     */
    void testConstructorWithGoodVertexShader() {
        RapidGL::ShaderNode node(
                GL_VERTEX_SHADER,
                "#version 140\n"
                "in vec4 MCVertex;\n"
                "void main() {\n"
                "    gl_Position = MCVertex;\n"
                "}\n");
        Gloop::Shader shader = node.getShader();
        CPPUNIT_ASSERT(shader.compiled());
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
    ShaderNodeTest test;
    try {
        test.testConstructorWithBadType();
        test.testConstructorWithEmptyString();
        test.testConstructorWithGoodFragmentShader();
        test.testConstructorWithGoodVertexShader();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        throw;
    }

    // Exit
    glfwTerminate();
    return 0;
}
