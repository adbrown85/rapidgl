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
#include "RapidGL/InstanceNode.h"
#include "RapidGL/InstanceNodeUnmarshaller.h"


/**
 * Unit test for `InstanceNodeUnmarshaller`.
 */
class InstanceNodeUnmarshallerTest : public CppUnit::TestFixture {
public:

    // Instance to use for testing
    RapidGL::Unmarshaller* const unmarshaller;

    /**
     * Constructs the test.
     */
    InstanceNodeUnmarshallerTest() : unmarshaller(new RapidGL::InstanceNodeUnmarshaller()) {
        // empty
    }

    /**
     * Ensures `unmarshal` throws when value of the _link_ attribute is empty.
     */
    void testUnmarshalWhenLinkIsEmpty() {
        std::map<std::string,std::string> attributes;
        attributes["link"] = "";
        CPPUNIT_ASSERT_THROW(unmarshaller->unmarshal(attributes), std::runtime_error);
    }

    /**
     * Ensures `unmarshal` throws when the _link_ attribute is missing.
     */
    void testUnmarshalWhenLinkIsMissing() {
        const std::map<std::string,std::string> attributes;
        CPPUNIT_ASSERT_THROW(unmarshaller->unmarshal(attributes), std::runtime_error);
    }

    /**
     * Ensures `unmarshal` works when value of the _link_ attribute is valid.
     */
    void testUnmarshalWhenLinkIsValid() {
        std::map<std::string,std::string> attributes;
        attributes["link"] = "foo";
        const RapidGL::Node* node = unmarshaller->unmarshal(attributes);
        const RapidGL::InstanceNode* instanceNode = dynamic_cast<const RapidGL::InstanceNode*>(node);
        CPPUNIT_ASSERT_EQUAL(std::string("foo"), instanceNode->getLink());
    }

    CPPUNIT_TEST_SUITE(InstanceNodeUnmarshallerTest);
    CPPUNIT_TEST(testUnmarshalWhenLinkIsEmpty);
    CPPUNIT_TEST(testUnmarshalWhenLinkIsMissing);
    CPPUNIT_TEST(testUnmarshalWhenLinkIsValid);
    CPPUNIT_TEST_SUITE_END();
};

int main(int argc, char* argv[]) {
    CppUnit::TextUi::TestRunner runner;
    runner.addTest(InstanceNodeUnmarshallerTest::suite());
    runner.run();
    return 0;
}
