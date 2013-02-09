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
#include <GL/glfw.h>
#include <glycerin/Volume.hxx>
#include <glycerin/VolumeReader.hxx>
#include <gloop/TextureObject.hxx>
#include <gloop/TextureTarget.hxx>
#include <gloop/TextureUnit.hxx>
#include <iostream>
#include <Poco/Path.h>
#include <stdexcept>
#include <string>
#include "RapidGL/AttributeNode.h"
#include "RapidGL/FloatUniformNode.h"
#include "RapidGL/ProgramNode.h"
#include "RapidGL/Sampler3dUniformNode.h"
#include "RapidGL/SceneNode.h"
#include "RapidGL/ShaderNode.h"
#include "RapidGL/SquareNode.h"
#include "RapidGL/State.h"
#include "RapidGL/TextureNode.h"
#include "RapidGL/UseNode.h"
#include "RapidGL/Visitor.h"


/**
 * Unit test for `Sampler3dUniformNode`.
 */
class Sampler3dUniformNodeTest {
public:

    // Number of seconds to sleep after rendering
    static const double SLEEP_TIME_IN_SECONDS = 1.0;

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
                "uniform sampler3D Texture1;\n"
                "uniform sampler3D Texture2;\n"
                "uniform float Depth;\n"
                "in vec4 Coord0;\n"
                "out vec4 FragColor;\n"
                "void main() {\n"
                "  vec3 coord = vec3(Coord0.st, Depth);\n"
                "  float sample;\n"
                "  if (Coord0.s < 0.5) {\n"
                "    sample = texture(Texture1, coord).r;\n"
                "  } else {\n"
                "    sample = texture(Texture2, coord).r;\n"
                "  }\n"
                "  FragColor = vec4(vec3(sample), 1);\n"
                "}\n";
    }

    /**
     * Returns the texture object to use for the bunny texture node.
     */
    static Gloop::TextureObject getBunnyTextureObject() {
        Glycerin::VolumeReader reader;
        const Glycerin::Volume volume = reader.read("RapidGL/bunny.vlb");
        return volume.createTexture();
    }

    /**
     * Returns the texture object to use for the head texture node.
     */
    static Gloop::TextureObject getHeadTextureObject() {
        Glycerin::VolumeReader reader;
        const Glycerin::Volume volume = reader.read("RapidGL/head.vlb");
        return volume.createTexture();
    }

    // Root of scene
    RapidGL::SceneNode sceneNode;

    // Bunny texture
    RapidGL::TextureNode bunnyTextureNode;

    // Head texture
    RapidGL::TextureNode headTextureNode;

    // Shader program
    RapidGL::ProgramNode programNode;

    // Vertex shader
    RapidGL::ShaderNode vertexShaderNode;

    // Fragment shader
    RapidGL::ShaderNode fragmentShaderNode;

    // Node indicating which attribute is for vertices
    RapidGL::AttributeNode vertexAttributeNode;

    // Node indicating which attribute is for texture coordinates
    RapidGL::AttributeNode coordinateAttributeNode;

    // Usage of program
    RapidGL::UseNode useNode;

    // Square
    RapidGL::SquareNode squareNode;

    // Uniform for bunny texture
    RapidGL::Sampler3dUniformNode bunnyUniformNode;

    // Uniform for head texture
    RapidGL::Sampler3dUniformNode headUniformNode;

    // Uniform for depth
    RapidGL::FloatUniformNode depthUniformNode;

    /**
     * Constructs the test.
     */
    Sampler3dUniformNodeTest() :
            bunnyTextureNode("bunny", Gloop::TextureTarget::texture3d(), getBunnyTextureObject()),
            headTextureNode("head", Gloop::TextureTarget::texture3d(), getHeadTextureObject()),
            programNode("foo"),
            vertexShaderNode(GL_VERTEX_SHADER, getVertexShaderSource()),
            fragmentShaderNode(GL_FRAGMENT_SHADER, getFragmentShaderSource()),
            vertexAttributeNode("MCVertex", RapidGL::AttributeNode::POINT, -1),
            coordinateAttributeNode("TexCoord0", RapidGL::AttributeNode::COORDINATE, -1),
            useNode("foo"),
            bunnyUniformNode("Texture1", "bunny"),
            headUniformNode("Texture2", "head"),
            depthUniformNode("Depth") {
        sceneNode.addChild(&programNode);
        programNode.addChild(&vertexShaderNode);
        programNode.addChild(&fragmentShaderNode);
        programNode.addChild(&vertexAttributeNode);
        programNode.addChild(&coordinateAttributeNode);
        sceneNode.addChild(&bunnyTextureNode);
        bunnyTextureNode.addChild(&headTextureNode);
        headTextureNode.addChild(&useNode);
        useNode.addChild(&bunnyUniformNode);
        useNode.addChild(&headUniformNode);
        useNode.addChild(&depthUniformNode);
        useNode.addChild(&squareNode);
    }

    /**
     * Ensures `Sampler3dUniformNode::preVisit` throws if texture node is of wrong type.
     */
    void testPreVisitWithWrongType() {

        // Make nodes
        RapidGL::SceneNode sceneNode;
        RapidGL::ProgramNode programNode("bar");
        RapidGL::ShaderNode vertexShaderNode(GL_VERTEX_SHADER, getVertexShaderSource());
        RapidGL::ShaderNode fragmentShaderNode(GL_FRAGMENT_SHADER, getFragmentShaderSource());
        RapidGL::TextureNode textureNode("foo", Gloop::TextureTarget::texture2d(), Gloop::TextureObject::generate());
        RapidGL::UseNode useNode("bar");
        RapidGL::Sampler3dUniformNode uniformNode("Texture1", "foo");

        // Connect nodes
        sceneNode.addChild(&programNode);
        programNode.addChild(&vertexShaderNode);
        programNode.addChild(&fragmentShaderNode);
        sceneNode.addChild(&textureNode);
        textureNode.addChild(&useNode);
        useNode.addChild(&uniformNode);

        // Visit the nodes
        RapidGL::State state;
        RapidGL::Visitor visitor(&state);
        CPPUNIT_ASSERT_THROW(visitor.visit(&sceneNode), std::runtime_error);
    }

    /**
     * Ensures `Sampler3dUniformNode` constructor throws if passed an empty link.
     */
    void testSampler3dUniformNodeWithEmptyLink() {
        CPPUNIT_ASSERT_THROW(RapidGL::Sampler3dUniformNode("foo", ""), std::invalid_argument);
    }

    /**
     * Ensures `Sampler3dUniformNode` constructor throws if passed an empty name.
     */
    void testSampler3dUniformNodeWithEmptyName() {
        CPPUNIT_ASSERT_THROW(RapidGL::Sampler3dUniformNode("", "foo"), std::invalid_argument);
    }

    /**
     * Ensures `Sampler3dUniformNode::testVisit` works correctly.
     */
    void testVisit() {

        // Visit the nodes
        RapidGL::State state;
        RapidGL::Visitor visitor(&state);
        visitor.visit(&sceneNode);

        // Check units
        CPPUNIT_ASSERT_EQUAL(0, bunnyUniformNode.getTextureUnit().toOrdinal());
        CPPUNIT_ASSERT_EQUAL(1, headUniformNode.getTextureUnit().toOrdinal());

        // Flush and pause
        for (int i = 0; i < 100; ++i) {
            depthUniformNode.setValue(((GLfloat) i) / 100);
            visitor.visit(&sceneNode);
            glfwSwapBuffers();
        }
        glfwSleep(SLEEP_TIME_IN_SECONDS);
    }
};

int main(int argc, char* argv[]) {

    // Capture working directory before GLFW changes it
#ifdef __APPLE__
    const std::string cwd = Poco::Path::current();
#endif

    // Initialize GLFW
    if (!glfwInit()) {
        throw std::runtime_error("Could not initialize GLFW!");
    }

#ifdef __APPLE__
    chdir(cwd.c_str());
#endif

    // Open window
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 2);
    glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    if (!glfwOpenWindow(512, 512, 0, 0, 0, 0, 0, 0, GLFW_WINDOW)) {
        throw std::runtime_error("Could not open GLFW window!");
    }

    // Run test
    try {
        Sampler3dUniformNodeTest test;
        test.testPreVisitWithWrongType();
        test.testSampler3dUniformNodeWithEmptyLink();
        test.testSampler3dUniformNodeWithEmptyName();
        test.testVisit();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        throw;
    }

    // Exit
    glfwTerminate();
    return 0;
}
