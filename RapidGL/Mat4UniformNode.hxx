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
#ifndef RAPIDGL_MAT4_UNIFORM_NODE_HXX
#define RAPIDGL_MAT4_UNIFORM_NODE_HXX
#include <string>
#include <m3d/Mat4.hxx>
#include "RapidGL/common.h"
#include "RapidGL/UniformNode.hxx"
namespace RapidGL {


/**
 * Node representing a 4x4 matrix uniform variable in a shader program.
 */
class Mat4UniformNode : public UniformNode {
public:
// Types
    enum Usage {
        IDENTITY,
        MODEL,
        MODEL_VIEW,
        MODEL_VIEW_PROJECTION,
        PROJECTION,
        VIEW,
        VIEW_PROJECTION
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
