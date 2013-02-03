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
#include "RapidGL/PolygonModeNode.h"
#include "RapidGL/PolygonModeNodeUnmarshaller.h"
#include "RapidGL/Unmarshaller.h"


/**
 * Unit test for `PolygonModeNodeUnmarshaller`.
 */
class PolygonModeNodeUnmarshallerTest : public CppUnit::TestFixture {
public:

    // Instance to use for testing
    RapidGL::Unmarshaller* const unmarshaller;

    /**
     * Constructs the test.
     */
    PolygonModeNodeUnmarshallerTest() : unmarshaller(new RapidGL::PolygonModeNodeUnmarshaller()) {
        // empty
    }

    /**
     * Ensures `unmarshal` throws when _mode_ is empty.
     */
    void testUnmarshalWhenModeIsEmpty() {
        std::map<std::string,std::string> attributes;
        attributes["mode"] = "";
        CPPUNIT_ASSERT_THROW(unmarshaller->unmarshal(attributes), std::runtime_error);
    }

    /**
     * Ensures `unmarshal` works correctly when _mode_ is _fill_.
     */
    void testUnmarshalWhenModeIsFill() {

        // Make map
        std::map<std::string,std::string> attributes;
        attributes["mode"] = "fill";

        // Unmarshal node
        const RapidGL::Node* node = unmarshaller->unmarshal(attributes);
        const RapidGL::PolygonModeNode* polygonModeNode = dynamic_cast<const RapidGL::PolygonModeNode*>(node);
        CPPUNIT_ASSERT(polygonModeNode != NULL);

        // Check mode
        CPPUNIT_ASSERT_EQUAL((GLenum) GL_FILL, polygonModeNode->getMode());
    }

    /**
     * Ensures `unmarshal` throws when _mode_ is _foo_.
     */
    void testUnmarshalWhenModeIsFoo() {
        std::map<std::string,std::string> attributes;
        attributes["mode"] = "foo";
        CPPUNIT_ASSERT_THROW(unmarshaller->unmarshal(attributes), std::runtime_error);
    }

    /**
     * Ensures `unmarshal` works correctly when _mode_ is _line_.
     */
    void testUnmarshalWhenModeIsLine() {

        // Make map
        std::map<std::string,std::string> attributes;
        attributes["mode"] = "line";

        // Unmarshal node
        const RapidGL::Node* node = unmarshaller->unmarshal(attributes);
        const RapidGL::PolygonModeNode* polygonModeNode = dynamic_cast<const RapidGL::PolygonModeNode*>(node);
        CPPUNIT_ASSERT(polygonModeNode != NULL);

        // Check mode
        CPPUNIT_ASSERT_EQUAL((GLenum) GL_LINE, polygonModeNode->getMode());
    }

    /**
     * Ensures `unmarshal` works correctly when _mode_ is _point_.
     */
    void testUnmarshalWhenModeIsPoint() {

        // Make map
        std::map<std::string,std::string> attributes;
        attributes["mode"] = "point";

        // Unmarshal node
        const RapidGL::Node* node = unmarshaller->unmarshal(attributes);
        const RapidGL::PolygonModeNode* polygonModeNode = dynamic_cast<const RapidGL::PolygonModeNode*>(node);
        CPPUNIT_ASSERT(polygonModeNode != NULL);

        // Check mode
        CPPUNIT_ASSERT_EQUAL((GLenum) GL_POINT, polygonModeNode->getMode());
    }

    /**
     * Ensures `unmarshal` throws when _mode_ is missing.
     */
    void testUnmarshalWhenModeIsMissing() {
        std::map<std::string,std::string> attributes;
        CPPUNIT_ASSERT_THROW(unmarshaller->unmarshal(attributes), std::runtime_error);
    }

    CPPUNIT_TEST_SUITE(PolygonModeNodeUnmarshallerTest);
    CPPUNIT_TEST(testUnmarshalWhenModeIsEmpty);
    CPPUNIT_TEST(testUnmarshalWhenModeIsFill);
    CPPUNIT_TEST(testUnmarshalWhenModeIsFoo);
    CPPUNIT_TEST(testUnmarshalWhenModeIsLine);
    CPPUNIT_TEST(testUnmarshalWhenModeIsPoint);
    CPPUNIT_TEST(testUnmarshalWhenModeIsMissing);
    CPPUNIT_TEST_SUITE_END();
};

int main(int argc, char* argv[]) {
    CppUnit::TextUi::TestRunner runner;
    runner.addTest(PolygonModeNodeUnmarshallerTest::suite());
    runner.run();
    return 0;
}
