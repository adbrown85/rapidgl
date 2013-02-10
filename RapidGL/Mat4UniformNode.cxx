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
#include "Poco/String.h"
#include "RapidGL/Mat4UniformNode.h"
namespace RapidGL {

// Map of usages by their name
std::map<std::string,Mat4UniformNode::Usage> Mat4UniformNode::usagesByName = createUsagesByName();

/**
 * Constructs a `Mat4UniformNode`.
 *
 * @param name Name of uniform as declared in the shader
 * @param usage How the uniform should be used, e.g. `MODEL_VIEW_PROJECTION`
 * @throws invalid_argument if name is empty
 */
Mat4UniformNode::Mat4UniformNode(const std::string& name, const Usage usage) :
        UniformNode(name, GL_FLOAT_MAT4),
        value(M3d::Mat4(1)),
        usage(usage) {
    // empty
}

std::map<std::string,Mat4UniformNode::Usage> Mat4UniformNode::createUsagesByName() {
    std::map<std::string,Mat4UniformNode::Usage> usagesByName;
    usagesByName["IDENTITY"] = IDENTITY;
    usagesByName["MODEL"] = MODEL;
    usagesByName["MODELVIEW"] = MODEL_VIEW;
    usagesByName["MODEL_VIEW"] = MODEL_VIEW;
    usagesByName["MODELVIEWPROJECTION"] = MODEL_VIEW_PROJECTION;
    usagesByName["MODEL_VIEW_PROJECTION"] = MODEL_VIEW_PROJECTION;
    usagesByName["PROJECTION"] = PROJECTION;
    usagesByName["VIEW"] = VIEW;
    usagesByName["VIEWPROJECTION"] = VIEW_PROJECTION;
    usagesByName["VIEW_PROJECTION"] = VIEW_PROJECTION;
    return usagesByName;
}

/**
 * Returns the value of a matrix in a `State`.
 *
 * @param state State to get matrix value from
 * @param usage Usage determining what matrix to get
 * @throws std::runtime_error if usage is unexpected
 */
M3d::Mat4 Mat4UniformNode::getMatrixFromState(const State& state, const Usage usage) {
    switch (usage) {
    case MODEL:
        return state.getModelMatrix();
    case MODEL_VIEW:
        return state.getModelViewMatrix();
    case MODEL_VIEW_PROJECTION:
        return state.getModelViewProjectionMatrix();
    case PROJECTION:
        return state.getProjectionMatrix();
    case VIEW:
        return state.getViewMatrix();
    case VIEW_PROJECTION:
        return state.getViewProjectionMatrix();
    default:
        throw std::runtime_error("[Mat4UniformNode] Unexpected usage!");
    }
}

/**
 * Returns how the uniform node is used.
 *
 * @return How the uniform node is used
 */
Mat4UniformNode::Usage Mat4UniformNode::getUsage() const {
    return usage;
}

/**
 * Returns a copy of the uniform's value.
 *
 * @return Copy of the uniform's value
 */
M3d::Mat4 Mat4UniformNode::getValue() const {
    return value;
}

/**
 * Parses a usage from a string.
 *
 * @param str String to parse
 * @return Corresponding usage for string
 * @throws std::invalid_argument if string could not be parsed as a valid usage
 */
Mat4UniformNode::Usage Mat4UniformNode::parseUsage(const std::string& str) {
    const std::string strAsUpperCase = Poco::toUpper(str);
    std::map<std::string,Usage>::const_iterator it = usagesByName.find(strAsUpperCase);
    if (it == usagesByName.end()) {
        throw std::invalid_argument("[Mat4UniformNode] String is not a valid usage!");
    } else {
        return it->second;
    }
}

void Mat4UniformNode::visit(State& state) {

    // Get the location
    const GLint location = getLocationInProgram(Gloop::Program::current());
    if (location < 0) {
        return;
    }

    // Get the value
    if (usage != IDENTITY) {
        value = getMatrixFromState(state, usage);
    }

    // Load the value
    GLfloat arr[16];
    value.toArrayInColumnMajor(arr);
    glUniformMatrix4fv(location, 1, false, arr);
}

} /* namespace RapidGL */
