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
#include <glycerin/Bitmap.hxx>
#include <glycerin/BitmapReader.hxx>
#include <gloop/TextureObject.hxx>
#include <gloop/TextureTarget.hxx>
#include <gloop/TextureUnit.hxx>
#include <iostream>
#include <Poco/Path.h>
#include <stdexcept>
#include <string>
#include "RapidGL/AttributeNode.hxx"
#include "RapidGL/ProgramNode.hxx"
#include "RapidGL/Sampler2dUniformNode.hxx"
#include "RapidGL/ShaderNode.hxx"
#include "RapidGL/SquareNode.hxx"
#include "RapidGL/State.hxx"
#include "RapidGL/TextureNode.hxx"
#include "RapidGL/Visitor.hxx"


/**
 * Unit test for `Sampler2dUniformNode`.
 */
class Sampler2dUniformNodeTest {
public:

    // Number of seconds to sleep after rendering
    static const int SLEEP_TIME_IN_SECONDS = 1;

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
                "uniform sampler2D Texture1;\n"
                "uniform sampler2D Texture2;\n"
                "in vec4 Coord0;\n"
                "out vec4 FragColor;\n"
                "void main() {\n"
                "  if (Coord0.s < 0.5) {\n"
                "    FragColor = texture(Texture1, Coord0.st);\n"
                "  } else {\n"
                "    FragColor = texture(Texture2, Coord0.st);\n"
                "  }\n"
                "}\n";
    }

    /**
     * Returns the texture object to use for the crate texture node.
     */
    static Gloop::TextureObject getCrateTextureObject() {
        Glycerin::BitmapReader reader;
        const Glycerin::Bitmap bitmap = reader.read("RapidGL/crate.bmp");
        return bitmap.createTexture();
    }

    /**
     * Returns the texture object to use for the stone texture node.
     */
    static Gloop::TextureObject getStoneTextureObject() {
        Glycerin::BitmapReader reader;
        const Glycerin::Bitmap bitmap = reader.read("RapidGL/stone.bmp");
        return bitmap.createTexture();
    }

    // Crate texture
    RapidGL::TextureNode crateTextureNode;

    // Stone texture
    RapidGL::TextureNode stoneTextureNode;

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

    // Square
    RapidGL::SquareNode squareNode;

    // Uniform for crate texture
    RapidGL::Sampler2dUniformNode crateUniformNode;

    // Uniform for stone texture
    RapidGL::Sampler2dUniformNode stoneUniformNode;

    /**
     * Constructs the test.
     */
    Sampler2dUniformNodeTest() :
            crateTextureNode("crate", Gloop::TextureTarget::texture2d(), getCrateTextureObject()),
            stoneTextureNode("stone", Gloop::TextureTarget::texture2d(), getStoneTextureObject()),
            vertexShaderNode(GL_VERTEX_SHADER, getVertexShaderSource()),
            fragmentShaderNode(GL_FRAGMENT_SHADER, getFragmentShaderSource()),
            vertexAttributeNode("MCVertex", RapidGL::AttributeNode::VERTEX),
            coordinateAttributeNode("TexCoord0", RapidGL::AttributeNode::COORDINATE),
            crateUniformNode("Texture1", "crate"),
            stoneUniformNode("Texture2", "stone") {
        crateTextureNode.addChild(&stoneTextureNode);
        stoneTextureNode.addChild(&programNode);
        programNode.addChild(&vertexShaderNode);
        programNode.addChild(&fragmentShaderNode);
        programNode.addChild(&vertexAttributeNode);
        programNode.addChild(&coordinateAttributeNode);
        programNode.addChild(&crateUniformNode);
        programNode.addChild(&stoneUniformNode);
        programNode.addChild(&squareNode);
    }

    /**
     * Ensures `Sampler2dUniformNode::preVisit` throws if texture node is of wrong type.
     */
    void testPreVisitWithWrongType() {

        // Make nodes
        RapidGL::TextureNode textureNode("foo", Gloop::TextureTarget::texture3d(), Gloop::TextureObject::generate());
        RapidGL::Sampler2dUniformNode uniformNode("Texture", "foo");
        textureNode.addChild(&uniformNode);

        // Call `preVisit`
        RapidGL::State state;
        CPPUNIT_ASSERT_THROW(uniformNode.preVisit(state), std::runtime_error);
    }

    /**
     * Ensures `Sampler2dUniformNode` constructor throws if passed an empty link.
     */
    void testSampler2dUniformNodeWithEmptyLink() {
        CPPUNIT_ASSERT_THROW(RapidGL::Sampler2dUniformNode("foo", ""), std::invalid_argument);
    }

    /**
     * Ensures `Sampler2dUniformNode` constructor throws if passed an empty name.
     */
    void testSampler2dUniformNodeWithEmptyName() {
        CPPUNIT_ASSERT_THROW(RapidGL::Sampler2dUniformNode("", "foo"), std::invalid_argument);
    }

    /**
     * Ensures `Sampler2dUniformNode::testVisit` works correctly.
     */
    void testVisit() {

        // Visit the nodes
        RapidGL::State state;
        RapidGL::Visitor visitor(&state);
        visitor.visit(&crateTextureNode);

        // Check units
        CPPUNIT_ASSERT_EQUAL(0, crateUniformNode.getTextureUnit().toOrdinal());
        CPPUNIT_ASSERT_EQUAL(1, stoneUniformNode.getTextureUnit().toOrdinal());

        // Flush and pause
        glfwSwapBuffers();
        sleep(SLEEP_TIME_IN_SECONDS);
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
        Sampler2dUniformNodeTest test;
        test.testPreVisitWithWrongType();
        test.testSampler2dUniformNodeWithEmptyLink();
        test.testSampler2dUniformNodeWithEmptyName();
        test.testVisit();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        throw;
    }

    // Exit
    glfwTerminate();
    return 0;
}