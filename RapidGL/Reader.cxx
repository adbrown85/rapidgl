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
#include <stdexcept>
#include "RapidGL/Reader.hxx"
namespace RapidGL {

/**
 * Constructs a reader.
 */
Reader::Reader() {
    rootNode = NULL;
    parser.setContentHandler(this);
}

/**
 * Destroys the reader.
 */
Reader::~Reader() {
    // empty
}

/**
 * Adds an unmarshaller to the reader.
 *
 * @param name Name of XML element to unmarshal
 * @param unmarshaller Pointer to unmarshaller, which is still owned by caller
 * @throws invalid_argument if name is empty or unmarshaller is `NULL`
 */
void Reader::addUnmarshaller(const std::string& name, Unmarshaller* unmarshaller) {

    if (name.empty()) {
        throw std::invalid_argument("Name is empty!");
    } else if (unmarshaller == NULL) {
        throw std::invalid_argument("Unmarshaller is NULL!");
    }

    unmarshallers[name] = unmarshaller;
}

void Reader::endElement(const std::string& uri, const std::string& localName, const std::string& qname) {
    std::map<std::string,Unmarshaller*>::const_iterator it = unmarshallers.find(localName);
    if ((it != unmarshallers.end()) && !nodeStack.empty()) {
        nodeStack.pop();
    }
}

/**
 * Reads a scene from a stream.
 *
 * @param stream Stream to read from
 * @return Root node of scene
 */
Node* Reader::read(std::istream& stream) {

    // Reset
    rootNode = NULL;
    while (!nodeStack.empty()) {
        nodeStack.pop();
    }

    // Parse the stream
    Poco::XML::InputSource source(stream);
    parser.parse(&source);

    // Return the root node
    return rootNode;
}

void Reader::startElement(const std::string& uri,
                          const std::string& localName,
                          const std::string& qname,
                          const Poco::XML::Attributes& attrList) {

    // Find the unmarshaller
    std::map<std::string,Unmarshaller*>::const_iterator it = unmarshallers.find(localName);
    if (it == unmarshallers.end()) {
        return;
    }
    Unmarshaller* const unmarshaller = it->second;

    // Convert the attributes list to a map
    std::map<std::string,std::string> attrMap;
    const int len = attrList.getLength();
    for (int i = 0; i < len; ++i ) {
        const std::string key = attrList.getLocalName(i);
        const std::string value = attrList.getValue(i);
        attrMap[key] = value;
    }

    // Unmarshal the node
    Node* const node = unmarshaller->unmarshal(attrMap);
    if (node == NULL) {
        throw std::runtime_error("[Reader] Unmarshaller returned NULL!");
    }

    // Update pointers
    if (nodeStack.empty()) {
        if (rootNode == NULL) {
            rootNode = node;
        } else {
            throw std::runtime_error("[Reader] Multiple roots detected!");
        }
    } else {
        Node* const parent = nodeStack.top();
        parent->addChild(node);
    }

    // Store node on the stack
    nodeStack.push(node);
}

} /* namespace RapidGL */
