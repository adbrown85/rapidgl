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
#ifndef RAPIDGL_USE_NODE_HXX
#define RAPIDGL_USE_NODE_HXX
#include "RapidGL/common.h"
#include "RapidGL/Node.h"
#include "RapidGL/ProgramNode.h"
#include "RapidGL/State.h"
namespace RapidGL {


/**
 * Node for using a program.
 */
class UseNode : public Node {
public:
// Methods
    UseNode(const std::string& programNodeId);
    virtual ~UseNode();
    ProgramNode* getProgramNode() const;
    virtual void postVisit(State& state);
    virtual void preVisit(State& state);
    virtual void visit(State& state);
private:
// Attributes
    const std::string programNodeId;
    ProgramNode* programNode;
    UseNode* lastUseNode;
};

} /* namespace RapidGL */
#endif
