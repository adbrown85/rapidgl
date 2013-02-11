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
#include "RapidGL/ProgramNode.h"
#include "RapidGL/SceneNode.h"
#include "RapidGL/State.h"


/**
 * Unit test for Program.
 */
class ProgramNodeTest {
public:

    /**
     * Fake node used for testing.
     */
    class FakeNode : public RapidGL::Node {
    public:
        FakeNode() { }
        virtual void visit(RapidGL::State& state) { }
    };

    /**
     * Ensures `findProgramNode` works when the program is in the tree.
     */
    void testFindProgramNodeWhenProgramIsInTree() {

        // Create nodes
        RapidGL::SceneNode sceneNode;
        FakeNode fakeNode;
        RapidGL::ProgramNode programNode("foo");

        // Connect nodes
        sceneNode.addChild(&fakeNode);
        fakeNode.addChild(&programNode);

        // Check results
        const RapidGL::ProgramNode* actual = findProgramNode(&sceneNode, programNode.getProgram());
        CPPUNIT_ASSERT_EQUAL((const RapidGL::ProgramNode*) &programNode, actual);
    }

    /**
     * Ensures `findProgramNode` works when the program is not in the tree.
     */
    void testFindProgramNodeWhenProgramIsNotInTree() {

        // Create nodes
        RapidGL::SceneNode sceneNode;
        FakeNode fakeNode;
        RapidGL::ProgramNode programNode("foo");

        // Connect nodes
        sceneNode.addChild(&fakeNode);
        fakeNode.addChild(&programNode);

        // Check results
        const Gloop::Program program = Gloop::Program::create();
        const RapidGL::ProgramNode* actual = findProgramNode(&sceneNode, program);
        CPPUNIT_ASSERT_EQUAL((const RapidGL::ProgramNode*) NULL, actual);
    }

    /**
     * Ensures `ProgramNode::preVisit` works when attribute is in program and it's been given an explicit location.
     */
    void testPreVisitWhenAttributeIsInProgramAndLocationIsSpecified() {

        // Create vertex shader
        RapidGL::ShaderNode vertexShaderNode(
                GL_VERTEX_SHADER,
                "#version 140\n"
                "in vec4 MCVertex;\n"
                "void main() {\n"
                "    gl_Position = MCVertex;\n"
                "}\n");

        // Create fragment shader
        RapidGL::ShaderNode fragmentShaderNode(
                GL_FRAGMENT_SHADER,
                "#version 140\n"
                "out vec4 FragColor;\n"
                "void main() {\n"
                "    FragColor = vec4(1);\n"
                "}\n");

        // Create attribute node
        RapidGL::AttributeNode attributeNode("MCVertex", RapidGL::AttributeNode::POINT, 7);

        // Create program node and attach shader and attribute nodes
        RapidGL::ProgramNode programNode("foo");
        programNode.addChild(&vertexShaderNode);
        programNode.addChild(&fragmentShaderNode);
        programNode.addChild(&attributeNode);

        // Traverse nodes
        RapidGL::State state;
        programNode.preVisit(state);

        // Check
        const Gloop::Program program = programNode.getProgram();
        CPPUNIT_ASSERT(program.linked());
        CPPUNIT_ASSERT_EQUAL(7, program.attribLocation("MCVertex"));
        CPPUNIT_ASSERT_EQUAL(7, attributeNode.getLocation());
    }

