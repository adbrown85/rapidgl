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
#ifndef RAPIDGL_UNIFORM_NODE_H
#define RAPIDGL_UNIFORM_NODE_H
#include <string>
#include "RapidGL/common.h"
#include "RapidGL/Node.h"
#include "RapidGL/ProgramNode.h"
#include "RapidGL/State.h"
#include "RapidGL/UseNode.h"
namespace RapidGL {


/**
 * Node representing a uniform variable in a shader program.
 */
class UniformNode : public Node {
public:
// Methods
    UniformNode(const std::string& name, GLenum type);
    GLint getLocation() const;
    std::string getName() const;
    GLenum getType() const;
    virtual void preVisit(State& state);
private:
// Attributes
    std::string name;
    GLint location;
    bool prepared;
    GLenum type;
};

} /* namespace RapidGL */
#endif
