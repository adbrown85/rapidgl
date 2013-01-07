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
#include <m3d/Math.hxx>
#include <m3d/Quat.hxx>
#include "RapidGL/Node.hxx"
#include "RapidGL/RotateNode.hxx"
#include "RapidGL/RotateNodeUnmarshaller.hxx"


/**
 * Unit test for `RotateNodeUnmarshaller`.
 */
class RotateNodeUnmarshallerTest : public CppUnit::TestFixture {
public:

    // Instance to use for testing
    RapidGL::RotateNodeUnmarshaller unmarshaller;

    /**
     * Ensures `RotateNodeUnmarshaller::unmarshal` throws an exception if given an invalid angle.
     */
    void testUnmarshalWithInvalidAngle() {

        // Make attributes
        std::map<std::string,std::string> attributes;
        attributes["axis"] = "0.0 0.0 0.0";
        attributes["angle"] = "foo";

        // Unmarshal
        CPPUNIT_ASSERT_THROW(unmarshaller.unmarshal(attributes), std::runtime_error);
    }

    /**
     * Ensures `RotateNodeUnmarshaller::unmarshal` throws an exception if given an invalid axis.
     */
    void testUnmarshalWithAxisWithInvalidComponent() {

        // Make attributes
        std::map<std::string,std::string> attributes;
        attributes["axis"] = "1.0 foo 3.0";
        attributes["angle"] = "30.0";

        // Unmarshal
        CPPUNIT_ASSERT_THROW(unmarshaller.unmarshal(attributes), std::runtime_error);
    }

    /**
     * Ensures `RotateNodeUnmarshaller::unmarshal` throws an exception if given an invalid axis.
     */
    void testUnmarshalWithAxisWithWrongNumberOfComponents() {

        // Make attributes
        std::map<std::string,std::string> attributes;
        attributes["axis"] = "1.0 2.0";
        attributes["angle"] = "30.0";

        // Unmarshal
        CPPUNIT_ASSERT_THROW(unmarshaller.unmarshal(attributes), std::runtime_error);
    }

    /**
     * Ensures `RotateNodeUnmarshaller::unmarshal` throws an exception if missing an angle.
     */
    void testUnmarshalWithMissingAngle() {

        // Make attributes
        std::map<std::string,std::string> attributes;
        attributes["axis"] = "0.0 0.0 1.0";

        // Unmarshal
        CPPUNIT_ASSERT_THROW(unmarshaller.unmarshal(attributes), std::runtime_error);
    }

    /**
     * Ensures `RotateNodeUnmarshaller::unmarshal` throws an exception if missing an axis.
     */
    void testUnmarshalWithMissingAxis() {

        // Make attributes
        std::map<std::string,std::string> attributes;
        attributes["angle"] = "30.0";

        // Unmarshal
        CPPUNIT_ASSERT_THROW(unmarshaller.unmarshal(attributes), std::runtime_error);
    }

    /**
     * Ensures `RotateNodeUnmarshaller::unmarshal` works.
     */
    void testUnmarshalWithValidAxisAngle() {

        // Make attributes
        std::map<std::string,std::string> attributes;
        attributes["axis"] = "0.0 0.0 1.0";
        attributes["angle"] = "30.0";

        // Unmarshal
        RapidGL::Node* node = unmarshaller.unmarshal(attributes);
        RapidGL::RotateNode* rotateNode = dynamic_cast<RapidGL::RotateNode*>(node);
        CPPUNIT_ASSERT(rotateNode != NULL);

        // Check rotation
        const M3d::Vec3 axis(0, 0, 1);
        const double angle = M3d::toRadians(30);
        const M3d::Quat expected = M3d::Quat::fromAxisAngle(axis, angle);
        const M3d::Quat actual = rotateNode->getRotation();
        CPPUNIT_ASSERT_EQUAL(expected, actual);
    }

    CPPUNIT_TEST_SUITE(RotateNodeUnmarshallerTest);
    CPPUNIT_TEST(testUnmarshalWithInvalidAngle);
    CPPUNIT_TEST(testUnmarshalWithAxisWithInvalidComponent);
    CPPUNIT_TEST(testUnmarshalWithAxisWithWrongNumberOfComponents);
    CPPUNIT_TEST(testUnmarshalWithMissingAngle);
    CPPUNIT_TEST(testUnmarshalWithMissingAxis);
    CPPUNIT_TEST(testUnmarshalWithValidAxisAngle);
    CPPUNIT_TEST_SUITE_END();
};

int main(int argc, char* argv[]) {
    CppUnit::TextUi::TestRunner runner;
    runner.addTest(RotateNodeUnmarshallerTest::suite());
    runner.run();
    return 0;
}
