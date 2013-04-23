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
#include <exception>
#include <iostream>
#include <map>
#include <stdexcept>
#include <string>
#include <cppunit/extensions/HelperMacros.h>
#include <GL/glfw.h>
#include <gloop/RenderbufferObject.hxx>
#include <gloop/RenderbufferTarget.hxx>
#include "RapidGL/RenderbufferNode.h"
#include "RapidGL/RenderbufferNodeUnmarshaller.h"


/**
 * Unit test for `RenderbufferNodeUnmarshaller`.
 */
class RenderbufferNodeUnmarshallerTest {
public:

    /**
     * Checks if an enumeration is a depth component.
     *
     * @param enumeration Enumeration to check
     * @return `true` if enumeration is a depth component
     */
    static bool isDepthComponent(const GLenum enumeration) {
        switch (enumeration) {
        case GL_DEPTH_COMPONENT:
        case GL_DEPTH_COMPONENT16:
        case GL_DEPTH_COMPONENT24:
        case GL_DEPTH_COMPONENT32:
        case GL_DEPTH_COMPONENT32F:
            return true;
        default:
            return false;
        }
    }

    /**
     * Checks if an enumeration is a red format.
     *
     * @param enumeration Enumeration to check
     * @return `true` if enumeration is a red format
     */
    static bool isRed(const GLenum enumeration) {
        switch (enumeration) {
        case GL_RED:
        case GL_R8:
        case GL_R16:
        case GL_R16F:
        case GL_R32F:
        case GL_R8I:
        case GL_R8UI:
        case GL_R16I:
        case GL_R16UI:
        case GL_R32I:
        case GL_R32UI:
            return true;
        default:
            return false;
        }
    }

    /**
     * Checks if an enumeration is a red-green format.
     *
     * @param enumeration Enumeration to check
     * @return `true` if enumeration is a red-green format
     */
    static bool isRedGreen(const GLenum enumeration) {
        switch (enumeration) {
        case GL_RG:
        case GL_RG8:
        case GL_RG16:
        case GL_RG16F:
        case GL_RG32F:
        case GL_RG8I:
        case GL_RG8UI:
        case GL_RG16I:
        case GL_RG16UI:
        case GL_RG32I:
        case GL_RG32UI:
            return true;
        default:
            return false;
        }
    }

    /**
     * Checks if an enumeration is a red-green-blue format.
     *
     * @param enumeration Enumeration to check
     * @return `true` if enumeration is a red-green-blue format
     */
    static bool isRedGreenBlue(const GLenum enumeration) {
        switch (enumeration) {
        case GL_RGB:
        case GL_RGB8:
        case GL_RGB16:
        case GL_RGB16F:
        case GL_RGB32F:
        case GL_RGB8I:
        case GL_RGB8UI:
        case GL_RGB16I:
        case GL_RGB16UI:
        case GL_RGB32I:
        case GL_RGB32UI:
            return true;
        default:
            return false;
        }
    }

    /**
     * Checks if an enumeration is a red-green-blue-alpha format.
     *
     * @param enumeration Enumeration to check
     * @return `true` if enumeration is a red-green-blue-alpha format
     */
    static bool isRedGreenBlueAlpha(const GLenum enumeration) {
        switch (enumeration) {
        case GL_RGBA:
        case GL_RGBA8:
        case GL_RGBA16:
        case GL_RGBA16F:
        case GL_RGBA32F:
        case GL_RGBA8I:
        case GL_RGBA8UI:
        case GL_RGBA16I:
        case GL_RGBA16UI:
        case GL_RGBA32I:
        case GL_RGBA32UI:
            return true;
        default:
            return false;
        }
    }

    // Instance to use for testing
    RapidGL::Unmarshaller* const unmarshaller;

    // Renderbuffer target
    const Gloop::RenderbufferTarget renderbuffer;

