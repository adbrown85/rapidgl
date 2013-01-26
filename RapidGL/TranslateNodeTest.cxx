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
#include <m3d/Mat4.h>
#include <m3d/Math.h>
#include <m3d/Quat.h>
#include <m3d/Vec3.h>
#include <m3d/Vec4.h>
#include "RapidGL/State.h"
#include "RapidGL/TranslateNode.h"


/**
 * Test for `TranslateNode`.
 */
class TranslateNodeTest : public CppUnit::TestFixture {
public:

    // Threshold for floating-point comparisons
    static const double TOLERANCE = 1e-6;

    /**
     * Ensures `TranslateNode::visit` post-multiplies in the translation matrix.
     */
    void testVisit() {

        // Make translate node from translation
        const M3d::Vec3 translation(5, 0, 0);
        RapidGL::TranslateNode translateNode;
        translateNode.setTranslation(translation);

        // Make a rotation
        const M3d::Vec3 axis(0, 0, 1);
        const double angle = M3d::toRadians(90);
        const M3d::Quat rotation = M3d::Quat::fromAxisAngle(axis, angle);

        // Set up state with the rotation
        RapidGL::State state;
        state.setModelMatrix(rotation.toMat4());

        // Call `visit`
        translateNode.visit(state);

        // Check position of origin
        M3d::Vec4 expected(0, 5, 0, 1);
        M3d::Vec4 actual = state.getModelMatrix() * M3d::Vec4(0, 0, 0, 1);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(expected.x, actual.x, TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(expected.y, actual.y, TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(expected.z, actual.z, TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(expected.w, actual.w, TOLERANCE);
    }

    CPPUNIT_TEST_SUITE(TranslateNodeTest);
    CPPUNIT_TEST(testVisit);
    CPPUNIT_TEST_SUITE_END();
};

int main(int argc, char* argv[]) {
    CppUnit::TextUi::TestRunner runner;
    runner.addTest(TranslateNodeTest::suite());
    runner.run();
    return 0;
}
