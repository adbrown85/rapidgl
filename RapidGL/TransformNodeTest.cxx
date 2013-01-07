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
#include "RapidGL/State.hxx"
#include "RapidGL/TransformNode.hxx"


/**
 * Test for `TransformNode`.
 */
class TransformNodeTest : public CppUnit::TestFixture {
public:

    // Threshold for floating-point comparisons
    static const double TOLERANCE = 1e-6;

    /**
     * Fake implementation of `TransformNode` for testing.
     */
    class FakeTransformNode : public RapidGL::TransformNode {
    public:
        virtual void visit(RapidGL::State& state) {
            // empty
        }
    };

    /**
     * Ensures `TransformNode::postVisit` pops the model matrix.
     */
    void testPostVisit() {

        // Make transform node
        FakeTransformNode transformNode;

        // Set up state
        RapidGL::State state;
        state.pushModelMatrix();
        CPPUNIT_ASSERT_EQUAL((size_t) 2, state.getModelMatrixStackSize());

        // Call `postVisit`
        transformNode.postVisit(state);

        // Check size of stack
        CPPUNIT_ASSERT_EQUAL((size_t) 1, state.getModelMatrixStackSize());
    }

    /**
     * Ensures `TransformNode::preVisit` pushes the model matrix.
     */
    void testPreVisit() {

        // Make transform node
        FakeTransformNode transformNode;

        // Set up state
        RapidGL::State state;
        CPPUNIT_ASSERT_EQUAL((size_t) 1, state.getModelMatrixStackSize());

        // Call `preVisit`
        transformNode.preVisit(state);

        // Check size of stack
        CPPUNIT_ASSERT_EQUAL((size_t) 2, state.getModelMatrixStackSize());
    }

    CPPUNIT_TEST_SUITE(TransformNodeTest);
    CPPUNIT_TEST(testPostVisit);
    CPPUNIT_TEST(testPreVisit);
    CPPUNIT_TEST_SUITE_END();
};

int main(int argc, char* argv[]) {
    CppUnit::TextUi::TestRunner runner;
    runner.addTest(TransformNodeTest::suite());
    runner.run();
    return 0;
}
