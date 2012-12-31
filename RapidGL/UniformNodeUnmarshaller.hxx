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
#ifndef RAPIDGL_UNIFORM_NODE_UNMARSHALLER_HXX
#define RAPIDGL_UNIFORM_NODE_UNMARSHALLER_HXX
#include <map>
#include <string>
#include "RapidGL/Node.hxx"
#include "RapidGL/FloatUniformNode.hxx"
#include "RapidGL/Mat3UniformNode.hxx"
#include "RapidGL/Mat4UniformNode.hxx"
#include "RapidGL/Unmarshaller.hxx"
#include "RapidGL/Vec3UniformNode.hxx"
#include "RapidGL/Vec4UniformNode.hxx"
namespace RapidGL {


/**
 * Unmarshaller for all types of uniforms.
 */
class UniformNodeUnmarshaller : public Unmarshaller {
public:
    UniformNodeUnmarshaller();
    virtual ~UniformNodeUnmarshaller();
    virtual Node* unmarshal(const std::map<std::string,std::string>& attributes);
private:
// Types
    struct Creator {
        virtual Node* create(const std::string& name, const std::string& value) const = 0;
    };
    struct FloatUniformNodeCreator : public Creator {
        virtual Node* create(const std::string& name, const std::string& value) const;
    };
    struct Mat3UniformNodeCreator : public Creator {
        virtual Node* create(const std::string& name, const std::string& value) const;
    };
    struct Mat4UniformNodeCreator : public Creator {
        virtual Node* create(const std::string& name, const std::string& value) const;
    };
    struct Vec3UniformNodeCreator : public Creator {
        virtual Node* create(const std::string& name, const std::string& value) const;
    };
    struct Vec4UniformNodeCreator : public Creator {
        virtual Node* create(const std::string& name, const std::string& value) const;
    };
// Constants
    static std::map<std::string,Creator*> creatorsByType;
// Methods
    static std::map<std::string,Creator*> createCreatorsByType();
    static std::string getName(const std::map<std::string,std::string>& attributes);
    static std::string getType(const std::map<std::string,std::string>& attributes);
    static std::string getValue(const std::map<std::string,std::string>& attributes);
    static bool isValidType(const std::string& str);
};

} /* namespace RapidGL */
#endif