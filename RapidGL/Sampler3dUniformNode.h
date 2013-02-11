/*
 * RapidGL - Rapid prototyping for OpenGL
 * Copyright (C) 2013  Andrew Brown
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
#ifndef RAPIDGL_SAMPLER3D_UNIFORM_NODE_H
#define RAPIDGL_SAMPLER3D_UNIFORM_NODE_H
#include <string>
#include "RapidGL/common.h"
#include "RapidGL/State.h"
#include "RapidGL/TextureNode.h"
#include "RapidGL/UniformNode.h"
namespace RapidGL {


/**
 * Node representing a `sampler3D` uniform in a shader.
 */
class Sampler3dUniformNode : public UniformNode {
public:
// Methods
    Sampler3dUniformNode(const std::string& name, const std::string& link);
    virtual ~Sampler3dUniformNode();
    std::string getLink() const;
    Gloop::TextureUnit getTextureUnit() const;
    virtual void preVisit(State& state);
    virtual void visit(State& state);
private:
// Constants
    static const GLenum TYPE = GL_SAMPLER_3D;
// Attributes
    bool prepared;
    const std::string link;
    Gloop::TextureUnit unit;
};

} /* namespace RapidGL */
#endif