    /**
     * Constructs a `RenderbufferNodeUnmarshallerTest`.
     */
    RenderbufferNodeUnmarshallerTest() : unmarshaller(new RapidGL::RenderbufferNodeUnmarshaller()) {
        // empty
    }

    /**
     * Ensures `RenderbufferNodeUnmarshaller::unmarshal` works if _format_ is _depth_.
     */
    void testUnmarshalWhenFormatIsDepth() {

        // Make mape
        std::map<std::string,std::string> attributes;
        attributes["id"] = "foo";
        attributes["format"] = "depth";
        attributes["width"] = "40";
        attributes["height"] = "30";

        // Unmarshal node
        RapidGL::Node* node = unmarshaller->unmarshal(attributes);
        const RapidGL::RenderbufferNode* renderbufferNode = dynamic_cast<RapidGL::RenderbufferNode*>(node);
        CPPUNIT_ASSERT(renderbufferNode != NULL);

        // Check value
        const Gloop::RenderbufferObject rbo = renderbufferNode->getRenderbufferObject();
        renderbuffer.bind(rbo);
        CPPUNIT_ASSERT(isDepthComponent(renderbuffer.internalFormat()));
        renderbuffer.unbind();
    }

    /**
     * Ensures `RenderbufferNodeUnmarshaller::unmarshal` throws if _format_ is empty.
     */
    void testUnmarshalWhenFormatIsEmpty() {
        std::map<std::string,std::string> attributes;
        attributes["id"] = "foo";
        attributes["format"] = "";
        attributes["width"] = "40";
        attributes["height"] = "30";
        CPPUNIT_ASSERT_THROW(unmarshaller->unmarshal(attributes), std::runtime_error);
    }

    /**
     * Ensures `RenderbufferNodeUnmarshaller::unmarshal` throws if _format_ is invalid.
     */
    void testUnmarshalWhenFormatIsInvalid() {
        std::map<std::string,std::string> attributes;
        attributes["id"] = "foo";
        attributes["format"] = "bar";
        attributes["width"] = "40";
        attributes["height"] = "30";
        CPPUNIT_ASSERT_THROW(unmarshaller->unmarshal(attributes), std::runtime_error);
    }

    /**
     * Ensures `RenderbufferNodeUnmarshaller::unmarshal` works if _format_ is _red_.
     */
    void testUnmarshalWhenFormatIsRed() {

        // Make mape
        std::map<std::string,std::string> attributes;
        attributes["id"] = "foo";
        attributes["format"] = "red";
        attributes["width"] = "40";
        attributes["height"] = "30";

        // Unmarshal node
        RapidGL::Node* node = unmarshaller->unmarshal(attributes);
        const RapidGL::RenderbufferNode* renderbufferNode = dynamic_cast<RapidGL::RenderbufferNode*>(node);
        CPPUNIT_ASSERT(renderbufferNode != NULL);

        // Check value
        const Gloop::RenderbufferObject rbo = renderbufferNode->getRenderbufferObject();
        renderbuffer.bind(rbo);
        CPPUNIT_ASSERT(isRed(renderbuffer.internalFormat()));
        renderbuffer.unbind();
    }

    /**
     * Ensures `RenderbufferNodeUnmarshaller::unmarshal` works if _format_ is _rg_.
     */
    void testUnmarshalWhenFormatIsRg() {

        // Make mape
        std::map<std::string,std::string> attributes;
        attributes["id"] = "foo";
        attributes["format"] = "rg";
        attributes["width"] = "40";
        attributes["height"] = "30";

        // Unmarshal node
        RapidGL::Node* node = unmarshaller->unmarshal(attributes);
        const RapidGL::RenderbufferNode* renderbufferNode = dynamic_cast<RapidGL::RenderbufferNode*>(node);
        CPPUNIT_ASSERT(renderbufferNode != NULL);

        // Check value
        const Gloop::RenderbufferObject rbo = renderbufferNode->getRenderbufferObject();
        renderbuffer.bind(rbo);
        CPPUNIT_ASSERT(isRedGreen(renderbuffer.internalFormat()));
        renderbuffer.unbind();
    }

