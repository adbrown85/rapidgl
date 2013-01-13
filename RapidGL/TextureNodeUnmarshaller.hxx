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
#ifndef RAPIDGL_TEXTURE_NODE_UNMARSHALLER_HXX
#define RAPIDGL_TEXTURE_NODE_UNMARSHALLER_HXX
#include <map>
#include <string>
#include <glycerin/Bitmap.hxx>
#include <glycerin/Volume.hxx>
#include "RapidGL/common.h"
#include "RapidGL/Node.hxx"
#include "RapidGL/TextureNode.hxx"
#include "RapidGL/Unmarshaller.hxx"
namespace RapidGL {


/**
 * Functor reading in a `TextureNode` from XML.
 */
class TextureNodeUnmarshaller : public Unmarshaller {
public:
// Methods
    TextureNodeUnmarshaller();
    virtual ~TextureNodeUnmarshaller();
    virtual Node* unmarshal(const std::map<std::string,std::string>& attributes);
private:
// Methods
    Node* createNodeFromBitmap(const std::string& name, const Glycerin::Bitmap& bitmap);
    Node* createNodeFromFile(const std::string& name, const std::string& file);
    Node* createNodeFromSize(const std::string& name, GLint size);
    Node* createNodeFromVolume(const std::string& name, const Glycerin::Volume& volume);
    std::string getFile(const std::map<std::string,std::string>& attributes);
    std::string getId(const std::map<std::string,std::string>& attributes);
    GLint getSize(const std::map<std::string,std::string>& attributes);
};

} /* namespace RapidGL */
#endif
