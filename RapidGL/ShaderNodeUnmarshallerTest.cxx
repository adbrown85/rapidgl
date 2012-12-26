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
#include <cppunit/extensions/HelperMacros.h>
#include <GL/glfw.h>
#include "RapidGL/ShaderNode.hxx"
#include "RapidGL/ShaderNodeUnmarshaller.hxx"


/**
 * Unit test for ShaderNodeUnmarshaller.
 */
class ShaderNodeUnmarshallerTest {
public:

    // Unmarshaller used to test
    RapidGL::ShaderNodeUnmarshaller unmarshaller;

    /**
     * Ensures that ShaderNodeUnmarshaller::unmarshal works correctly.
     */
    void testUnmarshal() {

        // Make a map of attributes
        std::map<std::string,std::string> attributes;
        attributes["type"] = "fragment";
        attributes["file"] = "RapidGL/solid.frag";

        // Unmarshal the node
        RapidGL::Node* node = unmarshaller.unmarshal(attributes);
        RapidGL::ShaderNode* shaderNode = dynamic_cast<RapidGL::ShaderNode*>(node);

        // Check fields
        Gloop::Shader shader = shaderNode->getShader();
        CPPUNIT_ASSERT_EQUAL((GLenum) GL_FRAGMENT_SHADER, shader.type());
        CPPUNIT_ASSERT_EQUAL(
                std::string(
                "#version 140\n"
                "\n"
                "// Uniforms\n"
                "uniform vec4 Color = vec4(1.0);\n"
                "\n"
                "// Outputs\n"
                "out vec4 FragColor;\n"
                "\n"
                "/*\n"
                " * Colors the fragment a solid color.\n"
                " */\n"
                "void main() {\n"
                "    FragColor = Color;\n"
                "}\n"),
                shader.source());
    }
};

int main(int argc, char* argv[]) {

    // Capture the initial working directory before GLFW changes it
#ifdef __APPLE__
    char* const cwd = new char[PATH_MAX];
    if (!getcwd(cwd, PATH_MAX)) {
        std::cerr << "Could not get current working directory!" << std::endl;
        return 1;
    }
#endif

    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Could not initialize GLFW!" << std::endl;
        return 1;
    }

    // Reset current directory
#ifdef __APPLE__
    chdir(cwd);
    delete[] cwd;
#endif

    // Open window
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 2);
    glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwOpenWindow(512, 512, 0, 0, 0, 0, 0, 0, GLFW_WINDOW);

    // Run test
    ShaderNodeUnmarshallerTest test;
    try {
        test.testUnmarshal();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        throw;
    }

    // Exit
    glfwTerminate();
    return 0;
}
