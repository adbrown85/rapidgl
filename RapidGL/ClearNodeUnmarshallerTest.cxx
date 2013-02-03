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
#include <map>
#include <string>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/ui/text/TestRunner.h>
#include <glycerin/Color.hxx>
#include "RapidGL/ClearNode.h"
#include "RapidGL/ClearNodeUnmarshaller.h"
#include "RapidGL/Node.h"
#include "RapidGL/Unmarshaller.h"
using namespace std;


/**
 * Unit test for ClearNodeUnmarshaller.
 */
class ClearNodeUnmarshallerTest : public CppUnit::TestFixture {
public:

    // Threshold for floating-point comparisons
    const static GLfloat TOLERANCE = 1e-6f;

    // Unmarshaller to use for testing
    RapidGL::Unmarshaller* const unmarshaller;

    /**
     * Constructs a ClearNodeUnmarshallerTest.
     */
    ClearNodeUnmarshallerTest() : unmarshaller(new RapidGL::ClearNodeUnmarshaller()) {
        // empty
    }

    /**
     * Ensures `ClearNodeUnmarshaller::unmarshal` works with a _color_ value.
     */
    void testUnmarshalWithColor() {

        // Make a map of attributes
        map<string,string> attributes;
        attributes["color"] = "0.1 0.2 0.3 0.4";

        // Unmarshal the node
        const RapidGL::Node* node = unmarshaller->unmarshal(attributes);
        const RapidGL::ClearNode* clearNode = dynamic_cast<const RapidGL::ClearNode*>(node);
        CPPUNIT_ASSERT(clearNode != NULL);

        // Check mask
        CPPUNIT_ASSERT_EQUAL((GLbitfield) GL_COLOR_BUFFER_BIT, clearNode->getMask());

        // Check color
        const Glycerin::Color color = clearNode->getColor();
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.1f, color.r, TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.2f, color.g, TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.3f, color.b, TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.4f, color.a, TOLERANCE);
    }

    /**
     * Ensures `ClearNodeUnmarshaller::unmarshal` works with both _color_ and _depth_ values.
     */
    void testUnmarshalWithColorAndDepth() {

        // Make a map of attributes
        map<string,string> attributes;
        attributes["color"] = "0.1 0.2 0.3 0.4";
        attributes["depth"] = "0.5";

        // Unmarshal the node
        const RapidGL::Node* node = unmarshaller->unmarshal(attributes);
        const RapidGL::ClearNode* clearNode = dynamic_cast<const RapidGL::ClearNode*>(node);
        CPPUNIT_ASSERT(clearNode != NULL);

        // Check mask
        CPPUNIT_ASSERT_EQUAL((GLbitfield) GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT, clearNode->getMask());

        // Check color
        const Glycerin::Color color = clearNode->getColor();
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.1f, color.r, TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.2f, color.g, TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.3f, color.b, TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.4f, color.a, TOLERANCE);

        // Check depth
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.5f, clearNode->getDepth(), TOLERANCE);
    }

    /**
     * Ensures `ClearNodeUnmarshaller::unmarshal` works with a _depth_ value.
     */
    void testUnmarshalWithDepth() {

        // Make a map of attributes
        map<string,string> attributes;
        attributes["depth"] = "0.5";

        // Unmarshal the node
        const RapidGL::Node* node = unmarshaller->unmarshal(attributes);
        const RapidGL::ClearNode* clearNode = dynamic_cast<const RapidGL::ClearNode*>(node);
        CPPUNIT_ASSERT(clearNode != NULL);

        // Check mask
        CPPUNIT_ASSERT_EQUAL((GLbitfield) GL_DEPTH_BUFFER_BIT, clearNode->getMask());

        // Check depth
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.5f, clearNode->getDepth(), TOLERANCE);
    }

    /**
     * Ensures `ClearNodeUnmarshaller::unmarshal` throws if given an invalid _alpha_ value.
     */
    void testUnmarshalWithInvalidAlpha() {
        map<string,string> attributes;
        attributes["color"] = "0.0 0.0 0.0 foo";
        CPPUNIT_ASSERT_THROW(unmarshaller->unmarshal(attributes), std::runtime_error);
    }

    /**
     * Ensures `ClearNodeUnmarshaller::unmarshal` throws if given an invalid _blue_ value.
     */
    void testUnmarshalWithInvalidBlue() {
        map<string,string> attributes;
        attributes["color"] = "0.0 0.0 foo 0.0";
        CPPUNIT_ASSERT_THROW(unmarshaller->unmarshal(attributes), std::runtime_error);
    }

    /**
     * Ensures `ClearNodeUnmarshaller::unmarshal` throws if given an invalid _green_ value.
     */
    void testUnmarshalWithInvalidGreen() {
        map<string,string> attributes;
        attributes["color"] = "0.0 foo 0.0 0.0";
        CPPUNIT_ASSERT_THROW(unmarshaller->unmarshal(attributes), std::runtime_error);
    }

    /**
     * Ensures `ClearNodeUnmarshaller::unmarshal` throws if given an invalid _red_ value.
     */
    void testUnmarshalWithInvalidRed() {
        map<string,string> attributes;
        attributes["color"] = "foo 0.0 0.0 0.0";
        CPPUNIT_ASSERT_THROW(unmarshaller->unmarshal(attributes), std::runtime_error);
    }

    CPPUNIT_TEST_SUITE(ClearNodeUnmarshallerTest);
    CPPUNIT_TEST(testUnmarshalWithColor);
    CPPUNIT_TEST(testUnmarshalWithColorAndDepth);
    CPPUNIT_TEST(testUnmarshalWithDepth);
    CPPUNIT_TEST(testUnmarshalWithInvalidAlpha);
    CPPUNIT_TEST(testUnmarshalWithInvalidBlue);
    CPPUNIT_TEST(testUnmarshalWithInvalidGreen);
    CPPUNIT_TEST(testUnmarshalWithInvalidRed);
    CPPUNIT_TEST_SUITE_END();
};

int main(int argc, char* argv[]) {
    CppUnit::TextUi::TestRunner runner;
    runner.addTest(ClearNodeUnmarshallerTest::suite());
    runner.run();
    return 0;
}
