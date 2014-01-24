/* tunnelprimitive.cpp -  Represents a tunnel that can be rendered.
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

#include "tunnelprimitive.h"


TunnelPrimitive::TunnelPrimitive()
{
    glm::mat4 identity;

    objects.push_back(std::unique_ptr<BoxPrimitive>(new BoxPrimitive(1.0f, 1.0f, 5.0f)));
    glm::mat4 transform = glm::translate(identity, glm::vec3(-5, 0, 0));
    objects[0]->setTransform(transform);

    objects.push_back(std::unique_ptr<BoxPrimitive>(new BoxPrimitive(1.0f, 1.0f, 5.0f)));
    transform = glm::translate(identity, glm::vec3(5, 0, 0));
    objects[1]->setTransform(transform);

    objects.push_back(std::unique_ptr<BoxPrimitive>(new BoxPrimitive(11, 0.10f, 5)));
    transform = glm::translate(identity, glm::vec3(0, 0.55f, 0));
    objects[2]->setTransform(transform);


    for (auto& mesh : objects)
        mesh->setColor(1.0f, 0.8f, 0.0f, 0.0f); //yellow
}

TunnelPrimitive::~TunnelPrimitive()
{
    // Nothing to do
}

void TunnelPrimitive::render()
{
    for (auto& mesh : objects)
        mesh->render();
}