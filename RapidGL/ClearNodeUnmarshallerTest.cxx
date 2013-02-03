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
     * Ensures ClearNodeUnmarshaller::unmarshal works correctly.
     */
    void testUnmarshal() {

        // Make a map of attributes
        map<string,string> attributes;
        attributes["red"] = "0.1";
        attributes["green"] = "0.2";
        attributes["blue"] = "0.3";
        attributes["alpha"] = "0.4";

        // Unmarshal the node
        const RapidGL::Node* node = unmarshaller->unmarshal(attributes);
        const RapidGL::ClearNode* clearNode = dynamic_cast<const RapidGL::ClearNode*>(node);
        CPPUNIT_ASSERT(clearNode != NULL);

        // Check values
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.1f, clearNode->getRed(), TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.2f, clearNode->getGreen(), TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.3f, clearNode->getBlue(), TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.4f, clearNode->getAlpha(), TOLERANCE);
    }

    /**
     * Ensures `ClearNodeUnmarshaller::unmarshal` throws if given an invalid _alpha_ value.
     */
    void testUnmarshalWithInvalidAlpha() {
        map<string,string> attributes;
        attributes["alpha"] = "foo";
        CPPUNIT_ASSERT_THROW(unmarshaller->unmarshal(attributes), std::runtime_error);
    }

    /**
     * Ensures `ClearNodeUnmarshaller::unmarshal` throws if given an invalid _blue_ value.
     */
    void testUnmarshalWithInvalidBlue() {
        map<string,string> attributes;
        attributes["blue"] = "foo";
        CPPUNIT_ASSERT_THROW(unmarshaller->unmarshal(attributes), std::runtime_error);
    }

    /**
     * Ensures `ClearNodeUnmarshaller::unmarshal` throws if given an invalid _green_ value.
     */
    void testUnmarshalWithInvalidGreen() {
        map<string,string> attributes;
        attributes["green"] = "foo";
        CPPUNIT_ASSERT_THROW(unmarshaller->unmarshal(attributes), std::runtime_error);
    }

    /**
     * Ensures `ClearNodeUnmarshaller::unmarshal` throws if given an invalid _red_ value.
     */
    void testUnmarshalWithInvalidRed() {
        map<string,string> attributes;
        attributes["red"] = "foo";
        CPPUNIT_ASSERT_THROW(unmarshaller->unmarshal(attributes), std::runtime_error);
    }

    CPPUNIT_TEST_SUITE(ClearNodeUnmarshallerTest);
    CPPUNIT_TEST(testUnmarshal);
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
