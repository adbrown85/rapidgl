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
#include <m3d/Mat4.hxx>
#include <m3d/Vec3.hxx>
#include <m3d/Vec4.hxx>
#include "RapidGL/ScaleNode.hxx"
#include "RapidGL/State.hxx"


/**
 * Unit test for `ScaleNode`.
 */
class ScaleNodeTest : public CppUnit::TestFixture {
public:

    // Threshold for floating-point comparisons
    static const double TOLERANCE = 1e-6;

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
     * Ensures `ScaleNode::visit` works correctly.
     */
    void testVisit() {

        // Make scale node
        RapidGL::ScaleNode scaleNode;
        scaleNode.setScale(M3d::Vec3(10, 20, 30));

        // Set up state
        RapidGL::State state;
        const M3d::Mat4 translateMatrix = getTranslationMatrix(5, 0, 0);
        state.setModelMatrix(translateMatrix);

        // Visit node
        const M3d::Vec3 p;
        scaleNode.visit(state);

        // Check result
        const M3d::Vec4 expected = M3d::Vec4(15, 20, 30, 1);
        const M3d::Vec4 actual = state.getModelMatrix() * M3d::Vec4(1, 1, 1, 1);
        CPPUNIT_ASSERT_EQUAL(expected, actual);
    }

    CPPUNIT_TEST_SUITE(ScaleNodeTest);
    CPPUNIT_TEST(testVisit);
    CPPUNIT_TEST_SUITE_END();
};

int main(int argc, char* argv[]) {
    CppUnit::TextUi::TestRunner runner;
    runner.addTest(ScaleNodeTest::suite());
    runner.run();
    return 0;
}