    /**
     * Ensures `RenderbufferNodeUnmarshaller::unmarshal` works if _format_ is _rgb_.
     */
    void testUnmarshalWhenFormatIsRgb() {

        // Make mape
        std::map<std::string,std::string> attributes;
        attributes["id"] = "foo";
        attributes["format"] = "rgb";
        attributes["width"] = "40";
        attributes["height"] = "30";

        // Unmarshal node
        RapidGL::Node* node = unmarshaller->unmarshal(attributes);
        const RapidGL::RenderbufferNode* renderbufferNode = dynamic_cast<RapidGL::RenderbufferNode*>(node);
        CPPUNIT_ASSERT(renderbufferNode != NULL);

        // Check value
        const Gloop::RenderbufferObject rbo = renderbufferNode->getRenderbufferObject();
        renderbuffer.bind(rbo);
        CPPUNIT_ASSERT(isRedGreenBlue(renderbuffer.internalFormat()));
        renderbuffer.unbind();
    }

    /**
     * Ensures `RenderbufferNodeUnmarshaller::unmarshal` works if _format_ is _rgba_.
     */
    void testUnmarshalWhenFormatIsRgba() {

        // Make mape
        std::map<std::string,std::string> attributes;
        attributes["id"] = "foo";
        attributes["format"] = "rgba";
        attributes["width"] = "40";
        attributes["height"] = "30";

        // Unmarshal node
        RapidGL::Node* node = unmarshaller->unmarshal(attributes);
        const RapidGL::RenderbufferNode* renderbufferNode = dynamic_cast<RapidGL::RenderbufferNode*>(node);
        CPPUNIT_ASSERT(renderbufferNode != NULL);

        // Check value
        const Gloop::RenderbufferObject rbo = renderbufferNode->getRenderbufferObject();
        renderbuffer.bind(rbo);
        CPPUNIT_ASSERT(isRedGreenBlueAlpha(renderbuffer.internalFormat()));
        renderbuffer.unbind();
    }

    /**
     * Ensures `RenderbufferNodeUnmarshaller::unmarshal` throws if _height_ is empty.
     */
    void testUnmarshalWhenHeightIsEmpty() {
        std::map<std::string,std::string> attributes;
        attributes["id"] = "foo";
        attributes["format"] = "red";
        attributes["width"] = "40";
        attributes["height"] = "";
        CPPUNIT_ASSERT_THROW(unmarshaller->unmarshal(attributes), std::runtime_error);
    }

    /**
     * Ensures `RenderbufferNodeUnmarshaller::unmarshal` works when _height_ is one.
     */
    void testUnmarshalWhenHeightIsOne() {

        // Make map
        std::map<std::string,std::string> attributes;
        attributes["id"] = "foo";
        attributes["format"] = "red";
        attributes["width"] = "8";
        attributes["height"] = "1";

        // Unmarshal node
        RapidGL::Node* node = unmarshaller->unmarshal(attributes);
        const RapidGL::RenderbufferNode* renderbufferNode = dynamic_cast<RapidGL::RenderbufferNode*>(node);
        CPPUNIT_ASSERT(renderbufferNode != NULL);

        // Check width
        const Gloop::RenderbufferObject rbo = renderbufferNode->getRenderbufferObject();
        renderbuffer.bind(rbo);
        CPPUNIT_ASSERT_EQUAL(1, renderbuffer.height());
        renderbuffer.unbind();
    }

    /**
     * Ensures `RenderbufferNodeUnmarshaller::unmarshal` throws if _height_ is zero.
     */
    void testUnmarshalWhenHeightIsZero() {
        std::map<std::string,std::string> attributes;
        attributes["id"] = "foo";
        attributes["format"] = "red";
        attributes["width"] = "1";
        attributes["height"] = "0";
        CPPUNIT_ASSERT_THROW(unmarshaller->unmarshal(attributes), std::runtime_error);
    }

