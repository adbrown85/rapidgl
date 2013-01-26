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
#include <m3d/Vec3.h>
#include "RapidGL/TranslateNodeUnmarshaller.h"
namespace RapidGL {

/**
 * Constructs a `TranslateNodeUnmarshaller`.
 */
TranslateNodeUnmarshaller::TranslateNodeUnmarshaller() {
    // empty
}

/**
 * Destructs a `TranslateNodeUnmarshaller`.
 */
TranslateNodeUnmarshaller::~TranslateNodeUnmarshaller() {
    // empty
}

Node* TranslateNodeUnmarshaller::unmarshal(const std::map<std::string,std::string>& attributes) {

    // Make value
    M3d::Vec3 value;

    // Get x
    const std::string x = findValue(attributes, "x");
    if (!x.empty()) {
        try {
            value.x = parseFloat(x);
        } catch (std::invalid_argument& e) {
            throw std::runtime_error("[TranslateNodeUnmarshaller] X value is invalid!");
        }
    }

    // Get y
    const std::string y = findValue(attributes, "y");
    if (!y.empty()) {
        try {
            value.y = parseFloat(y);
        } catch (std::invalid_argument& e) {
            throw std::runtime_error("[TranslateNodeUnmarshaller] Y value is invalid!");
        }
    }

    // Get z
    const std::string z = findValue(attributes, "z");
    if (!z.empty()) {
        try {
            value.z = parseFloat(z);
        } catch (std::invalid_argument& e) {
            throw std::runtime_error("[TranslateNodeUnmarshaller] Z value is invalid!");
        }
    }

    // Make node
    return new TranslateNode(value);
}

} /* namespace RapidGL */
