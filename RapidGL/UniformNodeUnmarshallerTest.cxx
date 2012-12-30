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
#include <m3d/Mat3.hxx>
#include <m3d/Mat4.hxx>
#include <m3d/Vec3.hxx>
#include <m3d/Vec4.hxx>
#include "RapidGL/UniformNodeUnmarshaller.hxx"
using std::map;
using std::string;


/**
 * Unit test for UniformNodeUnmarshaller.
 */
class UniformNodeUnmarshaller : public CppUnit::TestFixture {
public:

    // Threshold for floating-point comparisons
    static const double TOLERANCE = 1e-9;

    // Instance to use for testing
    RapidGL::UniformNodeUnmarshaller unmarshaller;

    /**
     * Ensures `UniformNodeUnmarshaller::unmarshal` throws if 'name' is empty.
     */
    void testUnmarshalWithEmptyName() {
        map<string,string> attributes;
        attributes["type"] = "float";
        attributes["name"] = "";
    }

    /**
     * Ensures `UniformNodeUnmarshaller::unmarshal` throws if 'type' is empty.
     */
    void testUnmarshalWithEmptyType() {
        map<string,string> attributes;
        attributes["type"] = "";
        attributes["name"] = "MVPMatrix";
        CPPUNIT_ASSERT_THROW(unmarshaller.unmarshal(attributes), std::runtime_error);
    }

    /**
     * Ensures `UniformNodeUnmarshaller::unmarshal` throws if 'type' is invalid.
     */
    void testUnmarshalWithInvalidType() {
        map<string,string> attributes;
        attributes["type"] = "foo";
        attributes["name"] = "MVPMatrix";
        CPPUNIT_ASSERT_THROW(unmarshaller.unmarshal(attributes), std::runtime_error);
    }

