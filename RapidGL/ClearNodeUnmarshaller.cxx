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
#include "RapidGL/ClearNodeUnmarshaller.hxx"
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

    // Create the node
    ClearNode* const clearNode = new ClearNode();

    // Parse for red
    const map<string,string>::const_iterator red = attributes.find("red");
    if (red != attributes.end()) {
        const GLfloat value = atof(red->second.c_str());
        clearNode->setRed(value);
    }

    // Parse for green
    const map<string,string>::const_iterator green = attributes.find("green");
    if (green != attributes.end()) {
        const GLfloat value = atof(green->second.c_str());
        clearNode->setGreen(value);
    }

    // Parse for blue
    const map<string,string>::const_iterator blue = attributes.find("blue");
    if (blue != attributes.end()) {
        const GLfloat value = atof(blue->second.c_str());
        clearNode->setBlue(value);
    }

    // Parse for alpha
    const map<string,string>::const_iterator alpha = attributes.find("alpha");
    if (alpha != attributes.end()) {
        const GLfloat value = atof(alpha->second.c_str());
        clearNode->setAlpha(value);
    }

    // Return the node
    return clearNode;
}

} /* namespace RapidGL */