/* arctunnelprimitive.cpp -  Represents an arc tunnel that can be rendered.
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

#include "c++14.h"

#include "boxprimitive.h"
#include "arcprimitive.h"
#include "roofprimitive.h"

#include "arctunnelprimitive.h"

ArcTunnelPrimitive::ArcTunnelPrimitive(const glm::mat4 &transform)
{
    addChild(std::make_unique<ArcPrimitive>(2.5f));
    addChild(std::make_unique<ArcPrimitive>(-2.5f));
    addChild(std::make_unique<RoofPrimitive>());
    setTransform(transform);

    auto modelData = std::make_unique<BoxPrimitive>(1.0f, 1.0f, 5.0f);
    glm::mat4 translate = glm::translate(transform, glm::vec3(-5, 0, 0));
    modelData->setTransform(translate);
    addChild(std::move(modelData));

    modelData = std::make_unique<BoxPrimitive>(1.0f, 1.0f, 5.0f);
    translate = glm::translate(transform, glm::vec3(5, 0, 0));
    modelData->setTransform(translate);
    addChild(std::move(modelData));

    setColor(1.0f, 0.8f, 0.0f, 0.0f); //yellow
}

ArcTunnelPrimitive::~ArcTunnelPrimitive()
{
    // Nothing to do
}
