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
#include "RapidGL/ClearNodeUnmarshaller.h"
using namespace std;
namespace RapidGL {

/**
 * Constructs a ClearNodeUnmarshaller.
 */
ClearNodeUnmarshaller::ClearNodeUnmarshaller() {
    // empty
}

/**
 * Destructs this ClearNodeUnmarshaller.
 */
ClearNodeUnmarshaller::~ClearNodeUnmarshaller() {
    // empty
}

/**
 * Creates a node from a map of XML attributes.
 *
 * @param attributes Map of XML attributes
 * @return Resulting ClearNode instance
 */
Node* ClearNodeUnmarshaller::unmarshal(const std::map<std::string,std::string>& attributes) {

    // Parse for red
    GLfloat red = 0.0f;
    if (attributes.count("red") > 0) {
        try {
            red = parseFloat(attributes.find("red")->second.c_str());
        } catch (std::invalid_argument& e) {
            throw std::runtime_error("[ClearNodeUnmarshaller] Could not parse red value!");
        }
    }

    // Parse for green
    GLfloat green = 0.0f;
    if (attributes.count("green") > 0) {
        try {
            green = parseFloat(attributes.find("green")->second.c_str());
        } catch (std::invalid_argument& e) {
            throw std::runtime_error("[ClearNodeUnmarshaller] Could not parse green value!");
        }
    }

    // Parse for blue
    GLfloat blue = 0.0f;
    if (attributes.count("blue") > 0) {
        try {
            blue = parseFloat(attributes.find("blue")->second.c_str());
        } catch (std::invalid_argument& e) {
            throw std::runtime_error("[ClearNodeUnmarshaller] Could not parse blue value!");
        }
    }

    // Parse for alpha
    GLfloat alpha = 1.0f;
    if (attributes.count("alpha") > 0) {
        try {
            alpha = parseFloat(attributes.find("alpha")->second.c_str());
        } catch (std::invalid_argument& e) {
            throw std::runtime_error("[ClearNodeUnmarshaller] Could not parse alpha value!");
        }
    }

    // Return the node
    return new ClearNode(red, green, blue, alpha);
}

} /* namespace RapidGL */