    /**
     * Ensures `ProgramNode::preVisit` works when attribute is in program and it has not been given a location.
     */
    void testPreVisitWhenAttributeIsInProgramAndLocationIsUnspecified() {

        // Create vertex shader
        RapidGL::ShaderNode vertexShaderNode(
                GL_VERTEX_SHADER,
                "#version 140\n"
                "in vec4 MCVertex;\n"
                "void main() {\n"
                "    gl_Position = MCVertex;\n"
                "}\n");

        // Create fragment shader
        RapidGL::ShaderNode fragmentShaderNode(
                GL_FRAGMENT_SHADER,
                "#version 140\n"
                "out vec4 FragColor;\n"
                "void main() {\n"
                "    FragColor = vec4(1);\n"
                "}\n");

        // Create attribute node
        RapidGL::AttributeNode attributeNode("MCVertex", RapidGL::AttributeNode::POINT, -1);

        // Create program node and attach shader and attribute nodes
        RapidGL::ProgramNode programNode("foo");
        programNode.addChild(&vertexShaderNode);
        programNode.addChild(&fragmentShaderNode);
        programNode.addChild(&attributeNode);

        // Traverse nodes
        RapidGL::State state;
        programNode.preVisit(state);

        // Check
        const Gloop::Program program = programNode.getProgram();
        CPPUNIT_ASSERT(program.linked());
        CPPUNIT_ASSERT(program.attribLocation("MCVertex") >= 0);
        CPPUNIT_ASSERT(attributeNode.getLocation() >= 0);
    }

    /**
     * Ensures `ProgramNode::preVisit` throws when attribute is not in program and location is specified.
     */
    void testPreVisitWhenAttributeIsNotInProgramAndLocationIsSpecified() {

        // Create vertex shader
        RapidGL::ShaderNode vertexShaderNode(
                GL_VERTEX_SHADER,
                "#version 140\n"
                "in vec4 MCVertex;\n"
                "void main() {\n"
                "    gl_Position = MCVertex;\n"
                "}\n");

        // Create fragment shader
        RapidGL::ShaderNode fragmentShaderNode(
                GL_FRAGMENT_SHADER,
                "#version 140\n"
                "out vec4 FragColor;\n"
                "void main() {\n"
                "    FragColor = vec4(1);\n"
                "}\n");

        // Create attribute node
        RapidGL::AttributeNode attributeNode("TexCoord0", RapidGL::AttributeNode::COORDINATE, 4);

        // Create program node and attach shader and attribute nodes
        RapidGL::ProgramNode programNode("foo");
        programNode.addChild(&vertexShaderNode);
        programNode.addChild(&fragmentShaderNode);
        programNode.addChild(&attributeNode);

        // Traverse nodes
        RapidGL::State state;
        CPPUNIT_ASSERT_THROW(programNode.preVisit(state), std::runtime_error);
    }

    /**
     * Ensures `ProgramNode::preVisit` throws when attribute is not in program and location is unspecified.
     */
    void testPreVisitWhenAttributeIsNotInProgramAndLocationIsUnspecified() {

        // Create vertex shader
        RapidGL::ShaderNode vertexShaderNode(
                GL_VERTEX_SHADER,
                "#version 140\n"
                "in vec4 MCVertex;\n"
                "void main() {\n"
                "    gl_Position = MCVertex;\n"
                "}\n");

        // Create fragment shader
        RapidGL::ShaderNode fragmentShaderNode(
                GL_FRAGMENT_SHADER,
                "#version 140\n"
                "out vec4 FragColor;\n"
                "void main() {\n"
                "    FragColor = vec4(1);\n"
                "}\n");

        // Create attribute node
        RapidGL::AttributeNode attributeNode("TexCoord0", RapidGL::AttributeNode::COORDINATE, -1);

        // Create program node and attach shader and attribute nodes
        RapidGL::ProgramNode programNode("foo");
        programNode.addChild(&vertexShaderNode);
        programNode.addChild(&fragmentShaderNode);
        programNode.addChild(&attributeNode);

        // Traverse nodes
        RapidGL::State state;
        CPPUNIT_ASSERT_THROW(programNode.preVisit(state), std::runtime_error);
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
    ProgramNodeTest test;
    try {
        test.testFindProgramNodeWhenProgramIsInTree();
        test.testFindProgramNodeWhenProgramIsNotInTree();
        test.testPreVisitWhenAttributeIsInProgramAndLocationIsSpecified();
        test.testPreVisitWhenAttributeIsInProgramAndLocationIsUnspecified();
        test.testPreVisitWhenAttributeIsNotInProgramAndLocationIsSpecified();
        test.testPreVisitWhenAttributeIsNotInProgramAndLocationIsUnspecified();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        throw;
    }

    // Exit
    glfwTerminate();
    return 0;
}
