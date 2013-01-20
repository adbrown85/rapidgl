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
#include "config.h"
#include <Poco/String.h>
#include "RapidGL/AttachmentNode.hxx"
namespace RapidGL {
using std::map;
using std::string;

// Usages indexed by their name
const map<string,AttachmentNode::Usage> AttachmentNode::USAGES_BY_NAME = AttachmentNode::createUsagesByName();

/**
 * Constructs an `AttachmentNode`.
 *
 * @param usage What kind of attachment this node should be used as, e.g. `COLOR`
 */
AttachmentNode::AttachmentNode(const Usage usage) : usage(usage) {
    // empty
}

/**
 * Destructs an `AttachmentNode`.
 */
AttachmentNode::~AttachmentNode() {
    // empty
}

/**
 * Attaches the item represented by this node to the currently bound framebuffer.
 *
 * @param attachment Attachment point to attach to, e.g. `GL_COLOR_ATTACHMENT0` or `GL_DEPTH_ATTACHMENT`
 * @throws std::runtime_error if could not make the attachment
 */
void AttachmentNode::attach(GLenum attachment) {
    // empty
}

/**
 * Creates the map of usages indexed by name.
 *
 * @return Map of usages indexed by name
 */
map<string,AttachmentNode::Usage> AttachmentNode::createUsagesByName() {
    map<string,AttachmentNode::Usage> usagesByName;
    usagesByName["COLOR"] = COLOR;
    usagesByName["DEPTH"] = DEPTH;
    usagesByName["STENCIL"] = STENCIL;
    return usagesByName;
}

/**
 * Returns what kind of attachment this node should be used as.
 *
 * @return What kind of attachment this node should be used as
 */
AttachmentNode::Usage AttachmentNode::getUsage() const {
    return usage;
}

/**
 * Parses a usage from a string.
 *
 * @param str String to parse
 * @return Resulting usage
 * @throws std::invalid_argument if string is not a valid usage
 */
AttachmentNode::Usage AttachmentNode::parseUsage(const std::string& str) {
    const string strAsUpper = Poco::toUpper(str);
    map<string,AttachmentNode::Usage>::const_iterator it = USAGES_BY_NAME.find(strAsUpper);
    if (it == USAGES_BY_NAME.end()) {
        throw std::invalid_argument("String is not a valid usage!");
    } else {
        return it->second;
    }
}

void AttachmentNode::visit(State& state) {
    // empty
}

} /* namespace RapidGL */
