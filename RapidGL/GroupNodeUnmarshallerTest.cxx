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
#include "RapidGL/GroupNode.h"
#include "RapidGL/GroupNodeUnmarshaller.h"


/**
 * Unit test for `GroupNodeUnmarshaller`.
 */
class GroupNodeUnmarshallerTest : public CppUnit::TestFixture {
public:

    // Instance to use for testing
    RapidGL::Unmarshaller* const unmarshaller;

    /**
     * Constructs the test.
     */
    GroupNodeUnmarshallerTest() : unmarshaller(new RapidGL::GroupNodeUnmarshaller()) {
        // empty
    }

    /**
     * Ensures `unmarshal` throws when value of the _id_ attribute is empty.
     */
    void testUnmarshalWhenIdIsEmpty() {
        std::map<std::string,std::string> attributes;
        attributes["id"] = "";
        CPPUNIT_ASSERT_THROW(unmarshaller->unmarshal(attributes), std::runtime_error);
    }

    /**
     * Ensures `unmarshal` throws when the _id_ attribute is missing.
     */
    void testUnmarshalWhenIdIsMissing() {
        const std::map<std::string,std::string> attributes;
        CPPUNIT_ASSERT_THROW(unmarshaller->unmarshal(attributes), std::runtime_error);
    }

    /**
     * Ensures `unmarshal` works when value of the _id_ attribute is valid.
     */
    void testUnmarshalWhenIdIsValid() {
        std::map<std::string,std::string> attributes;
        attributes["id"] = "foo";
        const RapidGL::Node* node = unmarshaller->unmarshal(attributes);
        const RapidGL::GroupNode* groupNode = dynamic_cast<const RapidGL::GroupNode*>(node);
        CPPUNIT_ASSERT_EQUAL(std::string("foo"), groupNode->getId());
    }

    CPPUNIT_TEST_SUITE(GroupNodeUnmarshallerTest);
    CPPUNIT_TEST(testUnmarshalWhenIdIsEmpty);
    CPPUNIT_TEST(testUnmarshalWhenIdIsMissing);
    CPPUNIT_TEST(testUnmarshalWhenIdIsValid);
    CPPUNIT_TEST_SUITE_END();
};

int main(int argc, char* argv[]) {
    CppUnit::TextUi::TestRunner runner;
    runner.addTest(GroupNodeUnmarshallerTest::suite());
    runner.run();
    return 0;
}
