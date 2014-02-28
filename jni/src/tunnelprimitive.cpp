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

#include <memory>

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>


#include "glos.h"

#include "tunnelprimitive.h"


TunnelPrimitive::TunnelPrimitive(const glm::mat4 &transform)
{
    auto box = std::make_unique<BoxPrimitive>(1.0f, 1.0f, 5.0f);
    glm::mat4 transformTunnel = glm::translate(transform, glm::vec3(-5.0f, 0.0f, 0.0f));
    box->setTransform(transformTunnel);
    addChild(std::move(box));

    box = std::make_unique<BoxPrimitive>(1.0f, 1.0f, 5.0f);
    transformTunnel = glm::translate(transform, glm::vec3(5, 0, 0));
    box->setTransform(transformTunnel);
    addChild(std::move(box));

    box = std::make_unique<BoxPrimitive>(11.0f, 0.10f, 5.0f);
    transformTunnel = glm::translate(transform, glm::vec3(0, 0.55f, 0));
    box->setTransform(transformTunnel);
    addChild(std::move(box));

    setColor(1.0f, 0.8f, 0.0f, 0.0f); //yellow

}

TunnelPrimitive::~TunnelPrimitive()
{
    // Nothing to do
}