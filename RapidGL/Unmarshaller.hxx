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
#ifndef RAPIDGL_UNMARSHALLER_HXX
#define RAPIDGL_UNMARSHALLER_HXX
#include <map>
#include <string>
#include "RapidGL/common.h"
#include "RapidGL/Node.hxx"
namespace RapidGL {


/**
 * Functor for unmarshalling a node.
 */
class Unmarshaller {
public:
// Methods
    Unmarshaller();
    virtual ~Unmarshaller();
    virtual Node* unmarshal(const std::map<std::string,std::string>& attributes) = 0;
protected:
// Methods
    static std::string findValue(const std::map<std::string,std::string>& map, const std::string& key);
    static GLfloat parseFloat(const std::string& str);
};

} /* namespace RapidGL */
#endif
