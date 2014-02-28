/* floorprimitive.cpp -  Represents a floor that can be rendered.
* Copyright (C) 2013 Paulo Pinto
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

#include <memory>

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "glos.h"

#include "floorprimitive.h"


FloorPrimitive::FloorPrimitive()
{
    auto disk = std::make_unique<DiskPrimitive>(0.0f, 50.0f, 10);
    disk->setColor(0.2f, 0.3f, 0.5f, 0.0f);

    glm::mat4 identity;
    glm::mat4 transform = glm::rotate(identity, -90.0f, glm::vec3(1, 0, 0));
    disk->setTransform(transform);
    addChild(std::move(disk));
}

FloorPrimitive::~FloorPrimitive()
{
    // nothing to do
}