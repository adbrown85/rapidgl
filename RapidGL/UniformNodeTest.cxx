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
#include <iostream>
#include <stdexcept>
#include "RapidGL/ProgramNode.h"
#include "RapidGL/ShaderNode.h"
#include "RapidGL/State.h"
#include "RapidGL/UniformNode.h"
#include "RapidGL/Visitor.h"


/**
 * Unit test for UniformNode.
 */
class UniformNodeTest {
public:

    /**
     * Mock node for testing.
     */
    class FakeNode : public RapidGL::Node {
    public:

        virtual void visit(RapidGL::State& state) {
            // empty
        }
    };

    /**
     * Mock uniform node for testing.
     */
    class FakeUniformNode : public RapidGL::UniformNode {
    public:

        FakeUniformNode(const std::string& name, GLenum type) : RapidGL::UniformNode(name, type) {
            // empty
        }

        virtual void visit(RapidGL::State& state) {
            // empty
        }
    };

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
            "uniform vec4 Color = vec4(1);\n"
            "out vec4 FragColor;\n"
            "void main() {\n"
            "  FragColor = Color;\n"
            "}\n";
    }

    // Program uniform is in
    RapidGL::ProgramNode programNode;

    // Vertex shader for program
    RapidGL::ShaderNode vertexShaderNode;

    // Fragment shader for program
    RapidGL::ShaderNode fragmentShaderNode;

    /**
     * Constructs the test.
     */
    UniformNodeTest() :
            vertexShaderNode(GL_VERTEX_SHADER, getVertexShaderSource()),
            fragmentShaderNode(GL_FRAGMENT_SHADER, getFragmentShaderSource()) {
        programNode.addChild(&vertexShaderNode);
        programNode.addChild(&fragmentShaderNode);
    }

    /**
     * Ensures `UniformNode::preVisit` throws if name is not in the shader program.
     */
    void testPreVisitWithInvalidName() {

        // Make a uniform node and connect it to the program
        FakeUniformNode uniformNode("Foo", GL_FLOAT);
        programNode.addChild(&uniformNode);

        // Visit the nodes
        RapidGL::State state;
        RapidGL::Visitor visitor(&state);
        CPPUNIT_ASSERT_THROW(visitor.visit(&programNode), std::runtime_error);

        // Disconnect uniform node
        programNode.removeChild(&uniformNode);
    }

    /**
     * Ensures `UniformNode::preVisit` throws if type is not what's declared in the shader.
     */
    void testPreVisitWithInvalidType() {

        // Make a uniform node and connect it to the program
        FakeUniformNode uniformNode("Color", GL_FLOAT);
        programNode.addChild(&uniformNode);

        // Visit the nodes
        RapidGL::State state;
        RapidGL::Visitor visitor(&state);
        CPPUNIT_ASSERT_THROW(visitor.visit(&programNode), std::runtime_error);

        // Disconnect uniform node
        programNode.removeChild(&uniformNode);
    }

    /**
     * Ensures `UniformNode::preVisit` throws if it does not have a program node ancestor.
     */
    void testPreVisitWithNoProgramNodeAncestor() {

        // Make nodes
        FakeNode fooNode;
        FakeNode barNode;
        FakeUniformNode uniformNode("Color", GL_FLOAT_VEC4);

        // Connect nodes
        fooNode.addChild(&barNode);
        barNode.addChild(&uniformNode);

        // Visit the nodes
        RapidGL::State state;
        RapidGL::Visitor visitor(&state);
        CPPUNIT_ASSERT_THROW(visitor.visit(&fooNode), std::runtime_error);
    }

    /**
     * Ensures `UniformNode::preVisit` works correctly with a valid name and type.
     */
    void testPreVisitWithValidNameAndType() {

        // Make a uniform node and connect it to the program
        FakeUniformNode uniformNode("Color", GL_FLOAT_VEC4);
        programNode.addChild(&uniformNode);

        // Visit the nodes
        RapidGL::State state;
        RapidGL::Visitor visitor(&state);
        visitor.visit(&programNode);

        // Check location
        CPPUNIT_ASSERT(uniformNode.getLocation() != -1);

        // Disconnect uniform node
        programNode.removeChild(&uniformNode);
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
        UniformNodeTest test;
        test.testPreVisitWithInvalidName();
        test.testPreVisitWithInvalidType();
        test.testPreVisitWithNoProgramNodeAncestor();
        test.testPreVisitWithValidNameAndType();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        throw;
    }

    // Exit
    glfwTerminate();
    return 0;
}
