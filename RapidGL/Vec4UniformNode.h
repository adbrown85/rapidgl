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
#ifndef RAPIDGL_VEC4_UNIFORM_NODE_H
#define RAPIDGL_VEC4_UNIFORM_NODE_H
#include <m3d/Vec4.h>
#include <string>
#include "RapidGL/common.h"
#include "RapidGL/Node.h"
#include "RapidGL/State.h"
#include "RapidGL/UniformNode.h"
namespace RapidGL {


/**
 * Node representing a 4-component vector uniform variable in a shader program.
 */
class Vec4UniformNode : public UniformNode {
public:
// Methods
    Vec4UniformNode(const std::string& name);
    Vec4UniformNode(const std::string& name, const M3d::Vec4& value);
    M3d::Vec4 getValue() const;
    void setValue(const M3d::Vec4& value);
    virtual void visit(State& state);
private:
// Constants
    static const GLenum TYPE = GL_FLOAT_VEC4;
// Attributes
    M3d::Vec4 value;
};

} /* namespace RapidGL */
#endif
