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
#include <map>
#include <Poco/Path.h>
#include <stdexcept>
#include <string>
#include "RapidGL/AttributeNode.hxx"
#include "RapidGL/Node.hxx"
#include "RapidGL/ProgramNode.hxx"
#include "RapidGL/ShaderNode.hxx"
#include "RapidGL/State.hxx"
#include "RapidGL/TextureNode.hxx"
#include "RapidGL/TextureNodeUnmarshaller.hxx"
#include "RapidGL/SquareNode.hxx"
#include "RapidGL/State.hxx"
#include "RapidGL/Visitor.hxx"


/**
 * Unit test for `TextureNodeUnmarshaller`.
 */
class TextureNodeUnmarshallerTest {
public:

    // Number of seconds to sleep after rendering
    static const int SLEEP_TIME_IN_SECONDS = 1;

    /**
     * Returns the source code for the fragment shader.
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

    // Instance to test with
    RapidGL::TextureNodeUnmarshaller unmarshaller;

    // Shader program
    RapidGL::ProgramNode programNode;

    // Vertex shader
    RapidGL::ShaderNode vertexShaderNode;

    // Fragment shader
    RapidGL::ShaderNode fragmentShaderNode;

    // Node describing vertex attribute
    RapidGL::AttributeNode vertexAttributeNode;

    // Node describing coordinate attribute
    RapidGL::AttributeNode coordinateAttributeNode;

    // Square
    RapidGL::SquareNode squareNode;

    /**
     * Constructs the test.
     */
    TextureNodeUnmarshallerTest() :
            vertexShaderNode(GL_VERTEX_SHADER, getVertexShaderSource()),
            fragmentShaderNode(GL_FRAGMENT_SHADER, getFragmentShaderSource()),
            vertexAttributeNode("MCVertex", RapidGL::AttributeNode::VERTEX),
            coordinateAttributeNode("TexCoord0", RapidGL::AttributeNode::COORDINATE) {
        programNode.addChild(&vertexShaderNode);
        programNode.addChild(&fragmentShaderNode);
        programNode.addChild(&vertexAttributeNode);
        programNode.addChild(&coordinateAttributeNode);
        programNode.addChild(&squareNode);
    }

    /**
     * Ensures `TextureNodeUnmarshaller::unmarshal` throws if passed an empty identifier.
     */
    void testUnmarshalWithEmptyId() {
        std::map<std::string,std::string> attributes;
        attributes["id"] = "";
        attributes["file"] = "RapidGL/crate.bmp";
        CPPUNIT_ASSERT_THROW(unmarshaller.unmarshal(attributes), std::runtime_error);
    }

    /**
     * Ensures `TextureNodeUnmarshaller::unmarshal` works correctly with a file.
     */
    void testUnmarshalWithFile() {

        // Unmarshal node
        std::map<std::string,std::string> attributes;
        attributes["id"] = "crate";
        attributes["file"] = "RapidGL/crate.bmp";
        RapidGL::Node* node = unmarshaller.unmarshal(attributes);
        RapidGL::TextureNode* textureNode = dynamic_cast<RapidGL::TextureNode*>(node);
        CPPUNIT_ASSERT(textureNode != NULL);

        // Check identifier
        CPPUNIT_ASSERT_EQUAL(std::string("crate"), textureNode->getId());

        // Render
        textureNode->addChild(&programNode);
        RapidGL::State state;
        RapidGL::Visitor visitor(&state);
        visitor.visit(textureNode);
        textureNode->removeChild(&programNode);
        glfwSwapBuffers();
        sleep(SLEEP_TIME_IN_SECONDS);
    }

    /**
     * Ensures `TextureNodeUnmarshall::unmarshal` throws if given a file and size.
     */
    void testUnmarshalWithFileAndSize() {
        std::map<std::string,std::string> attributes;
        attributes["id"] = "foo";
        attributes["file"] = "RapidGL/crate.bmp";
        attributes["size"] = "512";
        CPPUNIT_ASSERT_THROW(unmarshaller.unmarshal(attributes), std::runtime_error);
    }

