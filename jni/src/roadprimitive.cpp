/* roadprimitive.cpp -  Represents a road that can be rendered.
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

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "glos.h"

#include "roadprimitive.h"


RoadPrimitive::RoadPrimitive() : road(9, 11, 25)
{
    road.setColor(0, 0, 0, 0);

    glm::mat4 identity;
    glm::mat4 translation = glm::translate(identity, glm::vec3(0, 0.1f, 0));
    glm::mat4 transform = glm::rotate(translation, -90.0f, glm::vec3(1, 0, 0));
    road.setTransform(transform);

}

RoadPrimitive::~RoadPrimitive()
{
    // nothing to do
}

void RoadPrimitive::render()
{
    road.render();
}
