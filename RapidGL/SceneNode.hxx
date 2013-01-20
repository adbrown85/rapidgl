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
#ifndef RAPIDGL_SCENE_NODE_HXX
#define RAPIDGL_SCENE_NODE_HXX
#include "RapidGL/common.h"
#include "RapidGL/Node.hxx"
#include "RapidGL/State.hxx"
namespace RapidGL {


/**
 * Node intended to be the root of a scene.
 */
class SceneNode : public Node {
public:
// Methods
    SceneNode();
    virtual ~SceneNode();
    virtual void visit(State& state);
};

} /* namespace RapidGL */
#endif
