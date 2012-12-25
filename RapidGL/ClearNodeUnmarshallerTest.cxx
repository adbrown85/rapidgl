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
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/ui/text/TestRunner.h>
#include <map>
#include <string>
#include "RapidGL/ClearNode.hxx"
#include "RapidGL/ClearNodeUnmarshaller.hxx"
#include "RapidGL/Node.hxx"
#include "RapidGL/Unmarshaller.hxx"
using namespace std;


/**
 * Unit test for ClearNodeUnmarshaller.
 */
class ClearNodeUnmarshallerTest : public CppUnit::TestFixture {
public:

    // Threshold for floating-point comparisons
    const static GLfloat TOLERANCE = 1e-6f;

    // Unmarshaller to use for testing
    RapidGL::Unmarshaller* unmarshaller;

    /**
     * Constructs a ClearNodeUnmarshallerTest.
     */
    ClearNodeUnmarshallerTest() {
        this->unmarshaller = new RapidGL::ClearNodeUnmarshaller();
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
        RapidGL::ClearNode* node = (RapidGL::ClearNode*) unmarshaller->unmarshal(attributes);

        // Check values
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.1f, node->getRed(), TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.2f, node->getGreen(), TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.3f, node->getBlue(), TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.4f, node->getAlpha(), TOLERANCE);
    }

    CPPUNIT_TEST_SUITE(ClearNodeUnmarshallerTest);
    CPPUNIT_TEST(testUnmarshal);
    CPPUNIT_TEST_SUITE_END();
};

int main(int argc, char* argv[]) {
    CppUnit::TextUi::TestRunner runner;
    runner.addTest(ClearNodeUnmarshallerTest::suite());
    runner.run();
    return 0;
}
