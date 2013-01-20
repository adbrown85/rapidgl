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
#include <stdexcept>
#include <vector>
#include <m3d/Math.hxx>
#include <m3d/Quat.hxx>
#include "RapidGL/RotateNodeUnmarshaller.h"
namespace RapidGL {

/**
 * Constructs a `RotateNodeUnmarshaller`.
 */
RotateNodeUnmarshaller::RotateNodeUnmarshaller() {
    // empty
}

/**
 * Destructs a `RotateNodeUnmarshaller`.
 */
RotateNodeUnmarshaller::~RotateNodeUnmarshaller() {
    // empty
}

/**
 * Finds the value of the _angle_ attribute in a map.
 *
 * @param attributes Map of attribute keys and values to look in
 * @return Value of angle attribute
 * @throws std::runtime_error if value is unspecified or invalid
 */
double RotateNodeUnmarshaller::getAngle(const std::map<std::string,std::string>& attributes) {

    // Get value
    const std::string value = findValue(attributes,  "angle");
    if (value.empty()) {
        throw std::runtime_error("[RotateNodeUnmarshaller] Angle is unspecified!");
    }

    // Parse value
    try {
        return M3d::toRadians(parseFloat(value));
    } catch (std::invalid_argument& e) {
        throw std::runtime_error("[RotateNodeUnmarshaller] Invalid value for angle!");
    }
}

/**
 * Finds the value of the _axis_ attribute in a map.
 *
 * @param attributes Map of attribute keys and values to look in
 * @return Value of axis attribute
 * @throws std::runtime_error if value is unspecified or invalid
 */
M3d::Vec3 RotateNodeUnmarshaller::getAxis(const std::map<std::string,std::string>& attributes) {

    // Get value
    const std::string value = findValue(attributes, "axis");
    if (value.empty()) {
        throw std::runtime_error("[RotateNodeUnmarshaller] Axis is unspecified!");
    }

    // Tokenize value
    const std::vector<std::string> tokens = tokenize(value);
    if (tokens.size() != 3) {
        throw std::runtime_error("[RotateNodeUnmarshaller] Axis should have three components!");
    }

    // Parse tokens
    M3d::Vec3 axis;
    try {
        for (int i = 0; i < 3; ++i) {
            axis[i] = parseFloat(tokens[i]);
        }
    } catch (std::invalid_argument& e) {
        throw std::runtime_error("[RotateNodeUnmarshaller] Invalid value for axis!");
    }

    // Return axis
    return axis;
}

Node* RotateNodeUnmarshaller::unmarshal(const std::map<std::string,std::string>& attributes) {
    const M3d::Vec3 axis = getAxis(attributes);
    const double angle = getAngle(attributes);
    const M3d::Quat rotation = M3d::Quat::fromAxisAngle(axis, angle);
    return new RotateNode(rotation);
}

} /* namespace RapidGL */
