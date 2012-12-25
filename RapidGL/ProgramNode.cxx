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
#include "RapidGL/ProgramNode.hxx"
namespace RapidGL {

/**
 * Constructs a program node.
 */
ProgramNode::ProgramNode() : program(Gloop::Program::create()) {
    prepared = false;
}

/**
 * Destructs this program node.
 */
ProgramNode::~ProgramNode() {
    program.dispose();
}

/**
 * Returns the underlying OpenGL shader program.
 *
 * @return Underlying OpenGL shader program
 */
Gloop::Program ProgramNode::getProgram() const {
    return program;
}

void ProgramNode::preVisit(State& state) {

    // Skip if already prepared
    if (prepared) {
        return;
    }

    // Find and attach shaders
    const node_range_t children = getChildren();
    for (node_iterator_t it = children.begin; it != children.end; ++it) {
        ShaderNode* const shaderNode = dynamic_cast<ShaderNode*>(*it);
        if (shaderNode != NULL) {
            program.attachShader(shaderNode->getShader());
        }
    }

    // Link
    program.link();
    if (!program.linked()) {
        throw std::runtime_error("[ProgramNode] Program could not be linked!");
    }

    // Successfully prepared
    prepared = true;
}

void ProgramNode::visit(State& state) {
    program.use();
}

} /* namespace RapidGL */
