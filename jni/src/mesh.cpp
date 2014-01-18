/* mesh.cpp -  Represents a Mesh that can be rendered.
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
#include "mesh.h"

//#include "SDL.h"
//#include <iostream>

Mesh::Mesh() : idx(0), vertex(nullptr), vertexCount(0)
{
    // nothing to do
    //SDL_Log("Hi");
}

Mesh::~Mesh()
{
	// nothing to do
  //  SDL_Log("Bye");
    if (vertex) {
        delete[] vertex;
    }
}

void Mesh::render()
{
    if (vertex != nullptr && idx > 0) {
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(2, GL_FLOAT, 0, vertex);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, idx);
        glDisableClientState(GL_VERTEX_ARRAY);
    }
}

void Mesh::reserveMeshSize(GLint count)
{
    vertexCount = count;
    vertex = new GLfloat[count];
    idx = 0;
}

void Mesh::addVertex(GLfloat x, GLfloat y)
{
    if (vertex != nullptr && idx + 2 < vertexCount) {
        vertex[idx++] = x;
        vertex[idx++] = y;
    }
}