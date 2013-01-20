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
#include "RapidGL/AttributeNode.h"
#include "RapidGL/ClearNode.h"
#include "RapidGL/FloatUniformNode.h"
#include "RapidGL/Node.h"
#include "RapidGL/ProgramNode.h"
#include "RapidGL/ShaderNode.h"
#include "RapidGL/State.h"
#include "RapidGL/TextureNode.h"
#include "RapidGL/TextureNodeUnmarshaller.h"
#include "RapidGL/SquareNode.h"
#include "RapidGL/State.h"
#include "RapidGL/Visitor.h"


/**
 * Unit test for `TextureNodeUnmarshaller`.
 */
class TextureNodeUnmarshallerTest {
public:

    // Number of seconds to sleep after rendering
    static const double SLEEP_TIME_IN_SECONDS = 1.0;

    // Instance to test with
    RapidGL::TextureNodeUnmarshaller unmarshaller;

    /**
     * Ensures `TextureNodeUnmarshaller::unmarshal` works correctly with a bitmap file.
     */
    void testUnmarshalWithBitmapFile() {

        // Define vertex shader source code
        const std::string vertexShaderSource =
                "#version 140\n"
                "in vec4 MCVertex;\n"
                "in vec4 TexCoord0;\n"
                "out vec4 Coord0;\n"
                "void main() {\n"
                "  gl_Position = MCVertex;\n"
                "  Coord0 = TexCoord0;\n"
                "}\n";

        // Define fragment shader source code
        const std::string fragmentShaderSource =
                "#version 140\n"
                "uniform sampler2D Texture;\n"
                "in vec4 Coord0;\n"
                "out vec4 FragColor;\n"
                "void main() {\n"
                "  FragColor = texture(Texture, Coord0.st);\n"
                "}\n";

        // Create nodes
        RapidGL::ProgramNode programNode;
        RapidGL::ShaderNode vertexShaderNode(GL_VERTEX_SHADER, vertexShaderSource);
        RapidGL::ShaderNode fragmentShaderNode(GL_FRAGMENT_SHADER, fragmentShaderSource);
        RapidGL::AttributeNode pointAttributeNode("MCVertex", RapidGL::AttributeNode::POINT);
        RapidGL::AttributeNode coordinateAttributeNode("TexCoord0", RapidGL::AttributeNode::COORDINATE);
        RapidGL::SquareNode squareNode;

        // Connect nodes
        programNode.addChild(&vertexShaderNode);
        programNode.addChild(&fragmentShaderNode);
        programNode.addChild(&pointAttributeNode);
        programNode.addChild(&coordinateAttributeNode);
        programNode.addChild(&squareNode);

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
        glfwSleep(SLEEP_TIME_IN_SECONDS);
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
        CPPUNIT_ASSERT_EQUAL((GLenum) GL_LINEAR, target.minFilter());
        CPPUNIT_ASSERT_EQUAL((GLenum) GL_LINEAR, target.magFilter());
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
     * Ensures `TextureNodeUnmarshaller::unmarshal` works with a volume file.
     */
    void testUnmarshalWithVolumeFile() {

        // Define the source code for the vertex shader
        const std::string vertexShaderSource =
                "#version 140\n"
                "in vec4 MCVertex;\n"
                "in vec4 TexCoord0;\n"
                "out vec4 Coord0;\n"
                "void main() {\n"
                "  gl_Position = MCVertex;\n"
                "  Coord0 = TexCoord0;\n"
                "}\n";

        // Define the source code for the fragment shader
        const std::string fragmentShaderSource =
                "#version 140\n"
                "uniform float Depth;\n"
                "uniform sampler3D Volume;\n"
                "in vec4 Coord0;\n"
                "out vec4 FragColor;\n"
                "void main() {\n"
                "  float value = texture(Volume, vec3(Coord0.st, Depth)).r;\n"
                "  FragColor = vec4(vec3(value), 1);\n"
                "}\n";

        // Create clear
        RapidGL::ClearNode clearNode;

        // Create texture
        std::map<std::string,std::string> attributes;
        attributes["id"] = "volume";
        attributes["file"] = "RapidGL/bunny.vlb";
        RapidGL::Node* textureNode = unmarshaller.unmarshal(attributes);

        // Create program
        RapidGL::ProgramNode programNode;
        RapidGL::ShaderNode vertexShaderNode(GL_VERTEX_SHADER, vertexShaderSource);
        RapidGL::ShaderNode fragmentShaderNode(GL_FRAGMENT_SHADER, fragmentShaderSource);
        RapidGL::AttributeNode pointAttributeNode("MCVertex", RapidGL::AttributeNode::POINT);
        RapidGL::AttributeNode coordAttributeNode("TexCoord0", RapidGL::AttributeNode::COORDINATE);

        // Create square
        RapidGL::SquareNode squareNode;

        // Create uniform to set depth
        RapidGL::FloatUniformNode uniformNode("Depth");
        uniformNode.setValue(0.0f);

        // Connect nodes
        clearNode.addChild(textureNode);
        textureNode->addChild(&programNode);
        programNode.addChild(&vertexShaderNode);
        programNode.addChild(&fragmentShaderNode);
        programNode.addChild(&pointAttributeNode);
        programNode.addChild(&coordAttributeNode);
        programNode.addChild(&uniformNode);
        programNode.addChild(&squareNode);

        // Visit
        RapidGL::State state;
        RapidGL::Visitor visitor(&state);
        for (int i = 0; i < 100; ++i) {
            uniformNode.setValue(((GLfloat) i) / 100);
            visitor.visit(&clearNode);
            glfwSwapBuffers();
        }

        // Flush
        glfwSleep(SLEEP_TIME_IN_SECONDS);
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
        test.testUnmarshalWithBitmapFile();
        test.testUnmarshalWithEmptyId();
        test.testUnmarshalWithFileAndSize();
        test.testUnmarshalWithMissingFileAndSize();
        test.testUnmarshalWithMissingId();
        test.testUnmarshalWithNegativeSize();
        test.testUnmarshalWithSize();
        test.testUnmarshalWithUnsupportedFileType();
        test.testUnmarshalWithVolumeFile();
        test.testUnmarshalWithZeroSize();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        throw;
    }

    // Exit
    glfwTerminate();
    return 0;
}
