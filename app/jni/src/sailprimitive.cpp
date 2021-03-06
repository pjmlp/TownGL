/* sail.cpp -  Represents sails used by Windmills.
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

#include <cmath>
#include <memory>

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "glos.h"
#include "pi.h"
#include "mesh.h"

#include "sailprimitive.h"

Sail::Sail(const glm::mat4 &transform) : drawAngle(0.0f), sailsTransform(transform)
{
    GLfloat length = 0.75f;
    const GLint elems = 12;

    GLfloat angle;
    GLfloat maxAngle = 2 * PI;
    GLfloat angleSlice = maxAngle / static_cast<GLfloat>(elems);

    auto sails = std::make_unique<Mesh>(3, Mesh::RenderMode::triangles);
    auto sailLines = std::make_unique<Mesh>(3, Mesh::RenderMode::line_strip);
    for (angle = 0; angle < maxAngle; angle += angleSlice) {
        GLfloat x = length * cos(angle);
        GLfloat y = length * sin(angle);
        sails->addVertex(x, y, 0.0f);
        sails->addVertex(0.0f, 0.0f, 0.0f);

        sailLines->addVertex(x, y, 0.0f);

        angle += angleSlice;
        x = length * cos(angle);
        y = length * sin(angle);

        sails->addVertex(x, y, 0.0f);

        sailLines->addVertex(x, y, 0.0f);
    }
    sailLines->addVertex(length * cos(angle), length * sin(angle), 0.0f);

    sails->setColor(1.0f, 0.8f, 0.0f, 0.0f); //yellow
    sailLines->setColor(1.0f, 0.8f, 0.0f, 0.0f); //yellow

    sails->setTransform(transform);
    sailLines->setTransform(transform);

    sails->upload();
    sailLines->upload();
    addChild(std::move(sails));
    addChild(std::move(sailLines));
}

Sail::~Sail()
{
    // nothing to do
}

void Sail::update(GLfloat frame)
{
    drawAngle += 15 * frame;
    if (drawAngle > 360)
        drawAngle -= 360;

    glm::mat4 transform = glm::rotate(sailsTransform, toRadians(drawAngle), glm::vec3(0.0f, 0.0f, 1.0f));
    setTransform(transform);
}
