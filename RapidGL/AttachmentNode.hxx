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
#ifndef RAPIDGL_ATTACHMENT_NODE_HXX
#define RAPIDGL_ATTACHMENT_NODE_HXX
#include <map>
#include <string>
#include "RapidGL/common.h"
#include "RapidGL/Node.hxx"
#include "RapidGL/State.hxx"
namespace RapidGL {


/**
 * Attachment for a framebuffer.
 */
class AttachmentNode : public Node {
public:
// Types
    /// How attachment should be used.
    enum Usage {
        COLOR, ///< As a color attachment
        DEPTH, ///< As a depth attachment
        STENCIL ///< As a stencil attachment
    };
// Methods
    AttachmentNode(Usage usage);
    virtual ~AttachmentNode();
    virtual void attach(GLenum attachment) = 0;
    Usage getUsage() const;
    static Usage parseUsage(const std::string& str);
    virtual void visit(State& state);
private:
// Constants
    static const std::map<std::string,Usage> USAGES_BY_NAME;
// Attributes
    const Usage usage;
// Methods
    static std::map<std::string,Usage> createUsagesByName();
};

} /* namespace RapidGL */
#endif
