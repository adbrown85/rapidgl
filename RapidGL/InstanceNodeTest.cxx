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
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/ui/text/TestRunner.h>
#include "RapidGL/GroupNode.h"
#include "RapidGL/InstanceNode.h"
#include "RapidGL/Node.h"
#include "RapidGL/SceneNode.h"
#include "RapidGL/State.h"


/**
 * Unit test for `InstanceNode`.
 */
class InstanceNodeTest : public CppUnit::TestFixture {
public:

    /**
     * Fake node used for testing.
     */
    class FakeNode : public RapidGL::Node {
    private:
        bool visited;
    public:
        FakeNode() : visited(false) { }
        virtual void visit(RapidGL::State& state) { visited = true; }
        bool isVisited() { return visited; }
    };

    // Reusable state since `InstanceNode` doesn't use it
    RapidGL::State state;

    /**
     * Ensures constructor throws if passed an empty link.
     */
    void testInstanceNodeWithEmptyLink() {
        CPPUNIT_ASSERT_THROW(RapidGL::InstanceNode(""), std::invalid_argument);
    }

    /**
     * Ensures constructor works if passed a valid link.
     */
    void testInstanceNodeWithValidLink() {
        const RapidGL::InstanceNode instanceNode("foo");
        CPPUNIT_ASSERT_EQUAL(std::string("foo"), instanceNode.getLink());
    }

    /**
     * Ensures `InstanceNode::preVisit` throws if specified group is not in scene.
     */
    void testPreVisitWhenGroupIsAbsent() {

        // Make nodes
        RapidGL::SceneNode sceneNode;
        RapidGL::GroupNode groupNode("foo");
        RapidGL::InstanceNode instanceNode("bar");

        // Connect nodes
        sceneNode.addChild(&groupNode);
        sceneNode.addChild(&instanceNode);

        // Check
        CPPUNIT_ASSERT_THROW(instanceNode.preVisit(state), std::runtime_error);
    }

    /**
     * Ensures `InstanceNode::preVisit` works if specified group is in scene.
     */
    void testPreVisitWhenGroupIsPresent() {

        // Make nodes
        RapidGL::SceneNode sceneNode;
        RapidGL::GroupNode groupNode("foo");
        RapidGL::InstanceNode instanceNode("foo");

        // Connect nodes
        sceneNode.addChild(&groupNode);
        sceneNode.addChild(&instanceNode);

        // Check
        CPPUNIT_ASSERT_NO_THROW(instanceNode.preVisit(state));
    }

    /**
     * Ensures `InstanceNode::visit` works correctly.
     */
    void testVisit() {

        // Make nodes
        RapidGL::SceneNode sceneNode;
        RapidGL::GroupNode groupNode("foo");
        FakeNode fakeNode;
        RapidGL::InstanceNode instanceNode("foo");

        // Connect nodes
        sceneNode.addChild(&groupNode);
        groupNode.addChild(&fakeNode);
        sceneNode.addChild(&instanceNode);

        // Visit instance node
        instanceNode.preVisit(state);
        instanceNode.visit(state);

        // Check
        CPPUNIT_ASSERT(fakeNode.isVisited());
    }

    CPPUNIT_TEST_SUITE(InstanceNodeTest);
    CPPUNIT_TEST(testInstanceNodeWithEmptyLink);
    CPPUNIT_TEST(testInstanceNodeWithValidLink);
    CPPUNIT_TEST(testPreVisitWhenGroupIsAbsent);
    CPPUNIT_TEST(testPreVisitWhenGroupIsPresent);
    CPPUNIT_TEST(testVisit);
    CPPUNIT_TEST_SUITE_END();
};


int main(int argc, char* argv[]) {
    CppUnit::TextUi::TestRunner runner;
    runner.addTest(InstanceNodeTest::suite());
    runner.run();
    return 0;
}
