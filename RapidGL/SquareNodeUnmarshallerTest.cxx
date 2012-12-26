#include "config.h"
#include <cppunit/extensions/HelperMacros.h>
#include <GL/glfw.h>
#include <iostream>
#include <map>
#include <string>
#include "RapidGL/SquareNodeUnmarshaller.hxx"


/**
 * Unit test for SquareNodeUnmarshaller.
 */
class SquareNodeUnmarshallerTest {
public:

    // Instance to use for testing
    RapidGL::SquareNodeUnmarshaller unmarshaller;

    /**
     * Ensures `unmarshal` works correctly.
     */
    void testUnmarshal() {
        std::map<std::string,std::string> map;
        RapidGL::Node* node = unmarshaller.unmarshal(map);
        CPPUNIT_ASSERT(dynamic_cast<RapidGL::SquareNode*>(node) != NULL);
    }
};

int main(int argc, char* argv[]) {

    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Could not initialize GLFW!" << std::endl;
        return 1;
    }

    // Open a window
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 2);
    glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    if (!glfwOpenWindow(512, 512, 0, 0, 0, 0, 0, 0, GLFW_WINDOW)) {
        std::cerr << "Could not open GLFW window!" << std::endl;
        return 1;
    }

    // Run test
    try {
        SquareNodeUnmarshallerTest test;
        test.testUnmarshal();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    // Exit
    glfwTerminate();
    return 0;
}
