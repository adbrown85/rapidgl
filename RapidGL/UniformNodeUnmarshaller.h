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
#ifndef RAPIDGL_UNIFORM_NODE_UNMARSHALLER_H
#define RAPIDGL_UNIFORM_NODE_UNMARSHALLER_H
#include <map>
#include <string>
#include "RapidGL/Node.h"
#include "RapidGL/FloatUniformNode.h"
#include "RapidGL/Mat3UniformNode.h"
#include "RapidGL/Mat4UniformNode.h"
#include "RapidGL/Unmarshaller.h"
#include "RapidGL/Sampler2dUniformNode.h"
#include "RapidGL/Sampler3dUniformNode.h"
#include "RapidGL/Vec3UniformNode.h"
#include "RapidGL/Vec4UniformNode.h"
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
    struct FloatUniformNodeUnmarshaller : public Unmarshaller {
        virtual Node* unmarshal(const std::map<std::string,std::string>& attributes);
    };
    struct Mat3UniformNodeUnmarshaller : public Unmarshaller {
        virtual Node* unmarshal(const std::map<std::string,std::string>& attributes);
    };
    struct Mat4UniformNodeUnmarshaller : public Unmarshaller {
        virtual Node* unmarshal(const std::map<std::string,std::string>& attributes);
    };
    struct Sampler2dUniformNodeUnmarshaller : public Unmarshaller {
        virtual Node* unmarshal(const std::map<std::string,std::string>& attributes);
    };
    struct Sampler3dUniformNodeUnmarshaller : public Unmarshaller {
        virtual Node* unmarshal(const std::map<std::string,std::string>& attributes);
    };
    struct Vec3UniformNodeUnmarshaller : public Unmarshaller {
        virtual Node* unmarshal(const std::map<std::string,std::string>& attributes);
    };
    struct Vec4UniformNodeUnmarshaller : public Unmarshaller {
        virtual Node* unmarshal(const std::map<std::string,std::string>& attributes);
    };
// Constants
    static std::map<std::string,Unmarshaller*> delegatesByType;
// Methods
    static std::map<std::string,Unmarshaller*> createDelegatesByType();
    static std::string getLink(const std::map<std::string,std::string>& attributes);
    static std::string getUsage(const std::map<std::string,std::string>& attributes);
    static std::string getName(const std::map<std::string,std::string>& attributes);
    static std::string getType(const std::map<std::string,std::string>& attributes);
    static std::string getValue(const std::map<std::string,std::string>& attributes);
    static bool isValidType(const std::string& str);
};

} /* namespace RapidGL */
#endif
