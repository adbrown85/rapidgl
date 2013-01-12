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
#include <iostream>
#include <stdexcept>
#include <GL/glfw.h>
#include <gloop/TextureObject.hxx>
#include <gloop/TextureTarget.hxx>
#include "RapidGL/AttributeNode.hxx"
#include "RapidGL/ClearNode.hxx"
#include "RapidGL/FramebufferNode.hxx"
#include "RapidGL/ProgramNode.hxx"
#include "RapidGL/ShaderNode.hxx"
#include "RapidGL/SquareNode.hxx"
#include "RapidGL/State.hxx"
#include "RapidGL/TextureAttachmentNode.hxx"
#include "RapidGL/TextureNode.hxx"
#include "RapidGL/Visitor.hxx"


/**
 * Test for `TextureAttachmentNode`.
 */
class TextureAttachmentNodeTest {
public:

    static Gloop::TextureObject createTextureObject() {
        const Gloop::TextureObject texture = Gloop::TextureObject::generate();
        const Gloop::TextureTarget texture2d = Gloop::TextureTarget::texture2d();
        texture2d.bind(texture);
        texture2d.minFilter(GL_NEAREST);
        texture2d.magFilter(GL_NEAREST);
        texture2d.texImage2d(0, GL_RGB, 512, 512, GL_RGB, GL_UNSIGNED_BYTE, NULL);
        return texture;
    }

    /**
     * Returns the source code for the first vertex shader.
     */
    static std::string getFirstVertexShaderSource() {
        return
                "#version 140\n"
                "in vec4 MCVertex;\n"
                "void main() {\n"
                "  gl_Position = MCVertex;\n"
                "}\n";
    }

    /**
     * Returns the source code for the first fragment shader.
     */
    static std::string getFirstFragmentShaderSource() {
        return
                "#version 140\n"
                "uniform vec4 Color = vec4(0,1,0,1);\n"
                "out vec4 FragColor;\n"
                "void main() {\n"
                "  FragColor = Color;\n"
                "}\n";
    }

    /**
     * Returns the source code for the second vertex shader.
     */
    static std::string getSecondVertexShaderSource() {
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
     * Returns the source code for the second fragment shader.
     */
    static std::string getSecondFragmentShaderSource() {
        return
                "#version 140\n"
                "uniform sampler2D Texture;\n"
                "in vec4 Coord0;\n"
                "out vec4 FragColor;\n"
                "void main() {\n"
                "  FragColor = texture(Texture, Coord0.st);\n"
                "}\n";
    }

    // Texture to attach
    RapidGL::TextureNode textureNode;

    // Framebuffer
    RapidGL::FramebufferNode framebufferNode;

    // Attachment to framebuffer
    RapidGL::TextureAttachmentNode attachmentNode;

    // Clear nodes
    RapidGL::ClearNode firstClearNode;
    RapidGL::ClearNode secondClearNode;

    // Shader programs
    RapidGL::ProgramNode firstProgramNode;
    RapidGL::ProgramNode secondProgramNode;

    // Vertex shaders
    RapidGL::ShaderNode firstVertexShaderNode;
    RapidGL::ShaderNode secondVertexShaderNode;

    // Fragment shaders
    RapidGL::ShaderNode firstFragmentShaderNode;
    RapidGL::ShaderNode secondFragmentShaderNode;

    // Vertex attributes for points
    RapidGL::AttributeNode firstPointAttributeNode;
    RapidGL::AttributeNode secondPointAttributeNode;

    // Vertex attributes for texture coordinates
    RapidGL::AttributeNode secondCoordAttributeNode;

    // Square nodes
    RapidGL::SquareNode firstSquareNode;
    RapidGL::SquareNode secondSquareNode;

    /**
     * Constructs the test.
     */
    TextureAttachmentNodeTest() :
            textureNode("foo", Gloop::TextureTarget::texture2d(), createTextureObject()),
            attachmentNode(RapidGL::AttachmentNode::COLOR, "foo"),
            firstClearNode(0.0f, 0.0f, 1.0f),
            secondClearNode(1.0f, 0.0f, 0.0f),
            firstVertexShaderNode(GL_VERTEX_SHADER, getFirstVertexShaderSource()),
            firstFragmentShaderNode(GL_FRAGMENT_SHADER, getFirstFragmentShaderSource()),
            firstPointAttributeNode("MCVertex", RapidGL::AttributeNode::POINT),
            secondVertexShaderNode(GL_VERTEX_SHADER, getSecondVertexShaderSource()),
            secondFragmentShaderNode(GL_FRAGMENT_SHADER, getSecondFragmentShaderSource()),
            secondPointAttributeNode("MCVertex", RapidGL::AttributeNode::POINT),
            secondCoordAttributeNode("TexCoord0", RapidGL::AttributeNode::COORDINATE) {

        textureNode.addChild(&framebufferNode);
        textureNode.addChild(&secondProgramNode);

        framebufferNode.addChild(&attachmentNode);
        framebufferNode.addChild(&firstProgramNode);
        firstProgramNode.addChild(&firstVertexShaderNode);
        firstProgramNode.addChild(&firstFragmentShaderNode);
        firstProgramNode.addChild(&firstPointAttributeNode);
        firstProgramNode.addChild(&firstClearNode);
        firstProgramNode.addChild(&firstSquareNode);

        secondProgramNode.addChild(&secondVertexShaderNode);
        secondProgramNode.addChild(&secondFragmentShaderNode);
        secondProgramNode.addChild(&secondPointAttributeNode);
        secondProgramNode.addChild(&secondCoordAttributeNode);
        secondProgramNode.addChild(&secondClearNode);
        secondProgramNode.addChild(&secondSquareNode);
    }

    /**
     * Runs the test.
     */
    void run() {
        RapidGL::State state;
        RapidGL::Visitor visitor(&state);
        visitor.visit(&textureNode);
        glfwSwapBuffers();
        sleep(2);
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
        throw std::runtime_error("Could not open GLFW windodw!");
    }

    // Run test
    try {
        TextureAttachmentNodeTest test;
        test.run();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        throw e;
    }

    // Exit
    glfwTerminate();
    return 0;
}