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
#include <m3d/Mat4.h>
#include <m3d/Vec4.h>
#include <stdexcept>
#include <string>
#include "RapidGL/Mat4UniformNode.h"
#include "RapidGL/ProgramNode.h"
#include "RapidGL/SceneNode.h"
#include "RapidGL/ShaderNode.h"
#include "RapidGL/State.h"
#include "RapidGL/UseNode.h"
#include "RapidGL/Visitor.h"


/**
 * Unit test for Mat4UniformNode.
 */
class Mat4UniformNodeTest {
public:

    // Threshold for floating-point comparisons
    static const double TOLERANCE = 1e-9;

    /**
     * Returns the source code for the vertex shader.
     */
    static std::string getVertexShaderSource() {
        return
                "#version 140\n"
                "uniform mat4 Matrix;\n"
                "in vec4 MCVertex;\n"
                "void main() {\n"
                "  gl_Position = Matrix * MCVertex;\n"
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

    /**
     * Returns a random 4x4 matrix.
     */
    static M3d::Mat4 getRandomMatrix() {
        M3d::Mat4 mat;
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                mat[j][i] = rand() % 100;
            }
        }
        return mat;
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

    /**
     * Constructs the test.
     */
    Mat4UniformNodeTest() :
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
     * Ensures `Mat4UniformNode::getType` returns `GL_FLOAT_MAT4`.
     */
    void testGetType() {
        RapidGL::Mat4UniformNode uniformNode("foo", RapidGL::Mat4UniformNode::IDENTITY);
        CPPUNIT_ASSERT_EQUAL((GLenum) GL_FLOAT_MAT4, uniformNode.getType());
    }

    /**
     * Ensures `Mat4UniformNode::parseUsage` throws an exception if passed 'foo'.
     */
    void testParseUsageWithFoo() {
        CPPUNIT_ASSERT_THROW(RapidGL::Mat4UniformNode::parseUsage("foo"), std::invalid_argument);
    }

    /**
     * Ensures `Mat4UniformNode::parseUsage` works with 'identity'.
     */
    void testParseUsageWithIdentity() {
        RapidGL::Mat4UniformNode::Usage expected = RapidGL::Mat4UniformNode::IDENTITY;
        RapidGL::Mat4UniformNode::Usage actual = RapidGL::Mat4UniformNode::parseUsage("identity");
        CPPUNIT_ASSERT_EQUAL(expected, actual);
    }

    /**
     * Ensures `Mat4UniformNode::parseUsage` works with 'model'.
     */
    void testParseUsageWithModel() {
        RapidGL::Mat4UniformNode::Usage expected = RapidGL::Mat4UniformNode::MODEL;
        RapidGL::Mat4UniformNode::Usage actual = RapidGL::Mat4UniformNode::parseUsage("model");
        CPPUNIT_ASSERT_EQUAL(expected, actual);
    }

    /**
     * Ensures `Mat4UniformNode::parseUsage` works with 'modelview'.
     */
    void testParseUsageWithModelView() {
        RapidGL::Mat4UniformNode::Usage expected = RapidGL::Mat4UniformNode::MODEL_VIEW;
        RapidGL::Mat4UniformNode::Usage actual = RapidGL::Mat4UniformNode::parseUsage("modelview");
        CPPUNIT_ASSERT_EQUAL(expected, actual);
    }

    /**
     * Ensures `Mat4UniformNode::parseUsage` works with 'modelviewprojection'.
     */
    void testParseUsageWithModelViewProjection() {
        RapidGL::Mat4UniformNode::Usage expected = RapidGL::Mat4UniformNode::MODEL_VIEW_PROJECTION;
        RapidGL::Mat4UniformNode::Usage actual = RapidGL::Mat4UniformNode::parseUsage("modelviewprojection");
        CPPUNIT_ASSERT_EQUAL(expected, actual);
    }

    /**
     * Ensures `Mat4UniformNode::parseUsage` works with 'projection'.
     */
    void testParseUsageWithProjection() {
        RapidGL::Mat4UniformNode::Usage expected = RapidGL::Mat4UniformNode::PROJECTION;
        RapidGL::Mat4UniformNode::Usage actual = RapidGL::Mat4UniformNode::parseUsage("projection");
        CPPUNIT_ASSERT_EQUAL(expected, actual);
    }

    /**
     * Ensures `Mat4UniformNode::parseUsage` works with 'view'.
     */
    void testParseUsageWithView() {
        RapidGL::Mat4UniformNode::Usage expected = RapidGL::Mat4UniformNode::VIEW;
        RapidGL::Mat4UniformNode::Usage actual = RapidGL::Mat4UniformNode::parseUsage("view");
        CPPUNIT_ASSERT_EQUAL(expected, actual);
    }

    /**
     * Ensures `Mat4UniformNode::parseUsage` works with 'viewprojection'.
     */
    void testParseUsageWithViewProjection() {
        RapidGL::Mat4UniformNode::Usage expected = RapidGL::Mat4UniformNode::VIEW_PROJECTION;
        RapidGL::Mat4UniformNode::Usage actual = RapidGL::Mat4UniformNode::parseUsage("viewprojection");
        CPPUNIT_ASSERT_EQUAL(expected, actual);
    }

