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
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/ui/text/TestRunner.h>
#include "RapidGL/CullNode.hxx"
#include "RapidGL/CullNodeUnmarshaller.hxx"
#include "RapidGL/Node.hxx"


/**
 * Unit test for `CullNodeUnmarshaller`.
 */
class CullNodeUnmarshallerTest : public CppUnit::TestFixture {
public:

    // Instance to use for testing
    RapidGL::CullNodeUnmarshaller unmarshaller;

    /**
     * Ensures `CullNodeUnmarshaller::unmarshal` works when mode is _back_.
     */
    void testUnmarshalWhenModeIsBack() {

        // Make map
        std::map<std::string,std::string> attributes;
        attributes["mode"] = "back";

        // Unmarshal
        const RapidGL::Node* node = unmarshaller.unmarshal(attributes);
        const RapidGL::CullNode* cullNode = dynamic_cast<const RapidGL::CullNode*>(node);
        CPPUNIT_ASSERT(cullNode != NULL);

        // Check mode
        CPPUNIT_ASSERT_EQUAL((GLenum) GL_BACK, cullNode->getMode());
    }

    /**
     * Ensures `CullNodeUnmarshaller::unmarshal` works when mode is _both_.
     */
    void testUnmarshalWhenModeIsBoth() {

        // Make map
        std::map<std::string,std::string> attributes;
        attributes["mode"] = "both";

        // Unmarshal
        const RapidGL::Node* node = unmarshaller.unmarshal(attributes);
        const RapidGL::CullNode* cullNode = dynamic_cast<const RapidGL::CullNode*>(node);
        CPPUNIT_ASSERT(cullNode != NULL);

        // Check mode
        CPPUNIT_ASSERT_EQUAL((GLenum) GL_FRONT_AND_BACK, cullNode->getMode());
    }

    /**
     * Ensures `CullNodeUnmarshaller::unmarshal` throws when _mode_ is the empty string.
     */
    void testUnmarshalWhenModeIsEmptyString() {
        std::map<std::string,std::string> attributes;
        attributes["mode"] = "";
        CPPUNIT_ASSERT_THROW(unmarshaller.unmarshal(attributes), std::runtime_error);
    }

    /**
     * Ensures `CullNodeUnmarshaller::unmarshal` works when mode is _front_.
     */
    void testUnmarshalWhenModeIsFront() {

        // Make map
        std::map<std::string,std::string> attributes;
        attributes["mode"] = "front";

        // Unmarshal
        const RapidGL::Node* node = unmarshaller.unmarshal(attributes);
        const RapidGL::CullNode* cullNode = dynamic_cast<const RapidGL::CullNode*>(node);
        CPPUNIT_ASSERT(cullNode != NULL);

        // Check mode
        CPPUNIT_ASSERT_EQUAL((GLenum) GL_FRONT, cullNode->getMode());
    }

    /**
     * Ensures `CullNodeUnmarshaller::unmarshal` throws when _mode_ is invalid.
     */
    void testUnmarshalWhenModeIsInvalid() {
        std::map<std::string,std::string> attributes;
        attributes["mode"] = "foo";
        CPPUNIT_ASSERT_THROW(unmarshaller.unmarshal(attributes), std::runtime_error);
    }

    /**
     * Ensures `CullNodeUnmarshaller::unmarshal` works when mode is _none_.
     */
    void testUnmarshalWhenModeIsNone() {

        // Make map
        std::map<std::string,std::string> attributes;
        attributes["mode"] = "none";

        // Unmarshal
        const RapidGL::Node* node = unmarshaller.unmarshal(attributes);
        const RapidGL::CullNode* cullNode = dynamic_cast<const RapidGL::CullNode*>(node);
        CPPUNIT_ASSERT(cullNode != NULL);

        // Check mode
        CPPUNIT_ASSERT_EQUAL((GLenum) GL_NONE, cullNode->getMode());
    }

    /**
     * Ensures `CullNodeUnmarshaller::unmarshal` throws when the map is empty.
     */
    void testUnmarshalWithEmptyMap() {
        std::map<std::string,std::string> attributes;
        CPPUNIT_ASSERT_THROW(unmarshaller.unmarshal(attributes), std::runtime_error);
    }

    CPPUNIT_TEST_SUITE(CullNodeUnmarshallerTest);
    CPPUNIT_TEST(testUnmarshalWhenModeIsBack);
    CPPUNIT_TEST(testUnmarshalWhenModeIsBoth);
    CPPUNIT_TEST(testUnmarshalWhenModeIsEmptyString);
    CPPUNIT_TEST(testUnmarshalWhenModeIsFront);
    CPPUNIT_TEST(testUnmarshalWhenModeIsInvalid);
    CPPUNIT_TEST(testUnmarshalWhenModeIsNone);
    CPPUNIT_TEST(testUnmarshalWithEmptyMap);
    CPPUNIT_TEST_SUITE_END();
};

int main(int argc, char* argv[]) {
    CppUnit::TextUi::TestRunner runner;
    runner.addTest(CullNodeUnmarshallerTest::suite());
    runner.run();
    return 0;
}
