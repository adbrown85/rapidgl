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
#ifndef RAPIDGL_READER_HXX
#define RAPIDGL_READER_HXX
#include <iostream>
#include <map>
#include <stack>
#include <string>
#include "Poco/SAX/Attributes.h"
#include "Poco/SAX/DefaultHandler.h"
#include "Poco/SAX/InputSource.h"
#include "Poco/SAX/Locator.h"
#include "Poco/SAX/SAXParser.h"
#include "RapidGL/common.h"
#include "RapidGL/Node.hxx"
#include "RapidGL/Unmarshaller.hxx"
namespace RapidGL {


/**
 * Utility for reading a scene from a stream.
 */
class Reader : public Poco::XML::DefaultHandler {
public:
// Methods
    Reader();
    virtual ~Reader();
    void addUnmarshaller(const std::string& name, Unmarshaller* unmarshaller);
    void endElement(const std::string& uri, const std::string& localName, const std::string& qname);
    void startElement(const std::string&, const std::string&, const std::string&, const Poco::XML::Attributes&);
    Node* read(std::istream& stream);
private:
// Attributes
    std::map<std::string,Unmarshaller*> unmarshallers;
    std::stack<Node*> nodeStack;
    Poco::XML::SAXParser parser;
    Node* rootNode;
};

} /* namespace RapidGL */
#endif
