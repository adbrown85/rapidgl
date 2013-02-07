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
#include <stdexcept>
#include <string>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/ui/text/TestRunner.h>
#include "RapidGL/GroupNode.h"


/**
 * Unit test for `GroupNode`.
 */
class GroupNodeTest : public CppUnit::TestFixture {
public:

    /**
     * Ensures `GroupNode` throws when passed an empty identifier.
     */
    void testGroupNodeWithEmptyId() {
        CPPUNIT_ASSERT_THROW(RapidGL::GroupNode(""), std::invalid_argument);
    }

    /**
     * Ensures `GroupNode` works when passed a valid identifier.
     */
    void testGroupNodeWithValidId() {
        const RapidGL::GroupNode groupNode("foo");
        CPPUNIT_ASSERT_EQUAL(std::string("foo"), groupNode.getId());
    }

    CPPUNIT_TEST_SUITE(GroupNodeTest);
    CPPUNIT_TEST(testGroupNodeWithEmptyId);
    CPPUNIT_TEST(testGroupNodeWithValidId);
    CPPUNIT_TEST_SUITE_END();
};

int main(int argc, char* argv[]) {
    CppUnit::TextUi::TestRunner runner;
    runner.addTest(GroupNodeTest::suite());
    runner.run();
    return 0;
}
