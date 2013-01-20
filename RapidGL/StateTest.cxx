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
#include <stdexcept>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/ui/text/TestRunner.h>
#include <m3d/Mat4.hxx>
#include <m3d/Vec4.hxx>
#include "RapidGL/State.h"


/**
 * Unit test for `State`.
 */
class StateTest : public CppUnit::TestFixture {
public:

    // Threshold for floating-point comparisons
    static const double TOLERANCE = 1e-9;

    /**
     * Asserts that two matrices are approximately equal.
     *
     * @param expected Expected results
     * @param actual Actual results
     */
    static void assertMatricesEqual(const M3d::Mat4 expected, const M3d::Mat4 actual) {
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                CPPUNIT_ASSERT_DOUBLES_EQUAL(expected[j][i], actual[j][i], TOLERANCE);
            }
        }
    }

    /**
     * Asserts that a matrix is approximately the identity matrix.
     *
     * @param mat Matrix to check
     */
    static void assertMatrixIsIdentity(const M3d::Mat4& mat) {
        assertMatricesEqual(M3d::Mat4(1), mat);
    }

    /**
     * Ensures the default model matrix is the identity matrix.
     */
    void testDefaultModelMatrix() {
        const RapidGL::State state;
        const M3d::Mat4 mat = state.getModelMatrix();
        assertMatrixIsIdentity(mat);
    }

    /**
     * Ensures the default projection matrix is the identity matrix.
     */
    void testDefaultProjectionMatrix() {
        const RapidGL::State state;
        const M3d::Mat4 mat = state.getProjectionMatrix();
        assertMatrixIsIdentity(mat);
    }

    /**
     * Ensures the default view matrix is the identity matrix.
     */
    void testDefaultViewMatrix() {
        const RapidGL::State state;
        const M3d::Mat4 mat = state.getViewMatrix();
        assertMatrixIsIdentity(mat);
    }

    /**
     * Ensures `State::getModelViewMatrix` works correctly.
     */
    void testGetModelViewMatrix() {

        // Make model matrix
        M3d::Mat4 modelMatrix;
        modelMatrix[0] = M3d::Vec4(1, 2, 3, 4);
        modelMatrix[1] = M3d::Vec4(5, 6, 7, 8);
        modelMatrix[2] = M3d::Vec4(9, 10, 11, 12);
        modelMatrix[3] = M3d::Vec4(13, 14, 15, 16);

        // Make view matrix
        M3d::Mat4 viewMatrix;
        viewMatrix[0] = M3d::Vec4(10, 20, 30, 40);
        viewMatrix[1] = M3d::Vec4(50, 60, 70, 80);
        viewMatrix[2] = M3d::Vec4(90, 100, 110, 120);
        viewMatrix[3] = M3d::Vec4(130, 140, 150, 160);

        // Set matrices
        RapidGL::State state;
        state.setModelMatrix(modelMatrix);
        state.setViewMatrix(viewMatrix);

        // Check results
        const M3d::Mat4 expected = viewMatrix * modelMatrix;
        const M3d::Mat4 actual = state.getModelViewMatrix();
        assertMatricesEqual(expected, actual);
    }

    /**
     * Ensures `State::getModelViewProjectionMatrix` works correctly.
     */
    void testGetModelViewProjectionMatrix() {

        // Make model matrix
        M3d::Mat4 modelMatrix;
        modelMatrix[0] = M3d::Vec4(1, 2, 3, 4);
        modelMatrix[1] = M3d::Vec4(5, 6, 7, 8);
        modelMatrix[2] = M3d::Vec4(9, 10, 11, 12);
        modelMatrix[3] = M3d::Vec4(13, 14, 15, 16);

        // Make view matrix
        M3d::Mat4 viewMatrix;
        viewMatrix[0] = M3d::Vec4(10, 20, 30, 40);
        viewMatrix[1] = M3d::Vec4(50, 60, 70, 80);
        viewMatrix[2] = M3d::Vec4(90, 100, 110, 120);
        viewMatrix[3] = M3d::Vec4(130, 140, 150, 160);

        // Make projection matrix
        M3d::Mat4 projectionMatrix;
        projectionMatrix[0] = M3d::Vec4(100, 200, 300, 400);
        projectionMatrix[1] = M3d::Vec4(500, 600, 700, 800);
        projectionMatrix[2] = M3d::Vec4(900, 1000, 1100, 1200);
        projectionMatrix[3] = M3d::Vec4(1300, 1400, 1500, 1600);

        // Set matrices
        RapidGL::State state;
        state.setModelMatrix(modelMatrix);
        state.setViewMatrix(viewMatrix);
        state.setProjectionMatrix(projectionMatrix);

        // Check results
        const M3d::Mat4 expected = projectionMatrix * viewMatrix * modelMatrix;
        const M3d::Mat4 actual = state.getModelViewProjectionMatrix();
        assertMatricesEqual(expected, actual);
    }

    /**
     * Ensures `State::popModelMatrix` throws an exception if trying to pop off bottom.
     */
    void testPopModelMatrixWithBottom() {
        RapidGL::State state;
        CPPUNIT_ASSERT_THROW(state.popModelMatrix(), std::runtime_error);
    }

    /**
     * Ensures `State::popProjectionMatrix` throws an exception if trying to pop off bottom.
     */
    void testPopProjectionMatrixWithBottom() {
        RapidGL::State state;
        CPPUNIT_ASSERT_THROW(state.popProjectionMatrix(), std::runtime_error);
    }

    /**
     * Ensures `State::popViewMatrix` throws an exception if trying to pop off bottom.
     */
    void testPopViewMatrixWithBottom() {
        RapidGL::State state;
        CPPUNIT_ASSERT_THROW(state.popViewMatrix(), std::runtime_error);
    }

    /**
     * Ensures `State::getViewProjectionMatrix` works correctly.
     */
    void testViewProjectionMatrix() {

        // Make view matrix
        M3d::Mat4 viewMatrix;
        viewMatrix[0] = M3d::Vec4(1, 2, 3, 4);
        viewMatrix[1] = M3d::Vec4(5, 6, 7, 8);
        viewMatrix[2] = M3d::Vec4(9, 10, 11, 12);
        viewMatrix[3] = M3d::Vec4(13, 14, 15, 16);

        // Make projection matrix
        M3d::Mat4 projectionMatrix;
        projectionMatrix[0] = M3d::Vec4(10, 20, 30, 40);
        projectionMatrix[1] = M3d::Vec4(50, 60, 70, 80);
        projectionMatrix[2] = M3d::Vec4(90, 100, 110, 120);
        projectionMatrix[3] = M3d::Vec4(130, 140, 150, 160);

        // Set matrices
        RapidGL::State state;
        state.setViewMatrix(viewMatrix);
        state.setProjectionMatrix(projectionMatrix);

        // Check results
        const M3d::Mat4 expected = projectionMatrix * viewMatrix;
        const M3d::Mat4 actual = state.getViewProjectionMatrix();
        assertMatricesEqual(expected, actual);
    }

    CPPUNIT_TEST_SUITE(StateTest);
    CPPUNIT_TEST(testDefaultModelMatrix);
    CPPUNIT_TEST(testDefaultProjectionMatrix);
    CPPUNIT_TEST(testDefaultViewMatrix);
    CPPUNIT_TEST(testGetModelViewMatrix);
    CPPUNIT_TEST(testGetModelViewProjectionMatrix);
    CPPUNIT_TEST(testPopModelMatrixWithBottom);
    CPPUNIT_TEST(testPopProjectionMatrixWithBottom);
    CPPUNIT_TEST(testPopViewMatrixWithBottom);
    CPPUNIT_TEST(testViewProjectionMatrix);
    CPPUNIT_TEST_SUITE_END();
};

int main(int argc, char* argv[]) {
    CppUnit::TextUi::TestRunner runner;
    runner.addTest(StateTest::suite());
    runner.run();
    return 0;
}
