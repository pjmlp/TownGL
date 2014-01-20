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


#include "cylinderprimitive.h"
#include "pi.h"


static const int slices = 20;

/**
 * @param lowerRadius the lower radius of the cylinder.
 * @param upperRadius the upper radius of the cylinder.
 * @param height the cylinder height
 */
CylinderPrimitive::CylinderPrimitive(GLfloat lowerRadius, GLfloat upperRadius, GLfloat height) : meshdata(nullptr), elems(3)
{

    meshdata = new Mesh*[elems];
    for (int i = 0; i < elems; i++)
        meshdata[i] = nullptr;

    // bottom circle
    meshdata[0] = new Mesh(3, Mesh::RenderMode::triangle_fan);
    meshdata[0]->reserveMeshSize(slices * 3);
    meshdata[0]->addVertex(0.0f, 0.0f, 0.0f);
    for (int i = 0; i <= slices; i++) {
        GLfloat angle = static_cast<GLfloat>(i) / slices * 2 * PI;

        meshdata[0]->addVertex(cos(angle)*lowerRadius, 0.0f, sin(angle)*lowerRadius);
    }

    // top circle
    meshdata[1] = new Mesh(3, Mesh::RenderMode::triangle_fan);
    meshdata[1]->reserveMeshSize(slices * 3);
    meshdata[1]->addVertex(0.0f, height, 0.0f);
    for (int i = 0; i <= slices; i++) {
        GLfloat angle = static_cast<GLfloat>(i) / slices * 2 * PI;

        meshdata[1]->addVertex(cos(angle)*upperRadius, height, sin(angle)*upperRadius);
    }

    // the rest
    meshdata[2] = new Mesh(3, Mesh::RenderMode::triangle_strip);
    meshdata[2]->reserveMeshSize(slices * 3);
    for (int i = 0; i <= slices; i++) {
        GLfloat angle = static_cast<GLfloat>(i) / slices * 2 * PI;

        meshdata[2]->addVertex(cos(angle)*lowerRadius, 0.0f, sin(angle)*lowerRadius);

        meshdata[2]->addVertex(cos(angle)*upperRadius, height, sin(angle)*upperRadius);
    }
}

CylinderPrimitive::~CylinderPrimitive()
{
    if (meshdata != nullptr) {
        for (int i = 0; i < elems; i++)
        if (meshdata[i] != nullptr) {
            delete meshdata[i];
            meshdata[i] = nullptr;
        }
        delete[] meshdata;
    }
}


void CylinderPrimitive::render ()
{

    if (meshdata != nullptr) {
        for (int i = 0; i < elems; i++)
        if (meshdata[i] != nullptr) {
            meshdata[i]->render();
        }
    }
}


void CylinderPrimitive::setColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
    if (meshdata != nullptr) {
        for (int i = 0; i < elems; i++)
        if (meshdata[i] != nullptr) {
            meshdata[i]->setColor(r, g, b, a);
        }
    }

}