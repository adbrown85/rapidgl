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
#ifndef RAPIDGL_SCENE_NODE_UNMARSHALLER_HXX
#define RAPIDGL_SCENE_NODE_UNMARSHALLER_HXX
#include <map>
#include <string>
#include "RapidGL/common.h"
#include "RapidGL/Node.hxx"
#include "RapidGL/SceneNode.hxx"
#include "RapidGL/Unmarshaller.hxx"
namespace RapidGL {


/**
 * Unmarshaller for a `SceneNode`.
 */
class SceneNodeUnmarshaller : public Unmarshaller {
public:
// Methods
    SceneNodeUnmarshaller();
    virtual ~SceneNodeUnmarshaller();
    virtual Node* unmarshal(const std::map<std::string,std::string>& attributes);
};

} /* namespace RapidGL */
#endif
