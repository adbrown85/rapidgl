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
#include <gloop/Program.hxx>
#include <iostream>
#include "RapidGL/ProgramNode.h"
#include "RapidGL/SceneNode.h"
#include "RapidGL/ShaderNode.h"
#include "RapidGL/State.h"
#include "RapidGL/UseNode.h"
#include "RapidGL/Vec4UniformNode.h"
#include "RapidGL/Visitor.h"


/**
 * Unit test for Vec4UniformNode.
 */
class Vec4UniformNodeTest {
public:

    // Threshold for floating-point comparisons
    static const double TOLERANCE = 1e-9;

    /**
     * Fake `NodeListener` that stores the node that changed.
     */
    class FakeNodeListener : public RapidGL::NodeListener {
    public:
    // Attributes
        RapidGL::Node* node;
    // Methods
        FakeNodeListener() : node(NULL) { }
        virtual void nodeChanged(RapidGL::Node* node) {
            this->node = node;
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

    // Root of scene
    RapidGL::SceneNode sceneNode;

    // Shader program
    RapidGL::ProgramNode programNode;

    // Vertex shader in program
    RapidGL::ShaderNode vertexShaderNode;

    // Fragment shader in program
    RapidGL::ShaderNode fragmentShaderNode;

    // Usage of program
    RapidGL::UseNode useNode;

    // Uniform
    RapidGL::Vec4UniformNode uniformNode;

    /**
     * Constructs the test fixture.
     */
    Vec4UniformNodeTest() :
            programNode("foo"),
            vertexShaderNode(GL_VERTEX_SHADER, getVertexShaderSource()),
            fragmentShaderNode(GL_FRAGMENT_SHADER, getFragmentShaderSource()),
            useNode("foo"),
            uniformNode("Color") {
        sceneNode.addChild(&programNode);
        programNode.addChild(&vertexShaderNode);
        programNode.addChild(&fragmentShaderNode);
        sceneNode.addChild(&useNode);
        useNode.addChild(&uniformNode);
    }

    /**
     * Ensures `Vec4UniformNode::getType` returns `GL_FLOAT_VEC4`.
     */
    void testGetType() {
        CPPUNIT_ASSERT_EQUAL((GLenum) GL_FLOAT_VEC4, uniformNode.getType());
    }

    /**
     * Ensures `Vec4UniformNode::Vec4UniformNode(const string&, const Vec4&)` works correctly.
     */
    void testVec4UniformNodeStringVec4() {
        const M3d::Vec4 value(1, 2, 3, 4);
        const RapidGL::Vec4UniformNode uniformNode("foo", value);
        CPPUNIT_ASSERT_EQUAL(value, uniformNode.getValue());
    }

    /**
     * Ensures `Vec4UniformNode::setValue` fires an event.
     */
    void testSetValue() {

        // Make node and register listener
        RapidGL::Vec4UniformNode vec4UniformNode("foo");
        FakeNodeListener fakeNodeListener;
        vec4UniformNode.addNodeListener(&fakeNodeListener);

        // Change value and check listener was notified
        CPPUNIT_ASSERT_EQUAL((RapidGL::Node*) NULL, fakeNodeListener.node);
        vec4UniformNode.setValue(M3d::Vec4(1, 2, 3, 4));
        CPPUNIT_ASSERT_EQUAL((RapidGL::Node*) &vec4UniformNode, fakeNodeListener.node);
    }

    /**
     * Ensures `Vec4UniformNode::visit` works correctly.
     */
    void testVisit() {

        // Set the value
        uniformNode.setValue(M3d::Vec4(1.0f, 2.0f, 3.0f, 4.0f));

        // Visit the nodes
        RapidGL::State state;
        RapidGL::Visitor visitor(&state);
        visitor.visit(&sceneNode);

        // Check value of uniform in program
        Gloop::Program program = programNode.getProgram();
        const GLint location = program.uniformLocation(uniformNode.getName());
        GLfloat arr[4];
        glGetUniformfv(program.id(), location, arr);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0f, arr[0], TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(2.0f, arr[1], TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(3.0f, arr[2], TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(4.0f, arr[3], TOLERANCE);
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
        Vec4UniformNodeTest test;
        test.testGetType();
        test.testSetValue();
        test.testVec4UniformNodeStringVec4();
        test.testVisit();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        throw;
    }

    // Exit
    glfwTerminate();
    return 0;
}
