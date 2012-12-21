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
#include "RapidGL/Unmarshaller.hxx"
using namespace std;
namespace RapidGL {

/**
 * Constructs an unmarshaller.
 */
Unmarshaller::Unmarshaller() {
    // empty
}

/**
 * Destructs an umarshaller.
 */
Unmarshaller::~Unmarshaller() {
    // empty
}

/**
 * Unmarshals a node from XML attributes.
 *
 * @param attributes Map of attribute keys and values
 * @return New node instance for attributes, or `NULL` if could not be unmarshalled
 */
Node* Unmarshaller::unmarshal(const std::map<std::string,std::string>& attributes) {
    return NULL;
}

} /* namespace RapidGL */