    /**
     * Ensures `UniformNodeUnmarshaller::unmarshal` works with 'float' type.
     */
    void testUnmarshalWithFloatType() {

        // Unmarshal node
        map<string,string> attributes;
        attributes["type"] = "float";
        attributes["name"] = "Opacity";
        attributes["value"] = "1";
        RapidGL::Node* node = unmarshaller.unmarshal(attributes);
        RapidGL::FloatUniformNode* floatUniformNode = dynamic_cast<RapidGL::FloatUniformNode*>(node);
        CPPUNIT_ASSERT(floatUniformNode != NULL);

        // Check name
        CPPUNIT_ASSERT_EQUAL(string("Opacity"), floatUniformNode->getName());

        // Check value
        CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0f, floatUniformNode->getValue(), TOLERANCE);
    }

    /**
     * Ensures `UniformNodeUnmarshaller::unmarshal` works with 'mat3' type.
     */
    void testUnmarshalWithMat3Type() {

        // Unmarshal node
        map<string,string> attributes;
        attributes["type"] = "mat3";
        attributes["name"] = "MVPMatrix";
        attributes["value"] = "1 2 3 4 5 6 7 8 9";
        RapidGL::Node* node = unmarshaller.unmarshal(attributes);
        RapidGL::Mat3UniformNode* mat3UniformNode = dynamic_cast<RapidGL::Mat3UniformNode*>(node);
        CPPUNIT_ASSERT(mat3UniformNode != NULL);

        // Check name
        CPPUNIT_ASSERT_EQUAL(string("MVPMatrix"), mat3UniformNode->getName());

        // Check value
        const M3d::Mat3 mat = mat3UniformNode->getValue();
        GLfloat actual[9];
        mat.toArrayInColumnMajor(actual);
        for (int i = 0; i < 9; ++i) {
            CPPUNIT_ASSERT_DOUBLES_EQUAL((GLfloat) i + 1, actual[i], TOLERANCE);
        }
    }

    /**
     * Ensures `UniformNodeUnmarshaller::unmarshal` works with 'mat4' type.
     */
    void testUnmarshalWithMat4Type() {

        // Unmarshal node
        map<string,string> attributes;
        attributes["type"] = "mat4";
        attributes["name"] = "MVPMatrix";
        attributes["value"] = "1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16";
        RapidGL::Node* node = unmarshaller.unmarshal(attributes);
        RapidGL::Mat4UniformNode* mat4UniformNode = dynamic_cast<RapidGL::Mat4UniformNode*>(node);
        CPPUNIT_ASSERT(mat4UniformNode != NULL);

        // Check name
        CPPUNIT_ASSERT_EQUAL(string("MVPMatrix"), mat4UniformNode->getName());

        // Check value
        const M3d::Mat4 mat = mat4UniformNode->getValue();
        GLfloat actual[16];
        mat.toArrayInColumnMajor(actual);
        for (int i = 0; i < 16; ++i) {
            CPPUNIT_ASSERT_DOUBLES_EQUAL((GLfloat) i + 1, actual[i], TOLERANCE);
        }
    }

    /**
     * Ensures `UniformNodeUnmarshaller::unmarshal` throws if 'name' is missing.
     */
    void testUnmarshalWithMissingName() {
        map<string,string> attributes;
        attributes["type"] = "float";
        CPPUNIT_ASSERT_THROW(unmarshaller.unmarshal(attributes), std::runtime_error);
    }

    /**
     * Ensures `UniformNodeUnmarshaller::unmarshal` throws if 'type' is missing.
     */
    void testUnmarshalWithMissingType() {
        map<string,string> attributes;
        attributes["name"] = "MVPMatrix";
        CPPUNIT_ASSERT_THROW(unmarshaller.unmarshal(attributes), std::runtime_error);
    }

    /**
     * Ensures `UniformNodeUnmarshaller::unmarshal` works with 'vec3' type.
     */
    void testUnmarshalWithVec3Type() {

        // Unmarshal node
        map<string,string> attributes;
        attributes["type"] = "vec3";
        attributes["name"] = "Color";
        attributes["value"] = "1 2 3";
        RapidGL::Node* node = unmarshaller.unmarshal(attributes);
        RapidGL::Vec3UniformNode* vec3UniformNode = dynamic_cast<RapidGL::Vec3UniformNode*>(node);
        CPPUNIT_ASSERT(vec3UniformNode != NULL);

        // Check name
        CPPUNIT_ASSERT_EQUAL(string("Color"), vec3UniformNode->getName());

        // Check value
        const M3d::Vec3 value = vec3UniformNode->getValue();
        CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0f, value.x, TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(2.0f, value.y, TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(3.0f, value.z, TOLERANCE);
    }

    /**
     * Ensures `UniformNodeUnmarshaller::unmarshal` works with 'vec4' type.
     */
    void testUnmarshalWithVec4Type() {

        // Unmarshal node
        map<string,string> attributes;
        attributes["type"] = "vec4";
        attributes["name"] = "Color";
        attributes["value"] = "1 2 3 4";
        RapidGL::Node* node = unmarshaller.unmarshal(attributes);
        RapidGL::Vec4UniformNode* vec4UniformNode = dynamic_cast<RapidGL::Vec4UniformNode*>(node);
        CPPUNIT_ASSERT(vec4UniformNode != NULL);

        // Check name
        CPPUNIT_ASSERT_EQUAL(string("Color"), vec4UniformNode->getName());

        // Check value
        const M3d::Vec4 value = vec4UniformNode->getValue();
        CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0f, value.x, TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(2.0f, value.y, TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(3.0f, value.z, TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(4.0f, value.w, TOLERANCE);
    }

    CPPUNIT_TEST_SUITE(UniformNodeUnmarshaller);
    CPPUNIT_TEST(testUnmarshalWithEmptyName);
    CPPUNIT_TEST(testUnmarshalWithEmptyType);
    CPPUNIT_TEST(testUnmarshalWithFloatType);
    CPPUNIT_TEST(testUnmarshalWithMat3Type);
    CPPUNIT_TEST(testUnmarshalWithMat4Type);
    CPPUNIT_TEST(testUnmarshalWithInvalidType);
    CPPUNIT_TEST(testUnmarshalWithMissingName);
    CPPUNIT_TEST(testUnmarshalWithMissingType);
    CPPUNIT_TEST(testUnmarshalWithVec3Type);
    CPPUNIT_TEST(testUnmarshalWithVec4Type);
    CPPUNIT_TEST_SUITE_END();
};

int main(int argc, char* argv[]) {
    CppUnit::TextUi::TestRunner runner;
    runner.addTest(UniformNodeUnmarshaller::suite());
    runner.run();
    return 0;
}
