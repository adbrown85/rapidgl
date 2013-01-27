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
#include <stdexcept>
#include <string>
#include <cppunit/extensions/HelperMacros.h>
#include <glycerin/Projection.hxx>
#include <glycerin/Ray.hxx>
#include <m3d/Mat4.h>
#include <m3d/Math.h>
#include <m3d/Quat.h>
#include <m3d/Vec3.h>
#include <m3d/Vec4.h>
#include <GL/glfw.h>
#include "RapidGL/AttributeNode.h"
#include "RapidGL/CubeNode.h"
#include "RapidGL/Intersectable.h"
#include "RapidGL/Mat4UniformNode.h"
#include "RapidGL/ProgramNode.h"
#include "RapidGL/SceneNode.h"
#include "RapidGL/ShaderNode.h"
#include "RapidGL/State.h"
#include "RapidGL/UseNode.h"
#include "RapidGL/Visitor.h"


/**
 * Unit test for `CubeNode`.
 */
class CubeNodeTest {
public:

    // Number of seconds to sleep after rendering
    static const double SLEEP_TIME_IN_SECONDS = 2.0;

    // Threshold for floating-point comparisons
    static const double TOLERANCE = 1e-6;

    /**
     * Returns the source code for the vertex shader.
     */
    static std::string getVertexShaderSource() {
        return
                "#version 140\n"
                "uniform mat4 MVPMatrix = mat4(1);\n"
                "in vec4 MCVertex;\n"
                "in vec4 TexCoord0;\n"
                "out vec4 Coord0;\n"
                "void main() {\n"
                "  gl_Position = MVPMatrix * MCVertex;\n"
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

    /**
     * Returns the projection matrix used to render.
     */
    static M3d::Mat4 getProjectionMatrix() {
        return Glycerin::Projection::perspective(30, 1, 1, 100);
    }

    /**
     * Returns the view matrix used to render.
     */
    static M3d::Mat4 getViewMatrix() {

        // Make translation
        M3d::Mat4 translationMatrix(1);
        translationMatrix[3] = M3d::Vec4(0, 0, -4, 1);

        // Make axes
        const M3d::Vec3 xAxis(1, 0, 0);
        const M3d::Vec3 yAxis(0, 1, 0);

        // Make angles
        const double fifteenDegreesInRadians = M3d::toRadians(15);
        const double thirtyDegreesInRadians = M3d::toRadians(30);

        // Make rotation
        const M3d::Quat xRotation = M3d::Quat::fromAxisAngle(xAxis, fifteenDegreesInRadians);
        const M3d::Quat yRotation = M3d::Quat::fromAxisAngle(yAxis, -thirtyDegreesInRadians);
        const M3d::Quat rotation = yRotation * xRotation;
        const M3d::Mat4 rotationMatrix = rotation.toMat4();

        // Concatenate
        return translationMatrix * rotationMatrix;
    }

    // Root of scene
    RapidGL::SceneNode sceneNode;

    // Shader program
    RapidGL::ProgramNode programNode;

    // Vertex shader
    RapidGL::ShaderNode vertexShaderNode;

    // Fragment shader
    RapidGL::ShaderNode fragmentShaderNode;

    // Description of attribute for vertices
    RapidGL::AttributeNode vertexAttributeNode;

    // Description of attribute for texture coordinates
    RapidGL::AttributeNode coordinateAttributeNode;

    // Usage of program
    RapidGL::UseNode useNode;

    // Uniform for model-view-projection matrix
    RapidGL::Mat4UniformNode uniformNode;

    // Cube node
    RapidGL::CubeNode cubeNode;

    /**
     * Constructs the test.
     */
    CubeNodeTest() :
            programNode("foo"),
            vertexShaderNode(GL_VERTEX_SHADER, getVertexShaderSource()),
            fragmentShaderNode(GL_FRAGMENT_SHADER, getFragmentShaderSource()),
            vertexAttributeNode("MCVertex", RapidGL::AttributeNode::POINT),
            coordinateAttributeNode("TexCoord0", RapidGL::AttributeNode::COORDINATE),
            useNode("foo"),
            uniformNode("MVPMatrix", RapidGL::Mat4UniformNode::MODEL_VIEW_PROJECTION) {
        sceneNode.addChild(&programNode);
        programNode.addChild(&vertexShaderNode);
        programNode.addChild(&fragmentShaderNode);
        programNode.addChild(&vertexAttributeNode);
        programNode.addChild(&coordinateAttributeNode);
        sceneNode.addChild(&useNode);
        useNode.addChild(&uniformNode);
        useNode.addChild(&cubeNode);
    }

    /**
     * Ensures `CubeNode::intersect` works correctly.
     */
    void testIntersect() {

        // Make ray
        const M3d::Vec4 origin(0, 0, 10, 1);
        const M3d::Vec4 direction(0, 0, -1, 0);
        const Glycerin::Ray ray(origin, direction);

        // Make cube node
        const RapidGL::CubeNode node;
        const RapidGL::Intersectable* intersectable = dynamic_cast<const RapidGL::Intersectable*>(&node);
        CPPUNIT_ASSERT(intersectable != NULL);
        const double t = intersectable->intersect(ray);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(9.5, t, TOLERANCE);
    }

    /**
     * Ensures `CubeNode::visit` works correctly.
     */
    void testVisit() {

        // Turn on back face culling
        glCullFace(GL_BACK);
        glEnable(GL_CULL_FACE);

        // Set up state
        RapidGL::State state;
        state.setViewMatrix(getViewMatrix());
        state.setProjectionMatrix(getProjectionMatrix());

        // Visit nodes
        RapidGL::Visitor visitor(&state);
        visitor.visit(&sceneNode);

        // Flush
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
        CubeNodeTest test;
        test.testIntersect();
        test.testVisit();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        throw;
    }

    // Exit
    glfwTerminate();
    return 0;
}
