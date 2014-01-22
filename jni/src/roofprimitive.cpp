/* RoofPrimitive.cpp -  Draws the tunnel roof. Used by the tunnels in rectangular form
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

#include "glos.h"
#include "pi.h"
#include "mesh.h"

#include "roofprimitive.h"


static const int ELEMS = 19 * 4 * 3;
static GLfloat vertex[ELEMS];

RoofPrimitive::RoofPrimitive(): meshdata(nullptr), elems(19)
{
    meshdata = new Mesh*[elems];
    for (int i = 0; i < elems; i++)
        meshdata[i] = nullptr;


    GLfloat lastX = 5.5;
    GLfloat lastY = 0.5;

    for (int i = 0; i < elems; i++) {
        GLfloat angle = UTIL_TO_RADIANS(10.0f * (i + 1));
        meshdata[i] = new Mesh(3, Mesh::RenderMode::triangle_fan);
        meshdata[i]->reserveMeshSize(12);

        meshdata[i]->addVertex(lastX, lastY, 2.5);
        meshdata[i]->addVertex(lastX, lastY, -2.5);


        GLfloat x = 5.5f * cos(angle);
        GLfloat y = 0.5f + 5.5f * sin(angle);

        meshdata[i]->addVertex(x, y, -2.5);
        meshdata[i]->addVertex(x, y, 2.5);

        lastX = x;
        lastY = y;
    }
}

RoofPrimitive::~RoofPrimitive()
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

void RoofPrimitive::setColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
    if (meshdata != nullptr) {
        for (int i = 0; i < elems; i++)
        if (meshdata[i] != nullptr) {
            meshdata[i]->setColor(r, g, b, a);
        }
    }

}


void RoofPrimitive::render()
{
    if (meshdata != nullptr) {
        for (int i = 0; i < elems; i++)
        if (meshdata[i] != nullptr) {
            meshdata[i]->render();
        }
    }
}