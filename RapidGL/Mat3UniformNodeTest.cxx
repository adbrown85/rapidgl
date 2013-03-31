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
#include <m3d/Mat3.h>
#include <m3d/Vec3.h>
#include <stdexcept>
#include <string>
#include "RapidGL/Mat3UniformNode.h"
#include "RapidGL/ProgramNode.h"
#include "RapidGL/SceneNode.h"
#include "RapidGL/ShaderNode.h"
#include "RapidGL/State.h"
#include "RapidGL/Visitor.h"
#include "RapidGL/UseNode.h"


/**
 * Unit test for Mat3UniformNode.
 */
class Mat3UniformNodeTest {
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
                "uniform mat3 MVPMatrix;\n"
                "in vec4 MCVertex;\n"
                "void main() {\n"
                "  gl_Position = mat4(MVPMatrix) * MCVertex;\n"
                "}\n";
    }

    /**
     * Returns the source code for the fragment shader.
     */
    static std::string getFragmentShaderSource() {
        return
                "#version 140\n"
                "out vec4 FragColor;\n"
                "void main() {\n"
                "  FragColor = vec4(1);\n"
                "}\n";
    }

    // Root of scene
    RapidGL::SceneNode sceneNode;

    // Shader program
    RapidGL::ProgramNode programNode;

    // Vertex shader
    RapidGL::ShaderNode vertexShaderNode;

    // Fragment shader
    RapidGL::ShaderNode fragmentShaderNode;

    // Use of program
    RapidGL::UseNode useNode;

    // Uniform
    RapidGL::Mat3UniformNode uniformNode;

    /**
     * Constructs the test.
     */
    Mat3UniformNodeTest() :
            programNode("foo"),
            vertexShaderNode(GL_VERTEX_SHADER, getVertexShaderSource()),
            fragmentShaderNode(GL_FRAGMENT_SHADER, getFragmentShaderSource()),
            useNode("foo"),
            uniformNode("MVPMatrix") {
        sceneNode.addChild(&programNode);
        programNode.addChild(&vertexShaderNode);
        programNode.addChild(&fragmentShaderNode);
        sceneNode.addChild(&useNode);
        useNode.addChild(&uniformNode);
    }

    /**
     * Ensures `Mat3UniformNode::getType` returns `GL_FLOAT_MAT3`.
     */
    void testGetType() {
        CPPUNIT_ASSERT_EQUAL((GLenum) GL_FLOAT_MAT3, uniformNode.getType());
    }

    /**
     * Ensures `Mat3UniformNode::Mat3UniformNode(const string&, const Mat3&)` works correctly.
     */
    void testMat3UniformNodeStringMat3() {

        // Make initial value
        M3d::Mat3 value;
        value[0] = M3d::Vec3(1, 2, 3);
        value[1] = M3d::Vec3(4, 5, 6);
        value[2] = M3d::Vec3(7, 8, 9);

        // Construct node and check value
        const RapidGL::Mat3UniformNode uniformNode("foo", value);
        CPPUNIT_ASSERT_EQUAL(value, uniformNode.getValue());
    }

    /**
     * Ensures `Mat3UniformNode::setValue` fires an event.
     */
    void testSetValue() {

        // Create node and register listener
        RapidGL::Mat3UniformNode mat3UniformNode("foo");
        FakeNodeListener fakeNodeListener;
        mat3UniformNode.addNodeListener(&fakeNodeListener);

        // Change value and check listener was notified
        CPPUNIT_ASSERT_EQUAL((RapidGL::Node*) NULL, fakeNodeListener.node);
        mat3UniformNode.setValue(M3d::Mat3(0.5));
        CPPUNIT_ASSERT_EQUAL((RapidGL::Node*) &mat3UniformNode, fakeNodeListener.node);
    }

    /**
     * Ensures `Mat3UniformNode::visit` works correctly.
     */
    void testVisit() {

        // Set value
        M3d::Mat3 value;
        value[0] = M3d::Vec3(1, 2, 3);
        value[1] = M3d::Vec3(4, 5, 6);
        value[2] = M3d::Vec3(7, 8, 9);
        uniformNode.setValue(value);

        // Visit the nodes
        RapidGL::State state;
        RapidGL::Visitor visitor(&state);
        visitor.visit(&sceneNode);

        // Check value
        Gloop::Program program = programNode.getProgram();
        const GLint location = program.uniformLocation(uniformNode.getName());
        GLfloat expected[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        GLfloat actual[9];
        glGetUniformfv(program.id(), location, actual);
        for (int i = 0; i < 9; ++i) {
            CPPUNIT_ASSERT_DOUBLES_EQUAL(expected[i], actual[i], TOLERANCE);
        }
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
        Mat3UniformNodeTest test;
        test.testGetType();
        test.testMat3UniformNodeStringMat3();
        test.testSetValue();
        test.testVisit();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        throw;
    }

    // Exit
    glfwTerminate();
    return 0;
}
