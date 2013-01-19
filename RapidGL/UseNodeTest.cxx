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
#include <cppunit/extensions/HelperMacros.h>
#include <exception>
#include <iostream>
#include <stdexcept>
#include <string>
#include <GL/glfw.h>
#include "RapidGL/Node.h"
#include "RapidGL/ProgramNode.h"
#include "RapidGL/SceneNode.h"
#include "RapidGL/ShaderNode.h"
#include "RapidGL/State.h"
#include "RapidGL/UseNode.h"
#include "RapidGL/Visitor.h"


/**
 * Test for `UseNode`.
 */
class UseNodeTest {
public:

    /**
     * Fake node for testing.
     */
    class FakeNode : public RapidGL::Node {
    public:

        FakeNode(const std::string& id = "") : RapidGL::Node(id) {
            // empty
        }

        virtual void visit(RapidGL::State& state) {
            // empty
        }
    };

    /**
     * Returns the raw OpenGL identifier of the current OpenGL program.
     */
    static GLuint getCurrentProgram() {
        GLint program;
        glGetIntegerv(GL_CURRENT_PROGRAM, &program);
        return program;
    }

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
                "out vec4 FragColor;\n"
                "void main() {\n"
                "  FragColor = vec4(1);\n"
                "}\n";
    }

    // Reusable state since `UseNode` ignores it
    RapidGL::State state;

    /**
     * Ensures `UseNode::postVisit` works correctly.
     */
    void testPostVisit() {

        // Create scene node
        RapidGL::SceneNode sceneNode;

        // Add first program node
        RapidGL::ProgramNode firstProgramNode("first");
        sceneNode.addChild(&firstProgramNode);
        RapidGL::ShaderNode firstVertexShaderNode(GL_VERTEX_SHADER, getVertexShaderSource());
        RapidGL::ShaderNode firstFragmentShaderNode(GL_FRAGMENT_SHADER, getFragmentShaderSource());
        firstProgramNode.addChild(&firstVertexShaderNode);
        firstProgramNode.addChild(&firstFragmentShaderNode);

        // Add first program node
        RapidGL::ProgramNode secondProgramNode("second");
        sceneNode.addChild(&secondProgramNode);
        RapidGL::ShaderNode secondVertexShaderNode(GL_VERTEX_SHADER, getVertexShaderSource());
        RapidGL::ShaderNode secondFragmentShaderNode(GL_FRAGMENT_SHADER, getFragmentShaderSource());
        secondProgramNode.addChild(&secondVertexShaderNode);
        secondProgramNode.addChild(&secondFragmentShaderNode);

        // Add use nodes
        RapidGL::UseNode firstUseNode("first");
        sceneNode.addChild(&firstUseNode);
        RapidGL::UseNode secondUseNode("second");
        firstUseNode.addChild(&secondUseNode);

        // Visit program nodes
        RapidGL::Visitor visitor(&state);
        visitor.visit(&firstProgramNode);
        visitor.visit(&secondProgramNode);

        // Store program IDs
        const GLuint firstProgramId = firstProgramNode.getProgram().id();
        const GLuint secondProgramId = secondProgramNode.getProgram().id();

        // Start visiting first use node
        firstUseNode.preVisit(state);
        firstUseNode.visit(state);
        CPPUNIT_ASSERT_EQUAL(firstProgramId, getCurrentProgram());

        // Visit second use node
        secondUseNode.preVisit(state);
        secondUseNode.visit(state);
        CPPUNIT_ASSERT_EQUAL(secondProgramId, getCurrentProgram());
        secondUseNode.postVisit(state);
        CPPUNIT_ASSERT_EQUAL(firstProgramId, getCurrentProgram());

        // Finish visiting first use node
        firstUseNode.postVisit(state);
        CPPUNIT_ASSERT_EQUAL((GLuint) 0, getCurrentProgram());
    }

    /**
     * Ensures `UseNode::preVisit` throws if the node is the root of the scene.
     */
    void testPreVisitWhenNodeIsRoot() {
        RapidGL::UseNode useNode("foo");
        CPPUNIT_ASSERT_THROW(useNode.preVisit(state), std::runtime_error);
    }

    /**
     * Ensures `UseNode::preVisit` throws if the specified program node is not in the scene.
     */
    void testPreVisitWhenProgramNodeIdIsNotInScene() {
        RapidGL::SceneNode sceneNode;
        RapidGL::UseNode useNode("foo");
        sceneNode.addChild(&useNode);
        CPPUNIT_ASSERT_THROW(useNode.preVisit(state), std::runtime_error);
    }

    /**
     * Ensures `UseNode::preVisit` throws if the specified program node is not actually a program node.
     */
    void testPreVisitWhenProgramNodeIdIsNotProgram() {
        RapidGL::SceneNode sceneNode;
        FakeNode fakeNode("foo");
        RapidGL::UseNode useNode("foo");
        sceneNode.addChild(&fakeNode);
        sceneNode.addChild(&useNode);
        CPPUNIT_ASSERT_THROW(useNode.preVisit(state), std::runtime_error);
    }

    /**
     * Ensures `UseNode::preVisit` works if the specified program node is a program node.
     */
    void testPreVisitWhenProgramNodeIdIsProgram() {
        RapidGL::SceneNode sceneNode;
        RapidGL::ProgramNode programNode("foo");
        RapidGL::UseNode useNode("foo");
        sceneNode.addChild(&programNode);
        sceneNode.addChild(&useNode);
        useNode.preVisit(state);
    }

    /**
     * Ensures `UseNode::visit` works correctly.
     */
    void testVisit() {

        // Create scene node
        RapidGL::SceneNode sceneNode;

        // Add program node
        RapidGL::ProgramNode programNode("foo");
        sceneNode.addChild(&programNode);
        RapidGL::ShaderNode vertexShaderNode(GL_VERTEX_SHADER, getVertexShaderSource());
        RapidGL::ShaderNode fragmentShaderNode(GL_FRAGMENT_SHADER, getFragmentShaderSource());
        programNode.addChild(&vertexShaderNode);
        programNode.addChild(&fragmentShaderNode);

        // Add use node
        RapidGL::UseNode useNode("foo");
        sceneNode.addChild(&useNode);

        // Visit program node
        RapidGL::Visitor visitor(&state);
        visitor.visit(&programNode);

        // Visit use node
        useNode.preVisit(state);
        useNode.visit(state);
        CPPUNIT_ASSERT_EQUAL(programNode.getProgram().id(), getCurrentProgram());
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

    // Run test
    try {
        UseNodeTest test;
        test.testPostVisit();
        test.testPreVisitWhenNodeIsRoot();
        test.testPreVisitWhenProgramNodeIdIsNotInScene();
        test.testPreVisitWhenProgramNodeIdIsNotProgram();
        test.testPreVisitWhenProgramNodeIdIsProgram();
        test.testVisit();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        throw;
    }

    // Exit
    glfwTerminate();
    return 0;
}
