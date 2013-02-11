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
#include "RapidGL/FloatUniformNode.h"
#include "RapidGL/ProgramNode.h"
#include "RapidGL/SceneNode.h"
#include "RapidGL/ShaderNode.h"
#include "RapidGL/State.h"
#include "RapidGL/Visitor.h"
#include "RapidGL/UseNode.h"


/**
 * Unit test for FloatUniformNode.
 */
class FloatUniformNodeTest {
public:

    // Threshold for floating-point comparisons
    static const double TOLERANCE = 1e-9;

    /**
     * Returns the source code for the vertex shader.
     */
    static std::string getVertexShaderSource() {
        return
                "#version 140\n"
                "in vec4 MCVertex;\n"
                "void main() {\n"
                "  gl_Position = MCVertex;\n"
                "}\n";
    }

    /**
     * Returns the source code for the fragment shader.
     */
    static std::string getFragmentShaderSource() {
        return
                "#version 140\n"
                "uniform float Opacity;\n"
                "out vec4 FragColor;\n"
                "void main() {\n"
                "  FragColor = vec4(1, 1, 1, Opacity);\n"
                "}\n";
    }

    // Root of scene
    RapidGL::SceneNode sceneNode;

    // Program
    RapidGL::ProgramNode programNode;

    // Vertex shader
    RapidGL::ShaderNode vertexShaderNode;

    // Fragment shader
    RapidGL::ShaderNode fragmentShaderNode;

    // Use of program
    RapidGL::UseNode useNode;

    // Uniform
    RapidGL::FloatUniformNode uniformNode;

    /**
     * Constructs the test.
     */
    FloatUniformNodeTest() :
            programNode("foo"),
            vertexShaderNode(GL_VERTEX_SHADER, getVertexShaderSource()),
            fragmentShaderNode(GL_FRAGMENT_SHADER, getFragmentShaderSource()),
            useNode("foo"),
            uniformNode("Opacity") {
        sceneNode.addChild(&programNode);
        programNode.addChild(&vertexShaderNode);
        programNode.addChild(&fragmentShaderNode);
        sceneNode.addChild(&useNode);
        useNode.addChild(&uniformNode);
    }

    /**
     * Ensures `FloatUniformNode::FloatUniformNode(const string&)` works correctly.
     */
    void testFloatUniformNodeString() {
        const RapidGL::FloatUniformNode uniformNode("foo");
        CPPUNIT_ASSERT_EQUAL(0.0f, uniformNode.getValue());
    }

    /*
     * Ensures `FloatUniformNode::FloatUniformNode(const string&, GLfloat)` works correctly.
     */
    void testFloatUniformNodeStringFloat() {
        const GLfloat value = 1.0f;
        const RapidGL::FloatUniformNode uniformNode("foo", value);
        CPPUNIT_ASSERT_EQUAL(value, uniformNode.getValue());
    }

    /**
     * Ensures `FloatUniformNode::getType` returns `GL_FLOAT`.
     */
    void testGetType() {
        CPPUNIT_ASSERT_EQUAL((GLenum) GL_FLOAT, uniformNode.getType());
    }

    /**
     * Ensures `FloatUniformNode::visit` works correctly.
     */
    void testVisit() {

        // Set value
        uniformNode.setValue(0.5f);

        // Visit the nodes
        RapidGL::State state;
        RapidGL::Visitor visitor(&state);
        visitor.visit(&sceneNode);

        // Check value
        const Gloop::Program program = programNode.getProgram();
        const GLint location = program.uniformLocation(uniformNode.getName());
        GLfloat actual;
        glGetUniformfv(program.id(), location, &actual);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.5f, actual, TOLERANCE);
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
        throw std::runtime_error("Could not open GLFW window!");
    }

    // Run test
    try {
        FloatUniformNodeTest test;
        test.testFloatUniformNodeString();
        test.testFloatUniformNodeStringFloat();
        test.testGetType();
        test.testVisit();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        throw;
    }

    // Exit
    glfwTerminate();
    return 0;
}
