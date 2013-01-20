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
#include <cppunit/extensions/HelperMacros.h>
#include <GL/glfw.h>
#include <m3d/Mat3.hxx>
#include <m3d/Mat4.hxx>
#include <m3d/Vec3.hxx>
#include <m3d/Vec4.hxx>
#include "RapidGL/UniformNodeUnmarshaller.h"
using std::map;
using std::string;


/**
 * Unit test for UniformNodeUnmarshaller.
 */
class UniformNodeUnmarshallerTest {
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
        attributes["usage"] = "modelviewprojection";
        RapidGL::Node* node = unmarshaller.unmarshal(attributes);
        RapidGL::Mat4UniformNode* mat4UniformNode = dynamic_cast<RapidGL::Mat4UniformNode*>(node);
        CPPUNIT_ASSERT(mat4UniformNode != NULL);

        // Check name
        CPPUNIT_ASSERT_EQUAL(string("MVPMatrix"), mat4UniformNode->getName());

        // Check usage
        CPPUNIT_ASSERT_EQUAL(RapidGL::Mat4UniformNode::MODEL_VIEW_PROJECTION, mat4UniformNode->getUsage());

        // Check value
        const M3d::Mat4 expected = M3d::Mat4(1);
        const M3d::Mat4 actual = mat4UniformNode->getValue();
        CPPUNIT_ASSERT_EQUAL(expected, actual);
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
     * Ensures `UniformNodeUnmarshaller::unmarshal` works with 'sampler2d' type.
     */
    void testUnmarshalWithSampler2dType() {

        // Make map of attributes
        map<string,string> attributes;
        attributes["type"] = "sampler2d";
        attributes["name"] = "foo";
        attributes["link"] = "bar";

        // Unmarshal node
        RapidGL::Node* node = unmarshaller.unmarshal(attributes);
        RapidGL::Sampler2dUniformNode* sampler2dUniformNode = dynamic_cast<RapidGL::Sampler2dUniformNode*>(node);
        CPPUNIT_ASSERT(sampler2dUniformNode != NULL);

        // Check name and link
        CPPUNIT_ASSERT_EQUAL(string("foo"), sampler2dUniformNode->getName());
        CPPUNIT_ASSERT_EQUAL(string("bar"), sampler2dUniformNode->getLink());
    }

    /**
     * Ensures `UniformNodeUnmarshaller::unmarshal` works with 'sampler3d' type.
     */
    void testUnmarshalWithSampler3dType() {

        // Make map of attributes
        map<string,string> attributes;
        attributes["type"] = "sampler3d";
        attributes["name"] = "foo";
        attributes["link"] = "bar";

        // Unmarshal node
        RapidGL::Node* node = unmarshaller.unmarshal(attributes);
        RapidGL::Sampler3dUniformNode* sampler3dUniformNode = dynamic_cast<RapidGL::Sampler3dUniformNode*>(node);
        CPPUNIT_ASSERT(sampler3dUniformNode != NULL);

        // Check name and link
        CPPUNIT_ASSERT_EQUAL(string("foo"), sampler3dUniformNode->getName());
        CPPUNIT_ASSERT_EQUAL(string("bar"), sampler3dUniformNode->getLink());
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
};

int main(int argc, char* argv[]) {

    // Initialize GLFW
    if (!glfwInit()) {
        throw std::runtime_error("Could not initialize GLFW!");
    }

    // Open window
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 2);
    glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    if (!glfwOpenWindow(512, 512, 0, 0, 0, 0, 0, 0, GLFW_WINDOW)) {
        throw std::runtime_error("Could not open GLFW window!");
    }

    // Run test
    try {
        UniformNodeUnmarshallerTest test;
        test.testUnmarshalWithEmptyName();
        test.testUnmarshalWithEmptyType();
        test.testUnmarshalWithFloatType();
        test.testUnmarshalWithMat3Type();
        test.testUnmarshalWithMat4Type();
        test.testUnmarshalWithInvalidType();
        test.testUnmarshalWithMissingName();
        test.testUnmarshalWithMissingType();
        test.testUnmarshalWithSampler2dType();
        test.testUnmarshalWithSampler3dType();
        test.testUnmarshalWithVec3Type();
        test.testUnmarshalWithVec4Type();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        throw;
    }

    // Exit
    glfwTerminate();
    return 0;
}
