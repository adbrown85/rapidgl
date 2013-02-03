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
#ifndef RAPIDGL_POLYGON_MODE_NODE_H
#define RAPIDGL_POLYGON_MODE_NODE_H
#include "RapidGL/common.h"
#include "RapidGL/Node.h"
#include "RapidGL/State.h"
namespace RapidGL {


/**
 * Node that changes how OpenGL draws polygons.
 */
class PolygonModeNode : public Node {
public:
// Methods
    PolygonModeNode(GLenum mode);
    virtual ~PolygonModeNode();
    GLenum getMode() const;
    virtual void visit(State& state);
private:
// Attributes
    const GLenum mode;
// Methods
    static bool isMode(GLenum enumeration);
};

} /* namespace RapidGL */
#endif
