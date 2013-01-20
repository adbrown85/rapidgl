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
#include <sstream>
#include "RapidGL/Node.hxx"
#include "RapidGL/Reader.hxx"


/**
 * Unit test for Reader.
 */
class ReaderTest : public CppUnit::TestFixture {
public:

    /**
     * Mock node for testing.
     */
    class FakeNode : public RapidGL::Node {
    public:

        FakeNode(const std::string& name) : RapidGL::Node(name) {
            // empty
        }

        virtual void visit(RapidGL::State& state) {
            // empty
        }
    };

    /**
     * Mock node umarshaller for testing.
     */
    class FakeNodeUnmarshaller : public RapidGL::Unmarshaller {
    public:
        virtual RapidGL::Node* unmarshal(const std::map<std::string,std::string>& attributes) {
            const std::map<std::string,std::string>::const_iterator id = attributes.find("id");
            if (id == attributes.end()) {
                return new FakeNode("");
            } else {
                return new FakeNode(id->second);
            }
        }
    };

    // Instance to test with
    RapidGL::Reader reader;

    /**
     * Constructs a ReaderTest.
     */
    ReaderTest() {
        reader.addUnmarshaller("fake", new FakeNodeUnmarshaller());
    }

    /**
     * Checks if a node is a FakeNode.
     *
     * @param node Node to check
     * @return `true` if node is a FakeNode
     */
    static bool isFakeNode(RapidGL::Node* node) {
        return dynamic_cast<FakeNode*>(node) != NULL;
    }

    /**
     * Ensures Reader::read(istream&) works correctly.
     */
    void testRead() {

        // Make a scene
        std::stringstream stream("<fake><fake id='foo' /><fake id='bar' /></fake>");

        // Parse the scene
        RapidGL::Node* root = reader.read(stream);
        CPPUNIT_ASSERT(root != NULL);
        CPPUNIT_ASSERT(isFakeNode(root));

        // Check the children
        CPPUNIT_ASSERT(root->hasChildren());
        RapidGL::Node::node_range_t children = root->getChildren();
        RapidGL::Node::node_iterator_t it = children.begin;
        CPPUNIT_ASSERT_EQUAL(std::string("foo"), (*(it++))->getId());
        CPPUNIT_ASSERT_EQUAL(std::string("bar"), (*(it++))->getId());
        CPPUNIT_ASSERT(it == children.end);
    }

    CPPUNIT_TEST_SUITE(ReaderTest);
    CPPUNIT_TEST(testRead);
    CPPUNIT_TEST_SUITE_END();
};

int main(int argc, char* argv[]) {
    CppUnit::TextUi::TestRunner runner;
    runner.addTest(ReaderTest::suite());
    runner.run();
    return 0;
}
