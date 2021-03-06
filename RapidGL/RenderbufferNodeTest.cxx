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
#include <stdexcept>
#include <cppunit/extensions/HelperMacros.h>
#include <GL/glfw.h>
#include <gloop/RenderbufferObject.hxx>
#include <gloop/RenderbufferTarget.hxx>
#include "RapidGL/RenderbufferNode.h"


/**
 * Unit test for `RenderbufferNode`.
 */
class RenderbufferNodeTest {
public:

    /**
     * Returns the maximum renderbuffer size.
     */
    static GLsizei getMaxRenderbufferSize() {
        GLint value;
        glGetIntegerv(GL_MAX_RENDERBUFFER_SIZE, &value);
        return value;
    }

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

    // Maximum renderbuffer size
    const GLsizei maxRenderbufferSize;

    // Renderbuffer target
    const Gloop::RenderbufferTarget renderbuffer;

    /**
     * Constructs the test.
     */
    RenderbufferNodeTest() : maxRenderbufferSize(getMaxRenderbufferSize()) {
        // empty
    }

    /**
     * Ensures constructor works when format is `GL_DEPTH_COMPONENT`.
     */
    void testRenderbufferNodeWhenFormatIsDepthComponent() {

        // Make node and get RBO
        const RapidGL::RenderbufferNode node("foo", GL_DEPTH_COMPONENT, 8, 8);
        const Gloop::RenderbufferObject rbo = node.getRenderbufferObject();

        // Check format
        renderbuffer.bind(rbo);
        CPPUNIT_ASSERT(isDepthComponent(renderbuffer.internalFormat()));
        renderbuffer.unbind();
    }

    /**
     * Ensures constructor works when format is `GL_RED`.
     */
    void testRenderbufferNodeWhenFormatIsRed() {

        // Make node and get RBO
        const RapidGL::RenderbufferNode node("foo", GL_RED, 8, 8);
        const Gloop::RenderbufferObject rbo = node.getRenderbufferObject();

        // Check format
        renderbuffer.bind(rbo);
        CPPUNIT_ASSERT(isRed(renderbuffer.internalFormat()));
        renderbuffer.unbind();
    }

    /**
     * Ensures constructor works when format is `GL_RG`.
     */
    void testRenderbufferNodeWhenFormatIsRg() {

        // Make node and get RBO
        const RapidGL::RenderbufferNode node("foo", GL_RG, 8, 8);
        const Gloop::RenderbufferObject rbo = node.getRenderbufferObject();

        // Check format
        renderbuffer.bind(rbo);
        CPPUNIT_ASSERT(isRedGreen(renderbuffer.internalFormat()));
        renderbuffer.unbind();
    }

    /**
     * Ensures constructor works when format is `GL_RGB`.
     */
    void testRenderbufferNodeWhenFormatIsRgb() {

        // Make node and get RBO
        const RapidGL::RenderbufferNode node("foo", GL_RGB, 8, 8);
        const Gloop::RenderbufferObject rbo = node.getRenderbufferObject();

        // Check format
        renderbuffer.bind(rbo);
        CPPUNIT_ASSERT(isRedGreenBlue(renderbuffer.internalFormat()));
        renderbuffer.unbind();
    }

    /**
     * Ensures constructor works when format is `GL_RGBA`.
     */
    void testRenderbufferNodeWhenFormatIsRgba() {

        // Make node and get RBO
        const RapidGL::RenderbufferNode node("foo", GL_RGBA, 8, 8);
        const Gloop::RenderbufferObject rbo = node.getRenderbufferObject();

        // Check format
        renderbuffer.bind(rbo);
        CPPUNIT_ASSERT(isRedGreenBlueAlpha(renderbuffer.internalFormat()));
        renderbuffer.unbind();
    }

    /**
     * Ensures constructor throws when format is invalid.
     */
    void testRenderbufferNodeWhenFormatIsInvalid() {
        CPPUNIT_ASSERT_THROW(RapidGL::RenderbufferNode("foo", GL_VERSION, 1, 1), std::invalid_argument);
    }

    /**
     * Ensures constructor works when it's passed a height equal to `GL_MAX_RENDERBUFFER_SIZE`.
     */
    void testRenderbufferNodeWhenHeightIsMax() {

        // Make node and get RBO
        const RapidGL::RenderbufferNode node("foo", GL_RGB, 1, maxRenderbufferSize);
        const Gloop::RenderbufferObject rbo = node.getRenderbufferObject();

        // Check width
        renderbuffer.bind(rbo);
        CPPUNIT_ASSERT_EQUAL((GLsizei) maxRenderbufferSize, renderbuffer.height());
        renderbuffer.unbind();
    }

