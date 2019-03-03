/* world.h - Interface for the model drawing functions for the town
* Copyright (C) 2012 Paulo Pinto
*
* This library is free software; you can redistribute it and/or
* modify it under the terms of the GNU Lesser General Public
* License as published by the Free Software Foundation; either
* version 2 of the License, or (at your option) any later version.
*
* This library is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
* Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public
* License along with this library; if not, write to the
* Free Software Foundation, Inc., 59 Temple Place - Suite 330,
* Boston, MA 02111-1307, USA.
*/
#ifndef WORLD_H_
#define WORLD_H_

// for the compilers that support it. a bit faster than include guards
#pragma once

#include <vector>
#include <memory>

#include <glm/glm.hpp>
#include <glm/mat4x4.hpp>

#include "glos.h"

#include "primitive.h"
#include "effect.h"

/**
 * Represents the 3D world being shown.
 */
class World
{
public:
    void createScene();

    void update(GLfloat frame);
    void render();

    void setWorldMatrix(const glm::mat4& world);

private:
    glm::mat4 worldMatrix;
    std::vector<std::unique_ptr<Primitive>> objects;
    Effect shaders;
};

#endif /* WORLD_H_ */