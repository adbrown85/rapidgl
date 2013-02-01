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
#include <stdexcept>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/ui/text/TestRunner.h>
#include "RapidGL/Node.h"
#include "RapidGL/DepthFunctionNode.h"
#include "RapidGL/DepthFunctionNodeUnmarshaller.h"
#include "RapidGL/Unmarshaller.h"


/**
 * Unit test for `DepthFunctionNodeUnmarshaller`.
 */
class DepthFunctionNodeUnmarshallerTest : public CppUnit::TestFixture {
public:

    // Instance to use
    RapidGL::Unmarshaller* const unmarshaller;

    /**
     * Constructs the test.
     */
    DepthFunctionNodeUnmarshallerTest() : unmarshaller(new RapidGL::DepthFunctionNodeUnmarshaller()) {
        // empty
    }

    /**
     * Ensures `DepthFunctionNodeUnmarshaller::unmarshal` throws when _function_ is empty.
     */
    void testUnmarshalWhenFunctionIsEmpty() {
        std::map<std::string,std::string> attributes;
        attributes["function"] = "";
        CPPUNIT_ASSERT_THROW(unmarshaller->unmarshal(attributes), std::runtime_error);
    }

    /**
     * Ensures `DepthFunctionNodeUnmarshaller::unmarshal` throws when _function_ is invalid.
     */
    void testUnmarshalWhenFunctionIsInvalid() {
        std::map<std::string,std::string> attributes;
        attributes["function"] = "foo";
        CPPUNIT_ASSERT_THROW(unmarshaller->unmarshal(attributes), std::runtime_error);
    }

    /**
     * Ensures `DepthFunctionNodeUnmarshaller::unmarshal` throws when _function_ is missing.
     */
    void testUnmarshalWhenFunctionIsMissing() {
        std::map<std::string,std::string> attributes;
        CPPUNIT_ASSERT_THROW(unmarshaller->unmarshal(attributes), std::runtime_error);
    }

    /**
     * Ensures `DepthFunctionNodeUnmarshaller::unmarshal` works with _always_.
     */
    void testUnmarshalWithAlways() {

        // Make map
        std::map<std::string,std::string> attributes;
        attributes["function"] = "always";

        // Unmarshal node
        RapidGL::Node* node = unmarshaller->unmarshal(attributes);
        const RapidGL::DepthFunctionNode* depthFunctionNode = dynamic_cast<RapidGL::DepthFunctionNode*>(node);
        CPPUNIT_ASSERT(depthFunctionNode != NULL);

        // Check function
        CPPUNIT_ASSERT_EQUAL((GLenum) GL_ALWAYS, depthFunctionNode->getFunction());
    }

    /**
     * Ensures `DepthFunctionNodeUnmarshaller::unmarshal` works with _equal_.
     */
    void testUnmarshalWithEqual() {

        // Make map
        std::map<std::string,std::string> attributes;
        attributes["function"] = "equal";

        // Unmarshal node
        RapidGL::Node* node = unmarshaller->unmarshal(attributes);
        const RapidGL::DepthFunctionNode* depthFunctionNode = dynamic_cast<RapidGL::DepthFunctionNode*>(node);
        CPPUNIT_ASSERT(depthFunctionNode != NULL);

        // Check function
        CPPUNIT_ASSERT_EQUAL((GLenum) GL_EQUAL, depthFunctionNode->getFunction());
    }

    /**
     * Ensures `DepthFunctionNodeUnmarshaller::unmarshal` works with _gequal_.
     */
    void testUnmarshalWithGequal() {

        // Make map
        std::map<std::string,std::string> attributes;
        attributes["function"] = "gequal";

        // Unmarshal node
        RapidGL::Node* node = unmarshaller->unmarshal(attributes);
        const RapidGL::DepthFunctionNode* depthFunctionNode = dynamic_cast<RapidGL::DepthFunctionNode*>(node);
        CPPUNIT_ASSERT(depthFunctionNode != NULL);

        // Check function
        CPPUNIT_ASSERT_EQUAL((GLenum) GL_GEQUAL, depthFunctionNode->getFunction());
    }

