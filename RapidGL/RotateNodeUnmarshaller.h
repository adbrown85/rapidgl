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
#ifndef RAPIDGL_ROTATE_NODE_UNMARSHALLER_H
#define RAPIDGL_ROTATE_NODE_UNMARSHALLER_H
#include <map>
#include <string>
#include <m3d/Vec3.h>
#include "RapidGL/common.h"
#include "RapidGL/Node.h"
#include "RapidGL/RotateNode.h"
#include "RapidGL/Unmarshaller.h"
namespace RapidGL {


/**
 * Unmarshaller for `RotateNode`.
 */
class RotateNodeUnmarshaller : public Unmarshaller {
public:
// Methods
    RotateNodeUnmarshaller();
    virtual ~RotateNodeUnmarshaller();
    virtual Node* unmarshal(const std::map<std::string,std::string>& attributes);
private:
// Methods
    static double getAngle(const std::map<std::string,std::string>& attributes);
    static M3d::Vec3 getAxis(const std::map<std::string,std::string>& attributes);
};

} /* namespace RapidGL */
#endif
