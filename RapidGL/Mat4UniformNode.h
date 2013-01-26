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
#ifndef RAPIDGL_MAT4_UNIFORM_NODE_H
#define RAPIDGL_MAT4_UNIFORM_NODE_H
#include <string>
#include <m3d/Mat4.h>
#include "RapidGL/common.h"
#include "RapidGL/UniformNode.h"
namespace RapidGL {


/**
 * Node representing a 4x4 matrix uniform variable in a shader program.
 */
class Mat4UniformNode : public UniformNode {
public:
// Types
    /// Type of matrix a `Mat4UniformNode` should load when it's visited.
    enum Usage {
        IDENTITY, ///< Identity matrix
        MODEL, ///< Model matrix
        MODEL_VIEW, ///< Concatenation of model and view matrices
        MODEL_VIEW_PROJECTION, ///< Concatenation of model, view, and projection matrices
        PROJECTION, ///< Projection matrix
        VIEW, ///< View matrix
        VIEW_PROJECTION ///< Concatenation of view and projection matrices
    };
// Methods
    Mat4UniformNode(const std::string& name, Usage usage);
    Usage getUsage() const;
    M3d::Mat4 getValue() const;
    static Usage parseUsage(const std::string& str);
    virtual void visit(State& state);
private:
// Constants
    static std::map<std::string,Usage> usagesByName;
// Attributes
    const Usage usage;
    M3d::Mat4 value;
// Methods
    static std::map<std::string,Usage> createUsagesByName();
    static M3d::Mat4 getMatrixFromState(const State& state, Usage usage);
};

} /* namespace RapidGL */
#endif
