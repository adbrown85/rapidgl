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
#ifndef RAPIDGL_SHADERNODEUNMARSHALLER_HXX
#define RAPIDGL_SHADERNODEUNMARSHALLER_HXX
#include "RapidGL/common.h"
#include "RapidGL/ShaderNode.hxx"
#include "RapidGL/Unmarshaller.hxx"
namespace RapidGL {


/**
 * Unmarshaller for ShaderNode.
 */
class ShaderNodeUnmarshaller : public Unmarshaller {
public:
// Methods
    ShaderNodeUnmarshaller();
    virtual Node* unmarshal(const std::map<std::string,std::string>& attributes);
private:
// Constants
    static const int BUFFER_SIZE = 2048;
// Methods
    static std::string copyFile(const std::string& path);
    static std::string getFile(const std::map<std::string,std::string>& attributes);
    static GLenum getType(const std::map<std::string,std::string>& attributes);
};

} /* namespace RapidGL */
#endif
