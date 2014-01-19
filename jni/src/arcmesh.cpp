/* arcmesh.cpp -  Represents an Arc that can be rendered.
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
#include "arcmesh.h"


/**
 * @param depth How long the arch is.
 */
ArcMesh::ArcMesh(GLfloat depth) : meshdata(nullptr), elems(19)
{
    meshdata = new Mesh*[elems];
    for (int i = 0; i < elems; i++)
        meshdata[i] = nullptr;

    
    GLfloat lastXTop = 5.5;
    GLfloat lastYTop = 0.5;
    GLfloat lastXBottom = 4.5;
    GLfloat lastYBottom = 0.5;

    for (int i = 0, angle = 10; i < elems && angle < 180; i++, angle += 10) {
        meshdata[i] = new Mesh(3, Mesh::RenderMode::triangle_fan);
        meshdata[i]->reserveMeshSize(12);

        meshdata[i]->addVertex(lastXBottom, lastYBottom, depth);
        meshdata[i]->addVertex(lastXTop, lastYTop, depth);

        GLfloat x = 5.5f * cos(UTIL_TO_RADIANS(static_cast<GLfloat>(angle)));
        GLfloat y = 0.5f + 5.5f * sin(UTIL_TO_RADIANS(static_cast<GLfloat>(angle)));

        meshdata[i]->addVertex(x, y, depth);

        lastXTop = x;
        lastYTop = y;

        x = 4.5f * cos(UTIL_TO_RADIANS(static_cast<GLfloat>(angle)));
        y = 0.5f + 4.5f * sin(UTIL_TO_RADIANS(static_cast<GLfloat>(angle)));

        meshdata[i]->addVertex(x, y, depth);

        lastXBottom = x;
        lastYBottom = y;
    }
}

ArcMesh::~ArcMesh()
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

void ArcMesh::render()
{
    if (meshdata != nullptr) {
        for (int i = 0; i < elems; i++)
        if (meshdata[i] != nullptr) {
            meshdata[i]->render();
        }
    }
}
