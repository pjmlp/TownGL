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
#include <memory>

#include "c++14.h"

#include "glos.h"

#include "mesh.h"
#include "pi.h"

#include "cylinderprimitive.h"


/**
 * @param lowerRadius the lower radius of the cylinder.
 * @param upperRadius the upper radius of the cylinder.
 * @param height the cylinder height
 */
CylinderPrimitive::CylinderPrimitive(GLfloat lowerRadius, GLfloat upperRadius, GLfloat height)
{
    const int slices = 20;

    // bottom circle
    auto mesh = std::make_unique<Mesh>(3, Mesh::RenderMode::triangle_fan);
    mesh->addVertex(0.0f, 0.0f, 0.0f);
    for (int i = 0; i < slices; i++) {
        GLfloat angle = static_cast<GLfloat>(i) / static_cast<GLfloat>(slices) * 2 * PI;

        mesh->addVertex(cos(angle)*lowerRadius, 0.0f, sin(angle)*lowerRadius);
    }
    mesh->addVertex(0.0f, 0.0f, lowerRadius);
    addChild(std::move(mesh));

    // top circle
    mesh = std::make_unique<Mesh>(3, Mesh::RenderMode::triangle_fan);
    mesh->addVertex(0.0f, height, 0.0f);
    for (int i = 0; i < slices; i++) {
        GLfloat angle = static_cast<GLfloat>(i) / static_cast<GLfloat>(slices)* 2 * PI;

        mesh->addVertex(cos(angle)*upperRadius, height, sin(angle)*upperRadius);
    }
    mesh->addVertex(0.0f, height, upperRadius);
    addChild(std::move(mesh));

    // the rest
    mesh = std::make_unique<Mesh>(3, Mesh::RenderMode::triangles);
    for (int i = 0; i < slices; i++) {
        GLfloat angle = static_cast<GLfloat>(i) / static_cast<GLfloat>(slices) * 2 * PI;
        GLfloat nextAngle = static_cast<GLfloat>(i+1) / static_cast<GLfloat>(slices)* 2 * PI;

        // first one
        mesh->addVertex(cos(angle)*upperRadius, height, sin(angle)*upperRadius);
        mesh->addVertex(cos(angle)*lowerRadius, 0.0f, sin(angle)*lowerRadius);
        mesh->addVertex(cos(nextAngle)*upperRadius, height, sin(nextAngle)*upperRadius);

        // second one
        mesh->addVertex(cos(nextAngle)*upperRadius, height, sin(nextAngle)*upperRadius);
        mesh->addVertex(cos(angle)*lowerRadius, 0.0f, sin(angle)*lowerRadius);
        mesh->addVertex(cos(nextAngle)*lowerRadius, 0.0f, sin(nextAngle)*lowerRadius);

    }
    addChild(std::move(mesh));
}

CylinderPrimitive::~CylinderPrimitive()
{
    // Nothing to do
}
