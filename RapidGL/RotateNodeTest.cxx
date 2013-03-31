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
#include <m3d/Math.h>
#include <m3d/Quat.h>
#include <m3d/Mat4.h>
#include <m3d/Vec4.h>
#include "RapidGL/RotateNode.h"
#include "RapidGL/State.h"


/**
 * Test for `RotateNode`.
 */
class RotateNodeTest : public CppUnit::TestFixture {
public:

    // Threshold for floating-point comparisons
    static const double TOLERANCE = 1e-6;

    /**
     * Fake `NodeListener` that stores the node that changed.
     */
    class FakeNodeListener : public RapidGL::NodeListener {
    public:
    // Attributes
        RapidGL::Node* node;
    // Methods
        FakeNodeListener() : node(NULL) { }
        virtual void nodeChanged(RapidGL::Node* node) {
            this->node = node;
        }
    };

    /**
     * Creates a translation matrix for a translation.
     *
     * @param x Translation in X direction
     * @param y Translation in Y direction
     * @param z Translation in Z direction
     * @return Corresponding translation matrix
     */
    static M3d::Mat4 getTranslationMatrix(double x, double y, double z) {
        M3d::Mat4 mat(1);
        mat[3] = M3d::Vec4(x, y, z, 1);
        return mat;
    }

    /**
     * Ensures `RotateNode::setRotation` fires an event.
     */
    void testSetRotation() {

        // Make node and register listener
        RapidGL::RotateNode rotateNode;
        FakeNodeListener fakeNodeListener;
        rotateNode.addNodeListener(&fakeNodeListener);

        // Change rotation and check listener was notified
        CPPUNIT_ASSERT_EQUAL((RapidGL::Node*) NULL, fakeNodeListener.node);
        rotateNode.setRotation(M3d::Quat::Quat(0, 0, 0, 1));
        CPPUNIT_ASSERT_EQUAL((RapidGL::Node*) &rotateNode, fakeNodeListener.node);
    }

    /**
     * Ensures `RotateNode::visit` works correctly.
     */
    void testVisit() {

        // Make rotation
        const M3d::Vec3 axis(0, 0, 1);
        const double angle = M3d::toRadians(90);
        const M3d::Quat rotation = M3d::Quat::fromAxisAngle(axis, angle);

        // Make rotate node
        RapidGL::RotateNode rotateNode(rotation);

        // Set up state
        RapidGL::State state;
        const M3d::Mat4 translationMatrix = getTranslationMatrix(5, 0, 0);
        state.setModelMatrix(translationMatrix);

        // Visit node
        rotateNode.visit(state);

        // Check matrix
        const M3d::Vec4 expected(5, 1, 0, 1);
        const M3d::Vec4 actual = state.getModelMatrix() * M3d::Vec4(1, 0, 0, 1);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(expected.x, actual.x, TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(expected.y, actual.y, TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(expected.z, actual.z, TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(expected.w, actual.w, TOLERANCE);
    }

    CPPUNIT_TEST_SUITE(RotateNodeTest);
    CPPUNIT_TEST(testSetRotation);
    CPPUNIT_TEST(testVisit);
    CPPUNIT_TEST_SUITE_END();
};

int main(int argc, char* argv[]) {
    CppUnit::TextUi::TestRunner runner;
    runner.addTest(RotateNodeTest::suite());
    runner.run();
    return 0;
}