    /**
     * Ensures `Mat4UniformNode::visit` works when usage is `IDENTITY`.
     */
    void testVisitWithIdentityUsage() {

        // Add uniform node
        RapidGL::Mat4UniformNode uniformNode("Matrix", RapidGL::Mat4UniformNode::IDENTITY);
        useNode.addChild(&uniformNode);

        // Visit the nodes
        RapidGL::State state;
        RapidGL::Visitor visitor(&state);
        visitor.visit(&sceneNode);

        // Define expected value
        M3d::Mat4 mat(1);
        GLfloat expected[16];
        mat.toArrayInColumnMajor(expected);

        // Check value
        GLfloat actual[16];
        const Gloop::Program program = programNode.getProgram();
        const GLint location = program.uniformLocation(uniformNode.getName());
        glGetUniformfv(program.id(), location, actual);
        for (int i = 0; i < 16; ++i) {
            CPPUNIT_ASSERT_DOUBLES_EQUAL(expected[i], actual[i], TOLERANCE);
        }

        // Remove uniform node
        useNode.removeChild(&uniformNode);
    }

    /**
     * Ensures `Mat4UniformNode::visit` works when usage is `MODEL`.
     */
    void testVisitWithModelUsage() {

        // Add uniform node
        RapidGL::Mat4UniformNode uniformNode("Matrix", RapidGL::Mat4UniformNode::MODEL);
        useNode.addChild(&uniformNode);

        // Make matrix
        const M3d::Mat4 modelMatrix = getRandomMatrix();

        // Set up state
        RapidGL::State state;
        state.setModelMatrix(modelMatrix);

        // Visit the nodes
        RapidGL::Visitor visitor(&state);
        visitor.visit(&sceneNode);

        // Define expected value
        GLfloat expected[16];
        modelMatrix.toArrayInColumnMajor(expected);

        // Check value
        GLfloat actual[16];
        const Gloop::Program program = programNode.getProgram();
        const GLint location = program.uniformLocation(uniformNode.getName());
        glGetUniformfv(program.id(), location, actual);
        for (int i = 0; i < 16; ++i) {
            CPPUNIT_ASSERT_DOUBLES_EQUAL(expected[i], actual[i], TOLERANCE);
        }

        // Remove uniform node
        useNode.removeChild(&uniformNode);
    }

    /**
     * Ensures `Mat4UniformNode::visit` works when usage is `MODEL_VIEW`.
     */
    void testVisitWithModelViewUsage() {

        // Add uniform node
        RapidGL::Mat4UniformNode uniformNode("Matrix", RapidGL::Mat4UniformNode::MODEL_VIEW);
        useNode.addChild(&uniformNode);

        // Make matrices
        const M3d::Mat4 modelMatrix = getRandomMatrix();
        const M3d::Mat4 viewMatrix = getRandomMatrix();

        // Set up state
        RapidGL::State state;
        state.setModelMatrix(modelMatrix);
        state.setViewMatrix(viewMatrix);

        // Visit the nodes
        RapidGL::Visitor visitor(&state);
        visitor.visit(&sceneNode);

        // Define expected value
        GLfloat expected[16];
        M3d::Mat4 modelViewMatrix = viewMatrix * modelMatrix;
        modelViewMatrix.toArrayInColumnMajor(expected);

        // Check actual value
        GLfloat actual[16];
        const Gloop::Program program = programNode.getProgram();
        const GLint location = program.uniformLocation(uniformNode.getName());
        glGetUniformfv(program.id(), location, actual);
        for (int i = 0; i < 16; ++i) {
            CPPUNIT_ASSERT_DOUBLES_EQUAL(expected[i], actual[i], TOLERANCE);
        }

        // Remove uniform node
        useNode.removeChild(&uniformNode);
    }

    /**
     * Ensures `Mat4UniformNode::visit` works when usage is `MODEL_VIEW_PROJECTION`.
     */
    void testVisitWithModelViewProjectionUsage() {

        // Add uniform node
        RapidGL::Mat4UniformNode uniformNode("Matrix", RapidGL::Mat4UniformNode::MODEL_VIEW_PROJECTION);
        useNode.addChild(&uniformNode);

        // Make matrices
        const M3d::Mat4 modelMatrix = getRandomMatrix();
        const M3d::Mat4 viewMatrix = getRandomMatrix();
        const M3d::Mat4 projectionMatrix = getRandomMatrix();

        // Set up state
        RapidGL::State state;
        state.setModelMatrix(modelMatrix);
        state.setViewMatrix(viewMatrix);
        state.setProjectionMatrix(projectionMatrix);

        // Visit nodes
        RapidGL::Visitor visitor(&state);
        visitor.visit(&sceneNode);

        // Make expected value
        GLfloat expected[16];
        const M3d::Mat4 modelViewProjectionMatrix = projectionMatrix * viewMatrix * modelMatrix;
        modelViewProjectionMatrix.toArrayInColumnMajor(expected);

        // Check value
        GLfloat actual[16];
        const Gloop::Program program = programNode.getProgram();
        const GLint location = program.uniformLocation(uniformNode.getName());
        glGetUniformfv(program.id(), location, actual);
        for (int i = 0; i < 16; ++i) {
            CPPUNIT_ASSERT_DOUBLES_EQUAL(expected[i], actual[i], TOLERANCE);
        }

        // Remove uniform node
        useNode.removeChild(&uniformNode);
    }

