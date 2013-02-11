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
#include <glycerin/Ray.hxx>
#include <iostream>
#include <m3d/Vec4.h>
#include "RapidGL/AttributeNode.h"
#include "RapidGL/GroupNode.h"
#include "RapidGL/InstanceNode.h"
#include "RapidGL/Intersectable.h"
#include "RapidGL/ProgramNode.h"
#include "RapidGL/SceneNode.h"
#include "RapidGL/ShaderNode.h"
#include "RapidGL/SquareNode.h"
#include "RapidGL/State.h"
#include "RapidGL/UseNode.h"
#include "RapidGL/Visitor.h"


/**
 * Unit test for SquareNode.
 */
class SquareNodeTest {
public:

    // Number of seconds to sleep after rendering
    static const double SLEEP_TIME_IN_SECONDS = 1.0;

    // Threshold for floating-point comparisons
    static const double TOLERANCE = 1e-6;

    /**
     * Returns the source code for the first vertex shader.
     */
    static std::string getFirstVertexShaderSource() {
        return
                "#version 140\n"
                "in vec4 MCVertex;\n"
                "in vec4 TexCoord0;\n"
                "out vec4 Coord0;\n"
                "void main() {\n"
                "  gl_Position = MCVertex;\n"
                "  Coord0 = TexCoord0;\n"
                "}\n";
    }

    /**
     * Returns the source code for the first fragment shader.
     */
    static std::string getFirstFragmentShaderSource() {
        return
                "#version 140\n"
                "in vec4 Coord0;\n"
                "out vec4 FragColor;\n"
                "void main() {\n"
                "  FragColor = Coord0;\n"
                "}\n";
    }

    /**
     * Returns the source code for the second vertex shader.
     */
    static std::string getSecondVertexShaderSource() {
        return
                "#version 140\n"
                "in vec4 MCVertex;\n"
                "void main() {\n"
                "  gl_Position = MCVertex;\n"
                "}\n";
    }

    /**
     * Returns the source code for the second fragment shader.
     */
    static std::string getSecondFragmentShaderSource() {
        return
                "#version 140\n"
                "out vec4 FragColor;\n"
                "void main() {\n"
                "  FragColor = vec4(1);\n"
                "}\n";
    }

    // Reusable state since `SquareNode` doesn't use it
    RapidGL::State state;

    /**
     * Ensures `SquareNode::intersect` works correctly.
     */
    void testIntersect() {

        // Make ray
        const M3d::Vec4 origin(0, 0, 10, 1);
        const M3d::Vec4 direction(0, 0, -1, 0);
        const Glycerin::Ray ray(origin, direction);

        // Make square node
        const RapidGL::SquareNode node;
        const RapidGL::Intersectable *intersectable = dynamic_cast<const RapidGL::Intersectable*>(&node);
        CPPUNIT_ASSERT(intersectable != NULL);
        const double t = intersectable->intersect(ray);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(10, t, TOLERANCE);
    }

    /**
     * Ensures `SquareNode::visit` works correctly with instancing.
     */
    void testVisitWithInstancing() {

        // Create scene node
        RapidGL::SceneNode sceneNode;

        // Create first program, shader, and attribute nodes
        RapidGL::ProgramNode firstProgramNode("foo");
        RapidGL::ShaderNode firstVertexShaderNode(GL_VERTEX_SHADER, getFirstVertexShaderSource());
        RapidGL::ShaderNode firstFragmentShaderNode(GL_FRAGMENT_SHADER, getFirstFragmentShaderSource());
        RapidGL::AttributeNode firstVertexAttributeNode("MCVertex", RapidGL::AttributeNode::POINT, 1);
        RapidGL::AttributeNode firstCoordAttributeNode("TexCoord0", RapidGL::AttributeNode::COORDINATE, 2);

        // Create second program, shader, and attribute nodes
        RapidGL::ProgramNode secondProgramNode("bar");
        RapidGL::ShaderNode secondVertexShaderNode(GL_VERTEX_SHADER, getSecondVertexShaderSource());
        RapidGL::ShaderNode secondFragmentShaderNode(GL_FRAGMENT_SHADER, getSecondFragmentShaderSource());
        RapidGL::AttributeNode secondVertexAttributeNode("MCVertex", RapidGL::AttributeNode::POINT, 3);

        // Create first use node, group, and square
        RapidGL::UseNode firstUseNode("foo");
        RapidGL::GroupNode groupNode("baz");
        RapidGL::SquareNode squareNode;

        // Create second use node and instance
        RapidGL::UseNode secondUseNode("bar");
        RapidGL::InstanceNode instanceNode("baz");

        // Add first program, shader, and attribute nodes
        sceneNode.addChild(&firstProgramNode);
        firstProgramNode.addChild(&firstVertexShaderNode);
        firstProgramNode.addChild(&firstFragmentShaderNode);
        firstProgramNode.addChild(&firstVertexAttributeNode);
        firstProgramNode.addChild(&firstCoordAttributeNode);

        // Add second program, shader, and attribute nodes
        sceneNode.addChild(&secondProgramNode);
        secondProgramNode.addChild(&secondVertexShaderNode);
        secondProgramNode.addChild(&secondFragmentShaderNode);
        secondProgramNode.addChild(&secondVertexAttributeNode);

        // Add first use node, group, and square
        sceneNode.addChild(&firstUseNode);
        firstUseNode.addChild(&groupNode);
        groupNode.addChild(&squareNode);

        // Add second use node and instance
        sceneNode.addChild(&secondUseNode);
        secondUseNode.addChild(&instanceNode);

        // Visit program nodes
        RapidGL::Visitor visitor(&state);
        visitor.visit(&firstProgramNode);
        visitor.visit(&secondProgramNode);

        // Visit group
        visitor.visit(&firstUseNode);
        glfwSwapBuffers();
        glfwSleep(SLEEP_TIME_IN_SECONDS);

        // Visit instance
        visitor.visit(&secondUseNode);
        glfwSwapBuffers();
        glfwSleep(SLEEP_TIME_IN_SECONDS);
    }

    /**
     * Ensures `SquareNode::visit` throws if there is no current program.
     */
    void testVisitWithNoCurrentProgram() {
        RapidGL::SquareNode squareNode;
        glUseProgram(0);
        CPPUNIT_ASSERT_THROW(squareNode.visit(state), std::runtime_error);
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
        SquareNodeTest test;
        test.testIntersect();
        test.testVisitWithInstancing();
        test.testVisitWithNoCurrentProgram();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        throw;
    }

    // Exit
    glfwTerminate();
    return 0;
}
