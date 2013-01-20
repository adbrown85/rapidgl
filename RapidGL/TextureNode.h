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
#ifndef RAPIDGL_TEXTURE_NODE_H
#define RAPIDGL_TEXTURE_NODE_H
#include <gloop/TextureObject.hxx>
#include <gloop/TextureTarget.hxx>
#include <gloop/TextureUnit.hxx>
#include <string>
#include "RapidGL/common.h"
#include "RapidGL/Node.h"
namespace RapidGL {


/**
 * Node representing a texture.
 */
class TextureNode : public Node {
public:
// Methods
    TextureNode(const std::string& id, const Gloop::TextureTarget&, const Gloop::TextureObject&);
    virtual ~TextureNode();
    Gloop::TextureObject getTextureObject() const;
    Gloop::TextureTarget getTextureTarget() const;
    Gloop::TextureUnit getTextureUnit() const;
    virtual void preVisit(State& state);
    virtual void visit(State& state);
private:
// Attributes
    const Gloop::TextureObject texture;
    const Gloop::TextureTarget target;
    Gloop::TextureUnit unit;
    bool prepared;
};

} /* namespace RapidGL */
#endif
