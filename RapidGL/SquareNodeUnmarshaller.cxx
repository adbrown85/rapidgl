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
#include "RapidGL/SquareNodeUnmarshaller.h"
namespace RapidGL {

/**
 * Constructs a square node unmarshaller.
 */
SquareNodeUnmarshaller::SquareNodeUnmarshaller() {
    // empty
}

/**
 * Destructs this square node unmarshaller.
 */
SquareNodeUnmarshaller::~SquareNodeUnmarshaller() {
    // empty
}

Node* SquareNodeUnmarshaller::unmarshal(const std::map<std::string,std::string>& attributes) {
    return new SquareNode();
}

} /* namespace RapidGL */
