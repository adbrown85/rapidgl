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
#include "RapidGL/Node.hxx"


/**
 * Unit test for Node.
 */
class NodeTest : public CppUnit::TestFixture {
public:

    /**
     * Checks that Node::addChild(Node*) works correctly.
     */
    void testAddChild() {

        // Make parent and child nodes
        RapidGL::Node parent("parent");
        RapidGL::Node child("child");

        // Add child
        parent.addChild(&child);
        CPPUNIT_ASSERT(parent.hasChildren());

        // Check the pointer
        RapidGL::Node::node_range_t children = parent.getChildren();
        CPPUNIT_ASSERT_EQUAL((*(children.begin)), &child);
    }

    /**
     * Checks that Node::removeChild(Node*) works correctly.
     */
    void testRemoveChild() {

        // Make parent and child nodes
        RapidGL::Node parent;
        RapidGL::Node child;

        // Add child
        parent.addChild(&child);
        CPPUNIT_ASSERT(parent.hasChildren());

        // Remove child
        parent.removeChild(&child);
        CPPUNIT_ASSERT(!parent.hasChildren());
    }

    CPPUNIT_TEST_SUITE(NodeTest);
    CPPUNIT_TEST(testAddChild);
    CPPUNIT_TEST(testRemoveChild);
    CPPUNIT_TEST_SUITE_END();
};

int main(int argc, char* argv[]) {
    CppUnit::TextUi::TestRunner runner;
    runner.addTest(NodeTest::suite());
    runner.run();
}
