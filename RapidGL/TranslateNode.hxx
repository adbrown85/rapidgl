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
#ifndef RAPIDGL_TRANSLATE_NODE_HXX
#define RAPIDGL_TRANSLATE_NODE_HXX
#include <m3d/Vec3.hxx>
#include "RapidGL/common.h"
#include "RapidGL/Node.hxx"
#include "RapidGL/State.hxx"
#include "RapidGL/TransformNode.hxx"
namespace RapidGL {


/**
 * Node that translates the model matrix.
 */
class TranslateNode : public TransformNode {
public:
// Methods
    TranslateNode();
    TranslateNode(const M3d::Vec3& translation);
    virtual ~TranslateNode();
    M3d::Vec3 getTranslation() const;
    virtual void visit(State& state);
    void setTranslation(const M3d::Vec3& translation);
private:
// Attributes
    M3d::Vec3 translation;
};

} /* namespace RapidGL */
#endif
