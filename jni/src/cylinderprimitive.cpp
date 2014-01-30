/* CylinderPrimitive.cpp -  Represents a cylinder circle.
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

#include <cassert>
#include <cmath>

#include "mesh.h"
#include "pi.h"

#include "cylinderprimitive.h"



static const int slices = 20;

/**
 * @param lowerRadius the lower radius of the cylinder.
 * @param upperRadius the upper radius of the cylinder.
 * @param height the cylinder height
 */
CylinderPrimitive::CylinderPrimitive(GLfloat lowerRadius, GLfloat upperRadius, GLfloat height)
{
    // bottom circle
    meshdata.push_back(std::unique_ptr<Mesh>(new Mesh(3, Mesh::RenderMode::triangle_fan)));
    meshdata[0]->addVertex(0.0f, 0.0f, 0.0f);
    for (int i = 0; i <= slices; i++) {
        GLfloat angle = static_cast<GLfloat>(i) / slices * 2 * PI;

        meshdata[0]->addVertex(cos(angle)*lowerRadius, 0.0f, sin(angle)*lowerRadius);
    }

    // top circle
    meshdata.push_back(std::unique_ptr<Mesh>(new Mesh(3, Mesh::RenderMode::triangle_fan)));
    meshdata[1]->addVertex(0.0f, height, 0.0f);
    for (int i = 0; i <= slices; i++) {
        GLfloat angle = static_cast<GLfloat>(i) / slices * 2 * PI;

        meshdata[1]->addVertex(cos(angle)*upperRadius, height, sin(angle)*upperRadius);
    }

    // the rest
    meshdata.push_back(std::unique_ptr<Mesh>(new Mesh(3, Mesh::RenderMode::triangle_strip)));
    for (int i = 0; i <= slices; i++) {
        GLfloat angle = static_cast<GLfloat>(i) / slices * 2 * PI;

        meshdata[2]->addVertex(cos(angle)*lowerRadius, 0.0f, sin(angle)*lowerRadius);

        meshdata[2]->addVertex(cos(angle)*upperRadius, height, sin(angle)*upperRadius);
    }
}

CylinderPrimitive::~CylinderPrimitive()
{
    // Nothing to do
}

void CylinderPrimitive::setColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
    for (auto& mesh : meshdata)
        mesh->setColor(r, g, b, a);
}

void CylinderPrimitive::render ()
{
    for (auto& mesh : meshdata)
        mesh->render();
}
