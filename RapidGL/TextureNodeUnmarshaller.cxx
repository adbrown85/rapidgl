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
#include "config.h"
#include <gloop/TextureObject.hxx>
#include <gloop/TextureTarget.hxx>
#include <gloop/TextureUnit.hxx>
#include <glycerin/Bitmap.hxx>
#include <glycerin/BitmapReader.hxx>
#include <glycerin/Volume.hxx>
#include <glycerin/VolumeReader.hxx>
#include <Poco/Path.h>
#include <Poco/String.h>
#include "RapidGL/TextureNodeUnmarshaller.hxx"
namespace RapidGL {

/**
 * Constructs a `TextureNodeUnmarshaller`.
 */
TextureNodeUnmarshaller::TextureNodeUnmarshaller() {
    // empty
}

/**
 * Destructs a `TextureNodeUnmarshaller`.
 */
TextureNodeUnmarshaller::~TextureNodeUnmarshaller() {
    /// empty
}

Node* TextureNodeUnmarshaller::createNodeFromBitmap(const std::string& id, const Glycerin::Bitmap& bitmap) {

    // Activate texture unit
    const Gloop::TextureUnit unit = Gloop::TextureUnit::fromEnum(GL_TEXTURE0);
    unit.activate();

    // Create texture
    const Gloop::TextureObject texture = bitmap.createTexture();

    // Create the node
    return new TextureNode(id, Gloop::TextureTarget::texture2d(), texture);
}

Node* TextureNodeUnmarshaller::createNodeFromFile(const std::string& id, const std::string& file) {
    const Poco::Path path(file);
    const std::string extension = path.getExtension();
    if (Poco::icompare(extension, "bmp") == 0) {
        return createNodeFromBitmap(id, Glycerin::BitmapReader().read(file));
    } else if (Poco::icompare(extension, "vlb") == 0) {
        return createNodeFromVolume(id, Glycerin::VolumeReader().read(file));
    } else {
        throw std::runtime_error("[TextureNodeUnmarshaller] File type unrecognized!");
    }
}

Node* TextureNodeUnmarshaller::createNodeFromSize(const std::string& id, const GLint size) {

    // Generate a new texture
    const Gloop::TextureObject texture = Gloop::TextureObject::generate();

    // Activate texture unit
    const Gloop::TextureUnit unit = Gloop::TextureUnit::fromEnum(GL_TEXTURE0);
    unit.activate();

    // Bind texture
    const Gloop::TextureTarget target = Gloop::TextureTarget::texture2d();
    target.bind(texture);

    // Allocate
    target.texImage2d(
            0,                // level
            GL_RGBA,          // internal format
            size,             // width
            size,             // height
            GL_RGBA,          // format
            GL_UNSIGNED_BYTE, // type
            NULL);            // data

    // Create the node
    return new TextureNode(id, target, texture);
}

Node* TextureNodeUnmarshaller::createNodeFromVolume(const std::string& id, const Glycerin::Volume& volume) {

    // Activate texture unit
    const Gloop::TextureUnit unit = Gloop::TextureUnit::fromEnum(GL_TEXTURE0);
    unit.activate();

    // Create texture
    const Gloop::TextureObject texture = volume.createTexture();

    // Create the node
    return new TextureNode(id, Gloop::TextureTarget::texture3d(), texture);
}

std::string TextureNodeUnmarshaller::getFile(const std::map<std::string,std::string>& attributes) {
    return findValue(attributes, "file");
}

std::string TextureNodeUnmarshaller::getId(const std::map<std::string,std::string>& attributes) {
    const std::string id = findValue(attributes, "id");
    if (id.empty()) {
        throw std::runtime_error("[TextureNodeUnmarshaller] Must specify 'id'!");
    }
    return id;
}

GLint TextureNodeUnmarshaller::getSize(const std::map<std::string,std::string>& attributes) {

    // Find value
    const std::string size = findValue(attributes, "size");

    // Return -1 if unspecified
    if (size.empty()) {
        return -1;
    }

    // Parse the value
    GLfloat value;
    try {
        value = parseFloat(size);
    } catch (std::invalid_argument& e) {
        throw std::runtime_error("[TextureNodeUnmarshaller] Size is invalid!");
    }

    // Check range
    if (value < 1) {
        throw std::runtime_error("[TextureNodeUnmarshaller] Size must be at least one!");
    }

    // Return value
    return value;
}

Node* TextureNodeUnmarshaller::unmarshal(const std::map<std::string,std::string>& attributes) {

    // Get values
    const std::string id = getId(attributes);
    const std::string file = getFile(attributes);
    const GLint size = getSize(attributes);

    // Make node
    if (!file.empty() && (size != -1)) {
        throw std::runtime_error("[TextureNodeUnmarshaller] Cannot specify both 'file' and 'size'!");
    } else if (file.empty() && (size == -1)) {
        throw std::runtime_error("[TextureNodeUnmarshaller] Must specify 'file' or 'size'!");
    } else if (file.empty()) {
        return createNodeFromSize(id, size);
    } else {
        return createNodeFromFile(id, file);
    }
}

} /* namespace RapidGL */