    /**
     * Ensures `Mat4UniformNode::visit` works when usage is `PROJECTION`.
     */
    void testVisitWithProjectionUsage() {

        // Add uniform node
        RapidGL::Mat4UniformNode uniformNode("Matrix", RapidGL::Mat4UniformNode::PROJECTION);
        useNode.addChild(&uniformNode);

        // Make projection matrix
        const M3d::Mat4 projectionMatrix = getRandomMatrix();

        // Set up state
        RapidGL::State state;
        state.setProjectionMatrix(projectionMatrix);

        // Visit nodes
        RapidGL::Visitor visitor(&state);
        visitor.visit(&sceneNode);

        // Define expected value
        GLfloat expected[16];
        projectionMatrix.toArrayInColumnMajor(expected);

        // Check value
        GLfloat actual[16];
        const Gloop::Program program = programNode.getProgram();
        const GLint location = program.uniformLocation(uniformNode.getName());
        glGetUniformfv(program.id(), location, actual);
        for (int i = 0; i < 16; ++i) {
            CPPUNIT_ASSERT_DOUBLES_EQUAL(expected[i], actual[i], TOLERANCE);
        }

        // Remove uniform node
        useNode.removeChild(&uniformNode);
    }

    /**
     * Ensures `Mat4UniformNode::visit` works when usage is `VIEW`.
     */
    void testVisitWithViewUsage() {

        // Add uniform node
        RapidGL::Mat4UniformNode uniformNode("Matrix", RapidGL::Mat4UniformNode::VIEW);
        useNode.addChild(&uniformNode);

        // Make view matrix
        const M3d::Mat4 viewMatrix = getRandomMatrix();

        // Set up state
        RapidGL::State state;
        state.setViewMatrix(viewMatrix);

        // Visit nodes
        RapidGL::Visitor visitor(&state);
        visitor.visit(&sceneNode);

        // Define expected value
        GLfloat expected[16];
        viewMatrix.toArrayInColumnMajor(expected);

        // Check value
        GLfloat actual[16];
        const Gloop::Program program = programNode.getProgram();
        const GLint location = program.uniformLocation(uniformNode.getName());
        glGetUniformfv(program.id(), location, actual);
        for (int i = 0; i < 16; ++i) {
            CPPUNIT_ASSERT_DOUBLES_EQUAL(expected[i], actual[i], TOLERANCE);
        }

        // Remove uniform node
        useNode.removeChild(&uniformNode);
    }

    /**
     * Ensures `Mat4UniformNode::visit` works when usage is `VIEW_PROJECTION`.
     */
    void testVisitWithViewProjectionUsage() {

        // Add uniform node
        RapidGL::Mat4UniformNode uniformNode("Matrix", RapidGL::Mat4UniformNode::VIEW_PROJECTION);
        useNode.addChild(&uniformNode);

        // Make matrices
        const M3d::Mat4 viewMatrix = getRandomMatrix();
        const M3d::Mat4 projectionMatrix = getRandomMatrix();

        // Set up state
        RapidGL::State state;
        state.setViewMatrix(viewMatrix);
        state.setProjectionMatrix(projectionMatrix);

        // Visit nodes
        RapidGL::Visitor visitor(&state);
        visitor.visit(&sceneNode);

        // Define expected value
        GLfloat expected[16];
        const M3d::Mat4 viewProjectionMatrix = projectionMatrix * viewMatrix;
        viewProjectionMatrix.toArrayInColumnMajor(expected);

        // Check value
        GLfloat actual[16];
        const Gloop::Program program = programNode.getProgram();
        const GLint location = program.uniformLocation(uniformNode.getName());
        glGetUniformfv(program.id(), location, actual);
        for (int i = 0; i < 16; ++i) {
            CPPUNIT_ASSERT_DOUBLES_EQUAL(expected[i], actual[i], TOLERANCE);
        }

        // Remove uniform node
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
        Mat4UniformNodeTest test;
        test.testGetType();
        test.testParseUsageWithFoo();
        test.testParseUsageWithIdentity();
        test.testParseUsageWithModel();
        test.testParseUsageWithModelView();
        test.testParseUsageWithModelViewProjection();
        test.testParseUsageWithView();
        test.testParseUsageWithViewProjection();
        test.testVisitWithIdentityUsage();
        test.testVisitWithModelUsage();
        test.testVisitWithModelViewUsage();
        test.testVisitWithModelViewProjectionUsage();
        test.testVisitWithViewUsage();
        test.testVisitWithProjectionUsage();
        test.testVisitWithViewProjectionUsage();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        throw;
    }

    // Exit
    glfwTerminate();
    return 0;
}
