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
#ifndef RAPIDGL_COMMON_H
#define RAPIDGL_COMMON_H
#include <cstdlib>
#ifdef __APPLE__
#define GL3_PROTOTYPES
#include <OpenGL/gl3.h>
#else
#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>
#include <GL/glext.h>
#include <GL/glx.h>
#endif

#ifndef SIZE_MAX
#define SIZE_MAX ((size_t) -1)
#endif

namespace RapidGL {


/**
 * Pair of iterators.
 */
template<typename T>
struct Range {

    /**
     * Iterator for the beginning of this range.
     */
    T begin;

    /**
     * Iterator for the end of this range.
     */
    T end;

    /**
     * Constructs a range from two iterators.
     *
     * @param begin Iterator for the beginning of this range
     * @param end Iterator for the end of this range
     */
    Range(const T& begin, const T& end) : begin(begin), end(end) {
        // empty
    }
};

} /* namespace RapidGL */

#endif
