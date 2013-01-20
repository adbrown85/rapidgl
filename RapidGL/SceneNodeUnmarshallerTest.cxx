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
#include <map>
#include <string>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/ui/text/TestRunner.h>
#include "RapidGL/Node.h"
#include "RapidGL/SceneNode.h"
#include "RapidGL/SceneNodeUnmarshaller.h"


/**
 * Unit test for `SceneNodeUnmarshaller`.
 */
class SceneNodeUnmarshallerTest : public CppUnit::TestFixture {
public:

    // Instance to use for testing
    RapidGL::Unmarshaller* const unmarshaller;

    /**
     * Constructs the test.
     */
    SceneNodeUnmarshallerTest() : unmarshaller(new RapidGL::SceneNodeUnmarshaller()) {
        // empty
    }

    /**
     * Ensures `SceneNodeUnmarshaller::unmarshal` returns a `SceneNode`.
     */
    void testUnmarshal() {
        const std::map<std::string,std::string> attributes;
        RapidGL::Node* node = unmarshaller->unmarshal(attributes);
        CPPUNIT_ASSERT(dynamic_cast<RapidGL::SceneNode*>(node) != NULL);
    }

    CPPUNIT_TEST_SUITE(SceneNodeUnmarshallerTest);
    CPPUNIT_TEST(testUnmarshal);
    CPPUNIT_TEST_SUITE_END();
};

int main(int argc, char* argv[]) {
    CppUnit::TextUi::TestRunner runner;
    runner.addTest(SceneNodeUnmarshallerTest::suite());
    runner.run();
    return 0;
}
