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
#include <stdexcept>
#include "RapidGL/Node.hxx"
#include "RapidGL/AttributeNode.hxx"
#include "RapidGL/AttributeNodeUnmarshaller.hxx"
using std::runtime_error;
using std::map;
using std::string;


/**
 * Unit test for AttributeNodeUnmarshaller.
 */
class AttributeNodeUnmarshallerTest : public CppUnit::TestFixture {
public:

    // Unmarshaller to use for testing
    RapidGL::AttributeNodeUnmarshaller unmarshaller;

    /**
     * Ensures _unmarshal_ throws an exception if _name_ is empty.
     */
    void testUnmarshalWithEmptyName() {
        map<string,string> attributes;
        attributes["name"] = "";
        attributes["usage"] = "point";
        CPPUNIT_ASSERT_THROW(unmarshaller.unmarshal(attributes), runtime_error);
    }

    /**
     * Ensures _unmarshal_ throws an exception if _usage_ is empty.
     */
    void testUnmarshalWithEmptyUsage() {
        map<string,string> attributes;
        attributes["name"] = "MCVertex";
        attributes["usage"] = "";
        CPPUNIT_ASSERT_THROW(unmarshaller.unmarshal(attributes), runtime_error);
    }

    /**
     * Ensures _unmarshal_ throws an exception if _usage_ is invalid.
     */
    void testUnmarshalWithInvalidUsage() {
        map<string,string> attributes;
        attributes["name"] = "MCVertex";
        attributes["usage"] = "foo";
        CPPUNIT_ASSERT_THROW(unmarshaller.unmarshal(attributes), runtime_error);
    }

    /**
     * Ensures _unmarshal_ throws an exception if _name_ is unspecified.
     */
    void testUnmarshalWithUnspecifiedName() {
        map<string,string> attributes;
        attributes["usage"] = "point";
        CPPUNIT_ASSERT_THROW(unmarshaller.unmarshal(attributes), runtime_error);
    }

    /**
     * Ensures _unmarshal_ throws an exception if _usage_ is unspecified.
     */
    void testUnmarshalWithUnspecifiedUsage() {
        map<string,string> attributes;
        attributes["name"] = "MCVertex";
        CPPUNIT_ASSERT_THROW(unmarshaller.unmarshal(attributes), runtime_error);
    }

    CPPUNIT_TEST_SUITE(AttributeNodeUnmarshallerTest);
    CPPUNIT_TEST(testUnmarshalWithEmptyName);
    CPPUNIT_TEST(testUnmarshalWithEmptyUsage);
    CPPUNIT_TEST(testUnmarshalWithInvalidUsage);
    CPPUNIT_TEST(testUnmarshalWithUnspecifiedName);
    CPPUNIT_TEST(testUnmarshalWithUnspecifiedUsage);
    CPPUNIT_TEST_SUITE_END();
};

int main(int argc, char* argv[]) {
    CppUnit::TextUi::TestRunner runner;
    runner.addTest(AttributeNodeUnmarshallerTest::suite());
    runner.run();
    return 0;
}