    /**
     * Ensures `RenderbufferNodeUnmarshaller::unmarshal` throws if _id_ is empty.
     */
    void testUnmarshalWhenIdIsEmpty() {
        std::map<std::string,std::string> attributes;
        attributes["id"] = "";
        attributes["format"] = "red";
        attributes["width"] = "40";
        attributes["height"] = "30";
        CPPUNIT_ASSERT_THROW(unmarshaller->unmarshal(attributes), std::runtime_error);
    }

    /**
     * Ensures `RenderbufferNodeUnmarshaller::unmarshal` throws if _width_ is empty.
     */
    void testUnmarshalWhenWidthIsEmpty() {
        std::map<std::string,std::string> attributes;
        attributes["id"] = "foo";
        attributes["format"] = "red";
        attributes["width"] = "";
        attributes["height"] = "30";
        CPPUNIT_ASSERT_THROW(unmarshaller->unmarshal(attributes), std::runtime_error);
    }

    /**
     * Ensures `RenderbufferNodeUnmarshaller::unmarshal` works when _width_ is one.
     */
    void testUnmarshalWhenWidthIsOne() {

        // Make map
        std::map<std::string,std::string> attributes;
        attributes["id"] = "foo";
        attributes["format"] = "red";
        attributes["width"] = "1";
        attributes["height"] = "8";

        // Unmarshal node
        RapidGL::Node* node = unmarshaller->unmarshal(attributes);
        const RapidGL::RenderbufferNode* renderbufferNode = dynamic_cast<RapidGL::RenderbufferNode*>(node);
        CPPUNIT_ASSERT(renderbufferNode != NULL);

        // Check width
        const Gloop::RenderbufferObject rbo = renderbufferNode->getRenderbufferObject();
        renderbuffer.bind(rbo);
        CPPUNIT_ASSERT_EQUAL(1, renderbuffer.width());
        renderbuffer.unbind();
    }

    /**
     * Ensures `RenderbufferNodeUnmarshaller::unmarshal` throws if _width_ is zero.
     */
    void testUnmarshalWhenWidthIsZero() {
        std::map<std::string,std::string> attributes;
        attributes["id"] = "foo";
        attributes["format"] = "red";
        attributes["width"] = "0";
        attributes["height"] = "1";
        CPPUNIT_ASSERT_THROW(unmarshaller->unmarshal(attributes), std::runtime_error);
    }
};

int main(int argc, char* argv[]) {

    // Initialize
    if (!glfwInit()) {
        throw std::runtime_error("Could not initialize GLFW!");
    }

    // Open window
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 2);
    glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    if (!glfwOpenWindow(512, 512, 0, 0, 0, 0, 0, 0, GLFW_WINDOW)) {
        throw std::runtime_error("Could not open window!");
    }

    // Run test
    try {
        RenderbufferNodeUnmarshallerTest test;
        test.testUnmarshalWhenFormatIsDepth();
        test.testUnmarshalWhenFormatIsEmpty();
        test.testUnmarshalWhenFormatIsInvalid();
        test.testUnmarshalWhenFormatIsRed();
        test.testUnmarshalWhenFormatIsRg();
        test.testUnmarshalWhenFormatIsRgb();
        test.testUnmarshalWhenFormatIsRgba();
        test.testUnmarshalWhenHeightIsEmpty();
        test.testUnmarshalWhenHeightIsOne();
        test.testUnmarshalWhenHeightIsZero();
        test.testUnmarshalWhenIdIsEmpty();
        test.testUnmarshalWhenWidthIsEmpty();
        test.testUnmarshalWhenWidthIsOne();
        test.testUnmarshalWhenWidthIsZero();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        throw;
    }

    // Exit
    glfwTerminate();
    return 0;
}
