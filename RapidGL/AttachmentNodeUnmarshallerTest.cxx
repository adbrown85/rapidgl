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
#include "RapidGL/AttachmentNodeUnmarshaller.hxx"
#include "RapidGL/Node.hxx"
#include "RapidGL/TextureAttachmentNode.hxx"


/**
 * Unit test for `AttachmentNodeUnmarshaller`.
 */
class AttachmentNodeUnmarshallerTest {
public:

    // Instance to use for testing
    RapidGL::AttachmentNodeUnmarshaller unmarshaller;

    /**
     * Ensures `AttachmentNodeUnmarshaller::unmarshal` throws when _type_ is the empty string.
     */
    void testUnmarshalWhenTypeIsEmpty() {
        std::map<std::string,std::string> attributes;
        attributes["type"] = "";
        CPPUNIT_ASSERT_THROW(unmarshaller.unmarshal(attributes), std::runtime_error);
    }

    /**
     * Ensures `AttachmentNodeUnmarshaller::unmarshal` throws when _type_ is _foo_.
     */
    void testUnmarshalWhenTypeIsFoo() {
        std::map<std::string,std::string> attributes;
        attributes["type"] = "foo";
        CPPUNIT_ASSERT_THROW(unmarshaller.unmarshal(attributes), std::runtime_error);
    }

    /**
     * Ensures `AttachmentNodeUnmarshaller::unmarshal` works when _type_ is _texture_ and _usage_ is _color_.
     */
    void testUnmarshalWhenTypeIsTextureAndUsageIsColor() {

        // Make map
        std::map<std::string,std::string> attributes;
        attributes["type"] = "texture";
        attributes["link"] = "foo";
        attributes["usage"] = "color";

        // Unmarshal
        RapidGL::Node* node = unmarshaller.unmarshal(attributes);
        CPPUNIT_ASSERT(node != NULL);
        RapidGL::TextureAttachmentNode* attachmentNode = dynamic_cast<RapidGL::TextureAttachmentNode*>(node);
        CPPUNIT_ASSERT(attachmentNode != NULL);

        // Check fields
        CPPUNIT_ASSERT_EQUAL(std::string("foo"), attachmentNode->getLink());
        CPPUNIT_ASSERT_EQUAL(RapidGL::AttachmentNode::COLOR, attachmentNode->getUsage());
    }

    /**
     * Ensures `AttachmentNodeUnmarshaller::unmarshal` works when _type_ is _texture_ and _usage_ is _depth_.
     */
    void testUnmarshalWhenTypeIsTextureAndUsageIsDepth() {

        // Make map
        std::map<std::string,std::string> attributes;
        attributes["type"] = "texture";
        attributes["link"] = "foo";
        attributes["usage"] = "depth";

        // Unmarshal
        RapidGL::Node* node = unmarshaller.unmarshal(attributes);
        CPPUNIT_ASSERT(node != NULL);
        RapidGL::TextureAttachmentNode* attachmentNode = dynamic_cast<RapidGL::TextureAttachmentNode*>(node);
        CPPUNIT_ASSERT(attachmentNode != NULL);

        // Check fields
        CPPUNIT_ASSERT_EQUAL(std::string("foo"), attachmentNode->getLink());
        CPPUNIT_ASSERT_EQUAL(RapidGL::AttachmentNode::DEPTH, attachmentNode->getUsage());
    }

    /**
     * Ensures `AttachmentNodeUnmarshaller::unmarshal` works when _type_ is _texture_ and _usage_ is _stencil_.
     */
    void testUnmarshalWhenTypeIsTextureAndUsageIsStencil() {

        // Make map
        std::map<std::string,std::string> attributes;
        attributes["type"] = "texture";
        attributes["link"] = "foo";
        attributes["usage"] = "stencil";

        // Unmarshal
        RapidGL::Node* node = unmarshaller.unmarshal(attributes);
        CPPUNIT_ASSERT(node != NULL);
        RapidGL::TextureAttachmentNode* attachmentNode = dynamic_cast<RapidGL::TextureAttachmentNode*>(node);
        CPPUNIT_ASSERT(attachmentNode != NULL);

        // Check fields
        CPPUNIT_ASSERT_EQUAL(std::string("foo"), attachmentNode->getLink());
        CPPUNIT_ASSERT_EQUAL(RapidGL::AttachmentNode::STENCIL, attachmentNode->getUsage());
    }

    /**
     * Ensures `AttachmentNodeUnmarshaller::unmarshal` throws when _type_ is _texture_ but _link_ is absent.
     */
    void testUnmarshalWhenTypeIsTextureButLinkIsAbsent() {

        // Make map
        std::map<std::string,std::string> attributes;
        attributes["type"] = "texture";
        attributes["usage"] = "color";

        // Unmarshal
        CPPUNIT_ASSERT_THROW(unmarshaller.unmarshal(attributes), std::runtime_error);
    }

    /**
     * Ensures `AttachmentNodeUnmarshaller::unmarshal` throws when _type_ is _texture_ but _link_ is empty.
     */
    void testUnmarshalWhenTypeIsTextureButLinkIsEmpty() {

        // Make map
        std::map<std::string,std::string> attributes;
        attributes["type"] = "texture";
        attributes["link"] = "";
        attributes["usage"] = "color";

        // Unmarshal
        CPPUNIT_ASSERT_THROW(unmarshaller.unmarshal(attributes), std::runtime_error);
    }

    /**
     * Ensures `AttachmentNodeUnmarshaller::unmarshal` throws when _type_ is _texture_ but _usage_ is absent.
     */
    void testUnmarshalWhenTypeIsTextureButUsageIsAbsent() {

        // Make map
        std::map<std::string,std::string> attributes;
        attributes["type"] = "texture";
        attributes["link"] = "foo";

        // Unmarshal
        CPPUNIT_ASSERT_THROW(unmarshaller.unmarshal(attributes), std::runtime_error);
    }

    /**
     * Ensures `AttachmentNodeUnmarshaller::unmarshal` throws when _type_ is _texture_ but _usage_ is empty.
     */
    void testUnmarshalWhenTypeIsTextureButUsageIsEmpty() {

        // Make map
        std::map<std::string,std::string> attributes;
        attributes["type"] = "texture";
        attributes["link"] = "foo";
        attributes["usage"] = "";

        // Unmarshal
        CPPUNIT_ASSERT_THROW(unmarshaller.unmarshal(attributes), std::runtime_error);
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
        throw std::runtime_error("Could not open GLFW window!");
    }

    // Run test
    try {
        AttachmentNodeUnmarshallerTest test;
        test.testUnmarshalWhenTypeIsEmpty();
        test.testUnmarshalWhenTypeIsFoo();
        test.testUnmarshalWhenTypeIsTextureAndUsageIsColor();
        test.testUnmarshalWhenTypeIsTextureAndUsageIsDepth();
        test.testUnmarshalWhenTypeIsTextureAndUsageIsStencil();
        test.testUnmarshalWhenTypeIsTextureButLinkIsAbsent();
        test.testUnmarshalWhenTypeIsTextureButLinkIsEmpty();
        test.testUnmarshalWhenTypeIsTextureButUsageIsAbsent();
        test.testUnmarshalWhenTypeIsTextureButUsageIsEmpty();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        throw;
    }

    // Exit
    glfwTerminate();
    return 0;
}