    /**
     * Ensures constructor throws when it's passed a height greater than `GL_MAX_RENDERBUFFER_SIZE`.
     */
    void testRenderbufferNodeWhenHeightIsMaxPlusOne() {
        const GLsizei height = maxRenderbufferSize + 1;
        CPPUNIT_ASSERT_THROW(RapidGL::RenderbufferNode("foo", GL_RGB, 1, height), std::invalid_argument);
    }

    /**
     * Ensures constructor works when passed `1` for the height.
     */
    void testRenderbufferNodeWhenHeightIsOne() {

        // Make node and get RBO
        const RapidGL::RenderbufferNode node("foo", GL_RGBA, 8, 1);
        const Gloop::RenderbufferObject rbo = node.getRenderbufferObject();

        // Check format
        renderbuffer.bind(rbo);
        CPPUNIT_ASSERT_EQUAL((GLsizei) 1, renderbuffer.height());
        renderbuffer.unbind();
    }

    /**
     * Ensures constructor throws when it's passed a height of zero.
     */
    void testRenderbufferNodeWhenHeightIsZero() {
        CPPUNIT_ASSERT_THROW(RapidGL::RenderbufferNode("foo", GL_RGB, 512, 0), std::invalid_argument);
    }

    /**
     * Ensures constructor throws if passed an empty ID.
     */
    void testRenderbufferNodeWhenIdIsEmpty() {
        CPPUNIT_ASSERT_THROW(RapidGL::RenderbufferNode("", GL_RGB, 8, 8), std::invalid_argument);
    }

    /**
     * Ensures constructor works when it's passed _foo_.
     */
    void testRenderbufferNodeWhenIdIsFoo() {
        const RapidGL::RenderbufferNode node("foo", GL_RED, 1, 1);
        CPPUNIT_ASSERT_EQUAL(std::string("foo"), node.getId());
    }

    /**
     * Ensures constructor works when it's passed a width equal to `GL_MAX_RENDERBUFFER_SIZE`.
     */
    void testRenderbufferNodeWhenWidthIsMax() {

        // Make node and get RBO
        const RapidGL::RenderbufferNode node("foo", GL_RGB, maxRenderbufferSize, 1);
        const Gloop::RenderbufferObject rbo = node.getRenderbufferObject();

        // Check width
        renderbuffer.bind(rbo);
        CPPUNIT_ASSERT_EQUAL((GLsizei) maxRenderbufferSize, renderbuffer.width());
        renderbuffer.unbind();
    }

    /**
     * Ensures constructor throws when it's passed a width greater than `GL_MAX_RENDERBUFFER_SIZE`.
     */
    void testRenderbufferNodeWhenWidthIsMaxPlusOne() {
        const GLsizei width = maxRenderbufferSize + 1;
        CPPUNIT_ASSERT_THROW(RapidGL::RenderbufferNode("foo", GL_RGB, width, 1), std::invalid_argument);
    }

    /**
     * Ensures constructor works when passed `1` for the width.
     */
    void testRenderbufferNodeWhenWidthIsOne() {

        // Make node and get RBO
        const RapidGL::RenderbufferNode node("foo", GL_RGBA, 1, 8);
        const Gloop::RenderbufferObject rbo = node.getRenderbufferObject();

        // Check format
        renderbuffer.bind(rbo);
        CPPUNIT_ASSERT_EQUAL((GLsizei) 1, renderbuffer.width());
        renderbuffer.unbind();
    }

    /**
     * Ensures constructor throws when it's passed a width of zero.
     */
    void testRenderbufferNodeWhenWidthIsZero() {
        CPPUNIT_ASSERT_THROW(RapidGL::RenderbufferNode("foo", GL_RGB, 0, 512), std::invalid_argument);
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
        throw std::runtime_error("Could not open window!");
    }

    // Run test
    try {
        RenderbufferNodeTest test;
        test.testRenderbufferNodeWhenFormatIsDepthComponent();
        test.testRenderbufferNodeWhenFormatIsInvalid();
        test.testRenderbufferNodeWhenFormatIsRed();
        test.testRenderbufferNodeWhenFormatIsRg();
        test.testRenderbufferNodeWhenFormatIsRgb();
        test.testRenderbufferNodeWhenFormatIsRgba();
        test.testRenderbufferNodeWhenHeightIsMax();
        test.testRenderbufferNodeWhenHeightIsMaxPlusOne();
        test.testRenderbufferNodeWhenHeightIsOne();
        test.testRenderbufferNodeWhenHeightIsZero();
        test.testRenderbufferNodeWhenIdIsEmpty();
        test.testRenderbufferNodeWhenIdIsFoo();
        test.testRenderbufferNodeWhenWidthIsMax();
        test.testRenderbufferNodeWhenWidthIsMaxPlusOne();
        test.testRenderbufferNodeWhenWidthIsOne();
        test.testRenderbufferNodeWhenWidthIsZero();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        throw;
    }

    // Exit
    glfwTerminate();
    return 0;
}
