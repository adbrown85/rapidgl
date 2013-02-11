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
#ifndef RAPIDGL_PROGRAMNODE_H
#define RAPIDGL_PROGRAMNODE_H
#include <gloop/Program.hxx>
#include "RapidGL/common.h"
#include "RapidGL/AttributeNode.h"
#include "RapidGL/Node.h"
#include "RapidGL/ShaderNode.h"
#include "RapidGL/State.h"
namespace RapidGL {


/**
 * Node representing a shader program.
 */
class ProgramNode : public Node {
public:
// Methods
    ProgramNode(const std::string& id);
    virtual ~ProgramNode();
    Gloop::Program getProgram() const;
    virtual void preVisit(State& state);
    virtual void visit(State& state);
private:
// Attributes
    bool prepared;
    Gloop::Program program;
};

const ProgramNode* findProgramNode(const Node* root, const Gloop::Program& program);

} /* namespace RapidGL */
#endif
