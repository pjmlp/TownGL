/* windmillprimitive.cpp -  Represents a Windmill that can be rendered.
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

#include "c++14.h"
#include "glos.h"
#include "pi.h"
#include "mesh.h"
#include "cylinderprimitive.h"
#include "windmillprimitive.h"

WindmillPrimitive::WindmillPrimitive(const glm::mat4 &transform) : drawAngle(0.0f)
{
    auto base = std::make_unique<CylinderPrimitive>(1.0f, 1.0f, 1.0f);
    base->setColor(0.4f, 0.5f, 0, 0);  // brown
    base->setTransform(transform);
    addChild(std::move(base));
    
    
    auto roof = std::make_unique<CylinderPrimitive>(1.0f, 0.0f, 0.5f);

    glm::mat4 roofTransform = glm::translate(transform, glm::vec3(0.0f, 1.0f, 0.0f));
    roof->setTransform(roofTransform);
    roof->setColor(1, 0, 0, 0);   // red
    addChild(std::move(roof));

    glm::mat4 sailsTransform = glm::translate(transform, glm::vec3(0.0f, 1.0f, 1.0f));
    createSails(sailsTransform);
}

WindmillPrimitive::~WindmillPrimitive()
{

}

void WindmillPrimitive::update(GLfloat frame)
{
    /* temporary move here, this code should be removed when the framerate is fixed */
    drawAngle += 10 * frame;
    if (drawAngle > 360)
        drawAngle -= 360;

}

void WindmillPrimitive::createSails(const glm::mat4 &transform)
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

    addChild(std::move(sails));
    addChild(std::move(sailLines));
}