    /**
     * Ensures `TextureNodeUnmarshaller::unmarshal` throws if missing both file and size.
     */
    void testUnmarshalWithMissingFileAndSize() {
        std::map<std::string,std::string> attributes;
        attributes["id"] = "foo";
        CPPUNIT_ASSERT_THROW(unmarshaller.unmarshal(attributes), std::runtime_error);
    }

    /**
     * Ensures `TextureNodeUnmarshaller::unmarshal` throws if missing an identifier.
     */
    void testUnmarshalWithMissingId() {
        std::map<std::string,std::string> attributes;
        attributes["file"] = "RapidGL/crate.bmp";
        CPPUNIT_ASSERT_THROW(unmarshaller.unmarshal(attributes), std::runtime_error);
    }

    /**
     * Ensures `TextureNodeUnmarshaller::unmarshal` throws if given a negative size.
     */
    void testUnmarshalWithNegativeSize() {
        std::map<std::string,std::string> attributes;
        attributes["id"] = "foo";
        attributes["size"] = "-2";
        CPPUNIT_ASSERT_THROW(unmarshaller.unmarshal(attributes), std::runtime_error);
    }

    /**
     * Ensures `TextureNodeUnmarshaller::unmarshal` works with a size.
     */
    void testUnmarshalWithSize() {

        // Unmarshal node
        std::map<std::string,std::string> attributes;
        attributes["id"] = "foo";
        attributes["size"] = "512";
        RapidGL::Node *node = unmarshaller.unmarshal(attributes);
        RapidGL::TextureNode* textureNode = dynamic_cast<RapidGL::TextureNode*>(node);
        CPPUNIT_ASSERT(textureNode != NULL);

        // Get texture object and target
        Gloop::TextureUnit unit = textureNode->getTextureUnit();
        Gloop::TextureObject texture = textureNode->getTextureObject();
        Gloop::TextureTarget target = textureNode->getTextureTarget();

        // Bind texture
        unit.activate();
        target.bind(texture);

        // Check width and height
        CPPUNIT_ASSERT_EQUAL(512, target.width());
        CPPUNIT_ASSERT_EQUAL(512, target.height());
        CPPUNIT_ASSERT_EQUAL(1, target.depth());
        CPPUNIT_ASSERT(target.redSize() > 0);
        CPPUNIT_ASSERT(target.greenSize() > 0);
        CPPUNIT_ASSERT(target.blueSize() > 0);
        CPPUNIT_ASSERT(target.alphaSize() > 0);
    }

    /**
     * Ensures `TextureNodeUnmarshaller::unmarhal` throws if passed an unsupported file type.
     */
    void testUnmarshalWithUnsupportedFileType() {
        std::map<std::string,std::string> attributes;
        attributes["id"] = "foo";
        attributes["file"] = "foo.bar";
        CPPUNIT_ASSERT_THROW(unmarshaller.unmarshal(attributes), std::runtime_error);
    }

    /**
     * Ensures `TextureNodeUnmarshaller::unmarshal` throws if given a zero size.
     */
    void testUnmarshalWithZeroSize() {
        std::map<std::string,std::string> attributes;
        attributes["id"] = "foo";
        attributes["size"] = "0";
        CPPUNIT_ASSERT_THROW(unmarshaller.unmarshal(attributes), std::runtime_error);
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
        TextureNodeUnmarshallerTest test;
        test.testUnmarshalWithEmptyId();
        test.testUnmarshalWithFile();
        test.testUnmarshalWithFileAndSize();
        test.testUnmarshalWithMissingFileAndSize();
        test.testUnmarshalWithMissingId();
        test.testUnmarshalWithNegativeSize();
        test.testUnmarshalWithSize();
        test.testUnmarshalWithUnsupportedFileType();
        test.testUnmarshalWithZeroSize();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        throw;
    }

    sleep(1);

    // Exit
    glfwTerminate();
    return 0;
}