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
#include <map>
#include <stdexcept>
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


/**
 * Checks if a map contains a key.
 *
 * @param map Map to look in
 * @param key Key to look for
 * @return `true` if map contains key
 */
template<typename K, typename V>
bool containsKey(std::map<K,V> map, K key) {
    typename std::map<K,V>::const_iterator it = map.find(key);
    return it != map.end();
}


/**
 * Gets the value of a key in a map.
 *
 * @param map Map to look in
 * @param key Key to get value of
 * @return Value of key
 * @throws std::runtime_error if key is not in map
 */
template<typename K, typename V>
V getValueOfKey(std::map<K,V> map, K key) {
    typename std::map<K,V>::const_iterator it = map.find(key);
    if (it == map.end()) {
        throw std::runtime_error("Key is not in map!");
    } else {
        return it->second;
    }
}

} /* namespace RapidGL */

#endif
