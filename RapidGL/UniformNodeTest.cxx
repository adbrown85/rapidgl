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
#include "RapidGL/SceneNode.h"
#include "RapidGL/ShaderNode.h"
#include "RapidGL/State.h"
#include "RapidGL/UniformNode.h"
#include "RapidGL/UseNode.h"
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

        Gloop::Program getCurrentProgram() {
            return UniformNode::getCurrentProgram();
        }

        GLint getLocationInProgram(const Gloop::Program& program) {
            return UniformNode::getLocationInProgram(program);
        }

        virtual void visit(RapidGL::State& state) {
            getLocationInProgram(getCurrentProgram());
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

    // Program uniform is in
    RapidGL::ProgramNode programNode;

    // Vertex shader for program
    RapidGL::ShaderNode vertexShaderNode;

    // Fragment shader for program
    RapidGL::ShaderNode fragmentShaderNode;

    // Usage of program
    RapidGL::UseNode useNode;

    /**
     * Constructs the test.
     */
    UniformNodeTest() :
            programNode("foo"),
            vertexShaderNode(GL_VERTEX_SHADER, getVertexShaderSource()),
            fragmentShaderNode(GL_FRAGMENT_SHADER, getFragmentShaderSource()),
            useNode("foo") {
        sceneNode.addChild(&programNode);
        programNode.addChild(&vertexShaderNode);
        programNode.addChild(&fragmentShaderNode);
        sceneNode.addChild(&useNode);
    }

    /**
     * Ensures `UniformNode::getCurrentProgram` throws if there is no current program.
     */
    void testGetCurrentProgramWithNoCurrentProgram() {
        FakeUniformNode uniformNode("Color", GL_FLOAT_VEC4);
        glUseProgram(0);
        CPPUNIT_ASSERT_THROW(uniformNode.getCurrentProgram(), std::runtime_error);
    }

    /**
     * Ensures `UniformNode::getLocationInProgram` returns `-1` if uniform is not in the shader program.
     */
    void testGetLocationInProgramWithInvalidName() {

        // Make a uniform node and connect it to the use node
        FakeUniformNode uniformNode("Foo", GL_FLOAT);
        useNode.addChild(&uniformNode);

        // Visit the nodes
        RapidGL::State state;
        RapidGL::Visitor visitor(&state);
        visitor.visit(&sceneNode);

        // Check location
        CPPUNIT_ASSERT_EQUAL(-1, uniformNode.getLocationInProgram(programNode.getProgram()));

        // Disconnect uniform node
        useNode.removeChild(&uniformNode);
    }

    /**
     * Ensures `UniformNode::getLocationInProgram` throws if type is not what's declared in the shader.
     */
    void testGetLocationInProgramWithInvalidType() {

        // Make a uniform node and connect it to the use node
        FakeUniformNode uniformNode("Color", GL_FLOAT);
        useNode.addChild(&uniformNode);

        // Visit the nodes
        RapidGL::State state;
        RapidGL::Visitor visitor(&state);
        CPPUNIT_ASSERT_THROW(visitor.visit(&sceneNode), std::runtime_error);

        // Disconnect uniform node
        useNode.removeChild(&uniformNode);
    }

    /**
     * Ensures `UniformNode::getLocationInProgram` works correctly for two different programs.
     */
    void testGetLocationInProgramWithTwoPrograms() {

        // Make a uniform node
        FakeUniformNode uniformNode("Color", GL_FLOAT_VEC4);

        // Connect the node
        useNode.addChild(&uniformNode);

        // Visit the nodes
        RapidGL::State state;
        RapidGL::Visitor visitor(&state);
        visitor.visit(&sceneNode);

        // Disconnect uniform node
        useNode.removeChild(&uniformNode);

        // Make another scene
        RapidGL::SceneNode secondSceneNode;

        // Make another program
        RapidGL::ProgramNode secondProgramNode("bar");
        RapidGL::ShaderNode secondVertexShaderNode(GL_VERTEX_SHADER, getVertexShaderSource());
        RapidGL::ShaderNode secondFragmentShaderNode(
                GL_FRAGMENT_SHADER,
                "#version 140\n"
                "out vec4 FragColor;\n"
                "void main() {\n"
                "  FragColor = vec4(1);\n"
                "}\n");
        RapidGL::UseNode secondUseNode("bar");

        // Connect nodes
        secondSceneNode.addChild(&secondProgramNode);
        secondProgramNode.addChild(&secondVertexShaderNode);
        secondProgramNode.addChild(&secondFragmentShaderNode);
        secondSceneNode.addChild(&secondUseNode);
        secondUseNode.addChild(&uniformNode);

        // Visit the nodes
        visitor.visit(&secondSceneNode);

        // Check locations
        CPPUNIT_ASSERT(uniformNode.getLocationInProgram(programNode.getProgram()) >= 0);
        CPPUNIT_ASSERT(uniformNode.getLocationInProgram(secondProgramNode.getProgram()) < 0);
    }

    /**
     * Ensures `UniformNode::getLocationInProgram` works correctly with a valid name and type.
     */
    void testGetLocationInProgramWithValidNameAndType() {

        // Make a uniform node and connect it to the use node
        FakeUniformNode uniformNode("Color", GL_FLOAT_VEC4);
        useNode.addChild(&uniformNode);

        // Visit the nodes
        RapidGL::State state;
        RapidGL::Visitor visitor(&state);
        visitor.visit(&sceneNode);

        // Check location
        CPPUNIT_ASSERT(uniformNode.getLocationInProgram(programNode.getProgram()) >= 0);

        // Disconnect uniform node
        useNode.removeChild(&uniformNode);
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
        test.testGetCurrentProgramWithNoCurrentProgram();
        test.testGetLocationInProgramWithInvalidName();
        test.testGetLocationInProgramWithInvalidType();
        test.testGetLocationInProgramWithTwoPrograms();
        test.testGetLocationInProgramWithValidNameAndType();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        throw;
    }

    // Exit
    glfwTerminate();
    return 0;
}