    /**
     * Ensures `DepthFunctionNodeUnmarshaller::unmarshal` works with _greater_.
     */
    void testUnmarshalWithGreater() {

        // Make map
        std::map<std::string,std::string> attributes;
        attributes["function"] = "greater";

        // Unmarshal node
        RapidGL::Node* node = unmarshaller->unmarshal(attributes);
        const RapidGL::DepthFunctionNode* depthFunctionNode = dynamic_cast<RapidGL::DepthFunctionNode*>(node);
        CPPUNIT_ASSERT(depthFunctionNode != NULL);

        // Check function
        CPPUNIT_ASSERT_EQUAL((GLenum) GL_GREATER, depthFunctionNode->getFunction());
    }

    /**
     * Ensures `DepthFunctionNodeUnmarshaller::unmarshal` works with _lequal_.
     */
    void testUnmarshalWithLequal() {

        // Make map
        std::map<std::string,std::string> attributes;
        attributes["function"] = "lequal";

        // Unmarshal node
        RapidGL::Node* node = unmarshaller->unmarshal(attributes);
        const RapidGL::DepthFunctionNode* depthFunctionNode = dynamic_cast<RapidGL::DepthFunctionNode*>(node);
        CPPUNIT_ASSERT(depthFunctionNode != NULL);

        // Check function
        CPPUNIT_ASSERT_EQUAL((GLenum) GL_LEQUAL, depthFunctionNode->getFunction());
    }

    /**
     * Ensures `DepthFunctionNodeUnmarshaller::unmarshal` works with _less_.
     */
    void testUnmarshalWithLess() {

        // Make map
        std::map<std::string,std::string> attributes;
        attributes["function"] = "less";

        // Unmarshal node
        RapidGL::Node* node = unmarshaller->unmarshal(attributes);
        const RapidGL::DepthFunctionNode* depthFunctionNode = dynamic_cast<RapidGL::DepthFunctionNode*>(node);
        CPPUNIT_ASSERT(depthFunctionNode != NULL);

        // Check function
        CPPUNIT_ASSERT_EQUAL((GLenum) GL_LESS, depthFunctionNode->getFunction());
    }

    /**
     * Ensures `DepthFunctionNodeUnmarshaller::unmarshal` works with _never_.
     */
    void testUnmarshalWithNever() {

        // Make map
        std::map<std::string,std::string> attributes;
        attributes["function"] = "never";

        // Unmarshal node
        RapidGL::Node* node = unmarshaller->unmarshal(attributes);
        const RapidGL::DepthFunctionNode* depthFunctionNode = dynamic_cast<RapidGL::DepthFunctionNode*>(node);
        CPPUNIT_ASSERT(depthFunctionNode != NULL);

        // Check function
        CPPUNIT_ASSERT_EQUAL((GLenum) GL_NEVER, depthFunctionNode->getFunction());
    }

    /**
     * Ensures `DepthFunctionNodeUnmarshaller::unmarshal` works with _notequal_.
     */
    void testUnmarshalWithNotEqual() {

        // Make map
        std::map<std::string,std::string> attributes;
        attributes["function"] = "notequal";

        // Unmarshal node
        RapidGL::Node* node = unmarshaller->unmarshal(attributes);
        const RapidGL::DepthFunctionNode* depthFunctionNode = dynamic_cast<RapidGL::DepthFunctionNode*>(node);
        CPPUNIT_ASSERT(depthFunctionNode != NULL);

        // Check function
        CPPUNIT_ASSERT_EQUAL((GLenum) GL_NOTEQUAL, depthFunctionNode->getFunction());
    }

    CPPUNIT_TEST_SUITE(DepthFunctionNodeUnmarshallerTest);
    CPPUNIT_TEST(testUnmarshalWhenFunctionIsEmpty);
    CPPUNIT_TEST(testUnmarshalWhenFunctionIsInvalid);
    CPPUNIT_TEST(testUnmarshalWhenFunctionIsMissing);
    CPPUNIT_TEST(testUnmarshalWithAlways);
    CPPUNIT_TEST(testUnmarshalWithEqual);
    CPPUNIT_TEST(testUnmarshalWithGequal);
    CPPUNIT_TEST(testUnmarshalWithGreater);
    CPPUNIT_TEST(testUnmarshalWithLequal);
    CPPUNIT_TEST(testUnmarshalWithLess);
    CPPUNIT_TEST(testUnmarshalWithNever);
    CPPUNIT_TEST(testUnmarshalWithNotEqual);
    CPPUNIT_TEST_SUITE_END();
};

int main(int argc, char* argv[]) {
    CppUnit::TextUi::TestRunner runner;
    runner.addTest(DepthFunctionNodeUnmarshallerTest::suite());
    runner.run();
    return 0;
}
