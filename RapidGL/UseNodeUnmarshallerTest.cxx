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
#include <map>
#include <stdexcept>
#include <string>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/ui/text/TestRunner.h>
#include "RapidGL/Node.h"
#include "RapidGL/Unmarshaller.h"
#include "RapidGL/UseNodeUnmarshaller.h"


/**
 * Unit test for `UseNodeUnmarshaller`.
 */
class UseNodeUnmarshallerTest : public CppUnit::TestFixture {
public:

    // Instance to use for testing
    RapidGL::Unmarshaller* const unmarshaller;

    /**
     * Constructs the test.
     */
    UseNodeUnmarshallerTest() : unmarshaller(new RapidGL::UseNodeUnmarshaller()) {
        // empty
    }

    /**
     * Ensures `UseNodeUnmarshaller::unmarshal` throws when given an empty _program_ attribute.
     */
    void testUnmarshalWithEmptyProgram() {
        std::map<std::string,std::string> attributes;
        attributes["program"] = "";
        CPPUNIT_ASSERT_THROW(unmarshaller->unmarshal(attributes), std::runtime_error);
    }

    /**
     * Ensures `UseNodeUnmarshaller::unmarshal` works when given a valid _program_ attribute.
     */
    void testUnmarshalWithProgram() {
        std::map<std::string,std::string> attributes;
        attributes["program"] = "foo";
        RapidGL::Node* node = unmarshaller->unmarshal(attributes);
        RapidGL::UseNode* useNode = dynamic_cast<RapidGL::UseNode*>(node);
        CPPUNIT_ASSERT(useNode != NULL);
    }

    /**
     * Ensures `UseNodeUnmarshaller::unmarshal` throws when _program_ attribute is missing.
     */
    void testUnmarshalWithoutProgram() {
        std::map<std::string,std::string> attributes;
        CPPUNIT_ASSERT_THROW(unmarshaller->unmarshal(attributes), std::runtime_error);
    }

    CPPUNIT_TEST_SUITE(UseNodeUnmarshallerTest);
    CPPUNIT_TEST(testUnmarshalWithEmptyProgram);
    CPPUNIT_TEST(testUnmarshalWithProgram);
    CPPUNIT_TEST(testUnmarshalWithoutProgram);
    CPPUNIT_TEST_SUITE_END();
};

int main(int argc, char* argv[]) {
    CppUnit::TextUi::TestRunner runner;
    runner.addTest(UseNodeUnmarshallerTest::suite());
    runner.run();
    return 0;
}
