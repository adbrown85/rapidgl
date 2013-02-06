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
     * Returns the source code for the vertex shader.
     */
    static std::string getVertexShaderSource() {
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
     * Returns the source code for the fragment shader.
     */
    static std::string getFragmentShaderSource() {
        return
                "#version 140\n"
                "in vec4 Coord0;\n"
                "out vec4 FragColor;\n"
                "void main() {\n"
                "  FragColor = Coord0;\n"
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
     * Ensures `SquareNode::preVisit` throws if could not find program node.
     */
    void testPreVisitWithNoProgramNode() {
        RapidGL::SquareNode squareNode;
        CPPUNIT_ASSERT_THROW(squareNode.preVisit(state), std::runtime_error);
    }

    /**
     * Ensures `SquareNode::visit` works correctly.
     */
    void testVisit() {

        // Create nodes
        RapidGL::SceneNode sceneNode;
        RapidGL::ProgramNode programNode("foo");
        RapidGL::ShaderNode vertexShaderNode(GL_VERTEX_SHADER, getVertexShaderSource());
        RapidGL::ShaderNode fragmentShaderNode(GL_FRAGMENT_SHADER, getFragmentShaderSource());
        RapidGL::AttributeNode vertexAttributeNode("MCVertex", RapidGL::AttributeNode::POINT, -1);
        RapidGL::AttributeNode coordAttributeNode("TexCoord0", RapidGL::AttributeNode::COORDINATE, -1);
        RapidGL::UseNode useNode("foo");
        RapidGL::SquareNode squareNode;

        // Connect nodes
        sceneNode.addChild(&programNode);
        programNode.addChild(&vertexShaderNode);
        programNode.addChild(&fragmentShaderNode);
        programNode.addChild(&vertexAttributeNode);
        programNode.addChild(&coordAttributeNode);
        sceneNode.addChild(&useNode);
        useNode.addChild(&squareNode);

        // Visit
        RapidGL::Visitor visitor(&state);
        visitor.visit(&sceneNode);
        glfwSwapBuffers();
        glfwSleep(SLEEP_TIME_IN_SECONDS);
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
        test.testPreVisitWithNoProgramNode();
        test.testVisit();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        throw;
    }

    // Exit
    glfwTerminate();
    return 0;
}
