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
#ifndef RAPIDGL_CULL_NODE_UNMARSHALLER_H
#define RAPIDGL_CULL_NODE_UNMARSHALLER_H
#include <map>
#include <string>
#include "RapidGL/common.h"
#include "RapidGL/CullNode.h"
#include "RapidGL/Node.h"
#include "RapidGL/Unmarshaller.h"
namespace RapidGL {


/**
 * Unmarshaller for `CullNode`.
 */
class CullNodeUnmarshaller : public Unmarshaller {
public:
// Methods
    CullNodeUnmarshaller();
    virtual ~CullNodeUnmarshaller();
    virtual Node* unmarshal(const std::map<std::string,std::string>& attributes);
private:
// Attributes
    const std::map<std::string,GLenum> modesByValue;
// Methods
    static std::map<std::string,GLenum> createModesByValue();
    GLenum getMode(const std::map<std::string,std::string>& attributes);
};

} /* namespace RapidGL */
#endif
