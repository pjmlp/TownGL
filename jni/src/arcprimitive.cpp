/* ArcPrimitive.cpp -  Represents an Arc that can be rendered.
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
#include "arcprimitive.h"


/**
 * @param depth How long the arch is.
 */
ArcPrimitive::ArcPrimitive(GLfloat depth) : meshdata(nullptr), elems(19)
{
    meshdata = new Mesh*[elems];
    for (int i = 0; i < elems; i++)
        meshdata[i] = nullptr;

    
    GLfloat lastXTop = 5.5;
    GLfloat lastYTop = 0.5;
    GLfloat lastXBottom = 4.5;
    GLfloat lastYBottom = 0.5;

    for (int i = 0; i < elems; i++) {
        GLfloat angle = UTIL_TO_RADIANS(10.0f * (i + 1));
        meshdata[i] = new Mesh(3, Mesh::RenderMode::triangle_fan);
        meshdata[i]->reserveMeshSize(12);

        meshdata[i]->addVertex(lastXBottom, lastYBottom, depth);
        meshdata[i]->addVertex(lastXTop, lastYTop, depth);

        GLfloat x = 5.5f * cos(angle);
        GLfloat y = 0.5f + 5.5f * sin(angle);

        meshdata[i]->addVertex(x, y, depth);

        lastXTop = x;
        lastYTop = y;

        x = 4.5f * cos(angle);
        y = 0.5f + 4.5f * sin(angle);

        meshdata[i]->addVertex(x, y, depth);

        lastXBottom = x;
        lastYBottom = y;
    }
}

ArcPrimitive::~ArcPrimitive()
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

void ArcPrimitive::setColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
    if (meshdata != nullptr) {
        for (int i = 0; i < elems; i++)
        if (meshdata[i] != nullptr) {
            meshdata[i]->setColor(r, g, b, a);
        }
    }

}


void ArcPrimitive::render()
{
    if (meshdata != nullptr) {
        for (int i = 0; i < elems; i++)
        if (meshdata[i] != nullptr) {
            meshdata[i]->render();
        }
    }
}
