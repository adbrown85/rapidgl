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
#include <exception>
#include <iostream>
#include <stdexcept>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/ui/text/TestRunner.h>
#include "RapidGL/AttachmentNode.hxx"
using RapidGL::AttachmentNode;


/**
 * Unit test for `AttachmentNode`.
 */
class AttachmentNodeTest : public CppUnit::TestFixture {
public:

    /**
     * Fake `AttachmentNode` implementation for testing.
     */
    class FakeAttachmentNode : public AttachmentNode {
    public:

        FakeAttachmentNode(AttachmentNode::Usage usage) : AttachmentNode(usage) {
            // empty
        }

        void attach(GLenum attachment) {
            // empty
        }
    };

    /**
     * Ensures `AttachmentNode::getUsage` works when usage is `COLOR`.
     */
    void testGetUsageWhenColor() {
        const AttachmentNode::Usage expected = AttachmentNode::COLOR;
        FakeAttachmentNode node(expected);
        CPPUNIT_ASSERT_EQUAL(expected, node.getUsage());
    }

    /**
     * Ensures `AttachmentNode::getUsage` works when usage is `DEPTH`.
     */
    void testGetUsageWhenDepth() {
        const AttachmentNode::Usage expected = AttachmentNode::DEPTH;
        FakeAttachmentNode node(expected);
        CPPUNIT_ASSERT_EQUAL(expected, node.getUsage());
    }

    /**
     * Ensures `AttachmentNode::getUsage` works when usage is `STENCIL`.
     */
    void testGetUsageWhenStencil() {
        const AttachmentNode::Usage expected = AttachmentNode::STENCIL;
        FakeAttachmentNode node(expected);
        CPPUNIT_ASSERT_EQUAL(expected, node.getUsage());
    }

    /**
     * Ensures `AttachmentNode::parseUsage` works with _COLOR_.
     */
    void testParseUsageWithColor() {
        CPPUNIT_ASSERT_EQUAL(AttachmentNode::COLOR, AttachmentNode::parseUsage("COLOR"));
    }

    /**
     * Ensures `AttachmentNode::parseUsage` works with _DEPTH_.
     */
    void testParseUsageWithDepth() {
        CPPUNIT_ASSERT_EQUAL(AttachmentNode::DEPTH, AttachmentNode::parseUsage("DEPTH"));
    }

    /**
     * Ensures `AttachmentNode::parseUsage` rejects _foo_.
     */
    void testParseUsageWithFoo() {
        CPPUNIT_ASSERT_THROW(AttachmentNode::parseUsage("foo"), std::invalid_argument);
    }

    /**
     * Ensures `AttachmentNode::parseUsage` works with _STENCIL.
     */
    void testParseUsageWithStencil() {
        CPPUNIT_ASSERT_EQUAL(AttachmentNode::STENCIL, AttachmentNode::parseUsage("STENCIL"));
    }

    CPPUNIT_TEST_SUITE(AttachmentNodeTest);
    CPPUNIT_TEST(testGetUsageWhenColor);
    CPPUNIT_TEST(testGetUsageWhenDepth);
    CPPUNIT_TEST(testGetUsageWhenStencil);
    CPPUNIT_TEST(testParseUsageWithColor);
    CPPUNIT_TEST(testParseUsageWithDepth);
    CPPUNIT_TEST(testParseUsageWithFoo);
    CPPUNIT_TEST(testParseUsageWithStencil);
    CPPUNIT_TEST_SUITE_END();
};

int main(int argc, char* argv[]) {
    CppUnit::TextUi::TestRunner runner;
    runner.addTest(AttachmentNodeTest::suite());
    runner.run();
    return 0;
}
