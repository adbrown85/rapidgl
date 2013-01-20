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
#include <stdexcept>
#include <string>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/ui/text/TestRunner.h>
#include <m3d/Vec3.hxx>
#include "RapidGL/Node.h"
#include "RapidGL/TranslateNode.h"
#include "RapidGL/TranslateNodeUnmarshaller.h"


/**
 * Unit test for `TranslateNodeUnmarshaller`.
 */
class TranslateNodeUnmarshallerTest : public CppUnit::TestFixture {
public:

    // Instance to use for testing
    RapidGL::TranslateNodeUnmarshaller unmarshaller;

    /**
     * Ensures `unmarshal` throws an exception if passed an invalid value for 'x'.
     */
    void testUnmarshalWithInvalidX() {
        std::map<std::string,std::string> attributes;
        attributes["x"] = "foo";
        CPPUNIT_ASSERT_THROW(unmarshaller.unmarshal(attributes), std::runtime_error);
    }

    /**
     * Ensures `unmarshal` throws an exception if passed an invalid value for 'y'.
     */
    void testUnmarshalWithInvalidY() {
        std::map<std::string,std::string> attributes;
        attributes["y"] = "foo";
        CPPUNIT_ASSERT_THROW(unmarshaller.unmarshal(attributes), std::runtime_error);
    }

    /**
     * Ensures `unmarshal` throws an exception if passed an invalid value for 'z'.
     */
    void testUnmarshalWithInvalidZ() {
        std::map<std::string,std::string> attributes;
        attributes["z"] = "foo";
        CPPUNIT_ASSERT_THROW(unmarshaller.unmarshal(attributes), std::runtime_error);
    }

    /**
     * Ensures `unmarshal` works with a valid value for 'x'.
     */
    void testUnmarshalWithValidX() {

        // Make attributes
        std::map<std::string,std::string> attributes;
        attributes["x"] = "5";

        // Unmarshal node
        RapidGL::Node* node = unmarshaller.unmarshal(attributes);
        RapidGL::TranslateNode* translateNode = dynamic_cast<RapidGL::TranslateNode*>(node);
        CPPUNIT_ASSERT(translateNode != NULL);

        // Check translation
        const M3d::Vec3 expected(5, 0, 0);
        const M3d::Vec3 actual = translateNode->getTranslation();
        CPPUNIT_ASSERT_EQUAL(expected, actual);
    }

    /**
     * Ensures `unmarshal` works with a valid value for 'y'.
     */
    void testUnmarshalWithValidY() {

        // Make attributes
        std::map<std::string,std::string> attributes;
        attributes["y"] = "5";

        // Unmarshal node
        RapidGL::Node* node = unmarshaller.unmarshal(attributes);
        RapidGL::TranslateNode* translateNode = dynamic_cast<RapidGL::TranslateNode*>(node);
        CPPUNIT_ASSERT(translateNode != NULL);

        // Check translation
        const M3d::Vec3 expected(0, 5, 0);
        const M3d::Vec3 actual = translateNode->getTranslation();
        CPPUNIT_ASSERT_EQUAL(expected, actual);
    }

    /**
     * Ensures `unmarshal` works with a valid value for 'z'.
     */
    void testUnmarshalWithValidZ() {

        // Make attributes
        std::map<std::string,std::string> attributes;
        attributes["z"] = "5";

        // Unmarshal node
        RapidGL::Node* node = unmarshaller.unmarshal(attributes);
        RapidGL::TranslateNode* translateNode = dynamic_cast<RapidGL::TranslateNode*>(node);
        CPPUNIT_ASSERT(translateNode != NULL);

        // Check translation
        const M3d::Vec3 expected(0, 0, 5);
        const M3d::Vec3 actual = translateNode->getTranslation();
        CPPUNIT_ASSERT_EQUAL(expected, actual);
    }

    CPPUNIT_TEST_SUITE(TranslateNodeUnmarshallerTest);
    CPPUNIT_TEST(testUnmarshalWithInvalidX);
    CPPUNIT_TEST(testUnmarshalWithInvalidY);
    CPPUNIT_TEST(testUnmarshalWithInvalidZ);
    CPPUNIT_TEST(testUnmarshalWithValidX);
    CPPUNIT_TEST(testUnmarshalWithValidY);
    CPPUNIT_TEST(testUnmarshalWithValidZ);
    CPPUNIT_TEST_SUITE_END();
};

int main(int argc, char* argv[]) {
    CppUnit::TextUi::TestRunner runner;
    runner.addTest(TranslateNodeUnmarshallerTest::suite());
    runner.run();
    return 0;
}
