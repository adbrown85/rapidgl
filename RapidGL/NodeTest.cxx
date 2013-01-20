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
     * Fake node for testing.
     */
    class FooNode : public RapidGL::Node {
    public:

        FooNode(const std::string& id = "") : RapidGL::Node(id) {
            // empty
        }

        virtual void visit(RapidGL::State& state) {
            // empty
        }
    };

    /**
     * Fake node for testing.
     */
    class BarNode : public RapidGL::Node {
    public:
        BarNode(const std::string& id = "") : RapidGL::Node(id) {
            // empty
        }

        virtual void visit(RapidGL::State& state) {
            // empty
        }
    };

    /**
     * Checks that Node::addChild(Node*) works correctly.
     */
    void testAddChild() {

        // Make parent and child nodes
        FooNode parent("parent");
        BarNode child("child");

        // Add child
        parent.addChild(&child);
        CPPUNIT_ASSERT(parent.hasChildren());

        // Check the pointers
        RapidGL::Node::node_range_t children = parent.getChildren();
        CPPUNIT_ASSERT_EQUAL((*(children.begin)), (RapidGL::Node*) &child);
        CPPUNIT_ASSERT_EQUAL((RapidGL::Node*) &parent, child.getParent());
    }

    /**
     * Ensures findAncestor<T>(Node*. const std::string&) finds the correct ancestor.
     */
    void testFindAncestorNodeStringWithAncestorOfTypeAndWithId() {

        // Make nodes
        FooNode n1("foo");
        BarNode n2("foo");
        BarNode n3;
        FooNode n4;

        // Connect nodes
        n1.addChild(&n2);
        n2.addChild(&n3);
        n3.addChild(&n4);

        // Find 'FooNode' ancestor
        FooNode* node = RapidGL::findAncestor<FooNode>(&n4, "foo");
        CPPUNIT_ASSERT_EQUAL(&n1, node);
    }

    /**
     * Ensures findAncestor<T>(Node*, const std::string&) throws if passed an empty identifier.
     */
    void testFindAncestorNodeStringWithEmptyId() {
        const FooNode node;
        CPPUNIT_ASSERT_THROW(RapidGL::findAncestor<FooNode>(&node, ""), std::invalid_argument);
    }

    /**
     * Ensures findAncestor<T>(Node*, const std::string&) returns `NULL` when cannot find ancestor of type.
     */
    void testFindAncestorNodeStringWithNoAncestorOfType() {

        // Make nodes
        BarNode n1("foo");
        BarNode n2;
        BarNode n3;
        FooNode n4;

        // Connect Nodes
        n1.addChild(&n2);
        n2.addChild(&n3);
        n3.addChild(&n4);

        // Find 'FooNode' ancestor
        FooNode* node = RapidGL::findAncestor<FooNode>(&n4, "foo");
        CPPUNIT_ASSERT_EQUAL((FooNode*) NULL, node);
    }

    /**
     * Ensures findAncestor<T>(Node*, const std::string&) returns `NULL` when cannot find ancestor with identifier.
     */
    void testFindAncestorNodeStringWithNoAncestorWithId() {

        // Make nodes
        FooNode n1("bar");
        BarNode n2;
        BarNode n3;
        FooNode n4;

        // Connect Nodes
        n1.addChild(&n2);
        n2.addChild(&n3);
        n3.addChild(&n4);

        // Find 'FooNode' ancestor
        FooNode* node = RapidGL::findAncestor<FooNode>(&n4, "foo");
        CPPUNIT_ASSERT_EQUAL((FooNode*) NULL, node);
    }

    /**
     * Ensures findAncestor<T>(Node*, const std::string&) returns `NULL` when node has no parent.
     */
    void testFindAncestorNodeStringWithNoParent() {
        const FooNode node;
        CPPUNIT_ASSERT_EQUAL((FooNode*) NULL, RapidGL::findAncestor<FooNode>(&node, "foo"));
    }

    /**
     * Ensures findAncestor<T>(Node*, const std::string&) throws if passed a `NULL` node.
     */
    void testFindAncestorNodeStringWithNullNode() {
        CPPUNIT_ASSERT_THROW(RapidGL::findAncestor<FooNode>(NULL, "foo"), std::invalid_argument);
    }

    /**
     * Ensures findAncestor<T>(Node*) finds the correct ancestor.
     */
    void testFindAncestorNodeWithAncestorOfType() {

        // Make nodes
        FooNode n1;
        BarNode n2;
        BarNode n3;
        FooNode n4;

        // Connect nodes
        n1.addChild(&n2);
        n2.addChild(&n3);
        n3.addChild(&n4);

        // Find 'FooNode' ancestor
        FooNode* node = RapidGL::findAncestor<FooNode>(&n4);
        CPPUNIT_ASSERT_EQUAL(&n1, node);
    }

    /**
     * Ensures findAncestor<T>(Node*) returns `NULL` when node does not have an ancestor of that type.
     */
    void testFindAncestorNodeWithNoAncestorOfType() {

        // Make nodes
        BarNode n1;
        BarNode n2;
        BarNode n3;
        FooNode n4;

        // Connect Nodes
        n1.addChild(&n2);
        n2.addChild(&n3);
        n3.addChild(&n4);

        // Find 'FooNode' ancestor
        FooNode* node = RapidGL::findAncestor<FooNode>(&n4);
        CPPUNIT_ASSERT_EQUAL((FooNode*) NULL, node);
    }

    /**
     * Ensures findAncestor<T>(Node*) returns `NULL` when node has no parent.
     */
    void testFindAncestorNodeWithNoParent() {
        FooNode node;
        CPPUNIT_ASSERT_EQUAL((FooNode*) NULL, RapidGL::findAncestor<FooNode>(&node));
    }

    /**
     * Ensures findAncestor<T>(Node*) throws an exception if passed `NULL`.
     */
    void testFindAncestorNodeWithNull() {
        CPPUNIT_ASSERT_THROW(RapidGL::findAncestor<FooNode>(NULL), std::invalid_argument);
    }

    /**
     * Checks that Node::removeChild(Node*) works correctly.
     */
    void testRemoveChild() {

        // Make parent and child nodes
        FooNode parent;
        BarNode child;

        // Add child
        parent.addChild(&child);
        CPPUNIT_ASSERT(parent.hasChildren());

        // Remove child
        parent.removeChild(&child);
        CPPUNIT_ASSERT(!parent.hasChildren());
        CPPUNIT_ASSERT_EQUAL((RapidGL::Node*) NULL, child.getParent());
    }

    CPPUNIT_TEST_SUITE(NodeTest);
    CPPUNIT_TEST(testAddChild);
    CPPUNIT_TEST(testFindAncestorNodeStringWithAncestorOfTypeAndWithId);
    CPPUNIT_TEST(testFindAncestorNodeStringWithEmptyId);
    CPPUNIT_TEST(testFindAncestorNodeStringWithNoAncestorOfType);
    CPPUNIT_TEST(testFindAncestorNodeStringWithNoAncestorWithId);
    CPPUNIT_TEST(testFindAncestorNodeStringWithNoParent);
    CPPUNIT_TEST(testFindAncestorNodeStringWithNullNode);
    CPPUNIT_TEST(testFindAncestorNodeWithAncestorOfType);
    CPPUNIT_TEST(testFindAncestorNodeWithNoAncestorOfType);
    CPPUNIT_TEST(testFindAncestorNodeWithNoParent);
    CPPUNIT_TEST(testFindAncestorNodeWithNull);
    CPPUNIT_TEST(testRemoveChild);
    CPPUNIT_TEST_SUITE_END();
};

int main(int argc, char* argv[]) {
    CppUnit::TextUi::TestRunner runner;
    runner.addTest(NodeTest::suite());
    runner.run();
}
