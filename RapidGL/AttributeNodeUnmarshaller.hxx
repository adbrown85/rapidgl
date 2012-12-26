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
#ifndef RAPIDGL_ATTRIBUTE_NODE_UNMARSHALLER_HXX
#define RAPIDGL_ATTRIBUTE_NODE_UNMARSHALLER_HXX
#include <map>
#include <string>
#include "RapidGL/common.h"
#include "RapidGL/AttributeNode.hxx"
#include "RapidGL/Node.hxx"
#include "RapidGL/Unmarshaller.hxx"
namespace RapidGL {


/**
 * Unmarshaller for attribute nodes.
 */
class AttributeNodeUnmarshaller : public Unmarshaller {
public:
// Methods
    AttributeNodeUnmarshaller();
    virtual ~AttributeNodeUnmarshaller();
    virtual Node* unmarshal(const std::map<std::string,std::string>& attributes);
private:
// Methods
    static std::string getName(const std::map<std::string,std::string>& attributes);
    static AttributeNode::Usage getUsage(const std::map<std::string,std::string>& attributes);
};

} /* namespace RapidGL */
#endif