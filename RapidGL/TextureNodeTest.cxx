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
#include <gloop/TextureObject.hxx>
#include <gloop/TextureTarget.hxx>
#include <gloop/TextureUnit.hxx>
#include <glycerin/Bitmap.hxx>
#include <glycerin/BitmapReader.hxx>
#include <iostream>
#include <stdexcept>
#include <Poco/Path.h>
#include "RapidGL/AttributeNode.hxx"
#include "RapidGL/ProgramNode.hxx"
#include "RapidGL/ShaderNode.hxx"
#include "RapidGL/SquareNode.hxx"
#include "RapidGL/TextureNode.hxx"
#include "RapidGL/State.hxx"
#include "RapidGL/Visitor.hxx"


/**
 * Unit test for `TextureNode`.
 */
class TextureNodeTest {
public:

    // Number of seconds to pause after rendering
    static const int SLEEP_TIME_IN_SECONDS = 1;

    /**
     * Returns the source for the fragment shader.
     */
    static std::string getFragmentShaderSource() {
        return
                "#version 140\n"
                "uniform sampler2D Texture;\n"
                "in vec4 Coord0;\n"
                "out vec4 FragColor;\n"
                "void main() {\n"
                "  FragColor = texture(Texture, Coord0.st);\n"
                "}\n";
    }

    /**
     * Returns the texture object to use for the nexture node.
     */
    static Gloop::TextureObject getTextureObject() {
        Glycerin::BitmapReader reader;
        const Glycerin::Bitmap bitmap = reader.read("RapidGL/crate.bmp");
        return bitmap.createTexture();
    }

    /**
     * Returns the source for the vertex shader.
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

    // Node with texture
    RapidGL::TextureNode textureNode;

    // Shader program
    RapidGL::ProgramNode programNode;

    // Vertex shader
    RapidGL::ShaderNode vertexShaderNode;

    // Fragment shader
    RapidGL::ShaderNode fragmentShaderNode;

    // Node describing 'MCVertex' attribute
    RapidGL::AttributeNode vertexAttributeNode;

    // Node describing 'TexCoord0' attribute
    RapidGL::AttributeNode coordinateAttributeNode;

    // Square
    RapidGL::SquareNode squareNode;

    /**
     * Constructs the test.
     */
    TextureNodeTest() :
            textureNode("crate", Gloop::TextureTarget::texture2d(), getTextureObject()),
            vertexShaderNode(GL_VERTEX_SHADER, getVertexShaderSource()),
            fragmentShaderNode(GL_FRAGMENT_SHADER, getFragmentShaderSource()),
            vertexAttributeNode("MCVertex", RapidGL::AttributeNode::POINT),
            coordinateAttributeNode("TexCoord0", RapidGL::AttributeNode::COORDINATE) {
        textureNode.addChild(&programNode);
        programNode.addChild(&vertexShaderNode);
        programNode.addChild(&fragmentShaderNode);
        programNode.addChild(&vertexAttributeNode);
        programNode.addChild(&coordinateAttributeNode);
        programNode.addChild(&squareNode);
    }

    /**
     * Ensures `TextureNode::getUnit` returns increasing values when nodes are nested.
     */
    void testGetUnitWithNestedTextures() {

        // Store a reference to the target
        Gloop::TextureTarget target = Gloop::TextureTarget::texture2d();

        // Create textures
        RapidGL::TextureNode t1("t1", target, Gloop::TextureObject::generate());
        RapidGL::TextureNode t2("t2", target, Gloop::TextureObject::generate());
        RapidGL::TextureNode t3("t3", target, Gloop::TextureObject::generate());

        // Connect textures
        t1.addChild(&t2);
        t2.addChild(&t3);

        // Visit
        RapidGL::State state;
        RapidGL::Visitor visitor(&state);
        visitor.visit(&t1);

        // Check units
        CPPUNIT_ASSERT_EQUAL((GLenum) GL_TEXTURE0, t1.getTextureUnit().toEnum());
        CPPUNIT_ASSERT_EQUAL((GLenum) GL_TEXTURE1, t2.getTextureUnit().toEnum());
        CPPUNIT_ASSERT_EQUAL((GLenum) GL_TEXTURE2, t3.getTextureUnit().toEnum());
    }

    /**
     * Ensures `TextureNode` constructor throws if identifier is empty.
     */
    void testTextureNodeWithEmptyId() {
        const Gloop::TextureTarget target = Gloop::TextureTarget::texture2d();
        const Gloop::TextureObject texture = Gloop::TextureObject::generate();
        CPPUNIT_ASSERT_THROW(RapidGL::TextureNode("", target, texture), std::invalid_argument);
        texture.dispose();
    }

    /**
     * Ensures `TextureNode::visit` works correctly.
     */
    void testVisit() {
        RapidGL::State state;
        RapidGL::Visitor visitor(&state);
        visitor.visit(&textureNode);
        glfwSwapBuffers();
        sleep(SLEEP_TIME_IN_SECONDS);
    }
};

int main(int argc, char* argv[]) {

    // Capture working directory before GLFW changes it
#ifdef __APPLE__
    const std::string& cwd = Poco::Path::current();
#endif

    // Initialize GLFW
    if (!glfwInit()) {
        throw std::runtime_error("Could not initialize GLFW!");
    }

    // Reset working directory
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
        TextureNodeTest test;
        test.testGetUnitWithNestedTextures();
        test.testTextureNodeWithEmptyId();
        test.testVisit();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        throw e;
    }

    // Exit
    glfwTerminate();
    return 0;
}
