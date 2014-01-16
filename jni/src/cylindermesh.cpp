/* cylindermesh.cpp -  Represents a cylinder circle.
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


#include "cylindermesh.h"
#include "pi.h"


static const int slices = 20;

/**
 * @param lowerRadius the lower radius of the cylinder.
 * @param upperRadius the upper radius of the cylinder.
 * @param height the cylinder height
 */
CylinderMesh::CylinderMesh(GLfloat lowerRadius, GLfloat upperRadius, GLfloat height) :
 lowerVertex(nullptr), upperVertex(nullptr), roundVertex(nullptr)
{
    const int ELEMS = (slices + 1) * 3 * 2;
    lowerVertex = new GLfloat [ELEMS];
    upperVertex = new GLfloat[ELEMS];
    roundVertex = new GLfloat[ELEMS];

    int idx = 0;
    // bottom circle
    lowerVertex[idx++] = 0.0f;
    lowerVertex[idx++] = 0.0f;
    lowerVertex[idx++] = 0.0f;
    for (int i = 0; i <= slices; i++) {
        GLfloat angle = static_cast<GLfloat>(i) / slices * 2 * PI;
        lowerVertex[idx++] = cos(angle)*lowerRadius;
        lowerVertex[idx++] = 0.0f;
        lowerVertex[idx++] = sin(angle)*lowerRadius;
    }




    idx = 0;
    // top circle
    upperVertex[idx++] = 0.0f;
    upperVertex[idx++] = height;
    upperVertex[idx++] = 0.0f;
    for (int i = 0; i <= slices; i++) {
        GLfloat angle = static_cast<GLfloat>(i) / slices * 2 * PI;
        upperVertex[idx++] = cos(angle)*upperRadius;
        upperVertex[idx++] = height;
        upperVertex[idx++] = sin(angle)*upperRadius;
    }




    idx = 0;
    // the rest
    for (int i = 0; i <= slices; i++) {
        GLfloat angle = static_cast<GLfloat>(i) / slices * 2 * PI;
        roundVertex[idx++] = cos(angle)*lowerRadius;
        roundVertex[idx++] = 0.0f;
        roundVertex[idx++] = sin(angle)*lowerRadius;

        roundVertex[idx++] = cos(angle)*upperRadius;
        roundVertex[idx++] = height;
        roundVertex[idx++] = sin(angle)*upperRadius;
    }



}

CylinderMesh::~CylinderMesh() {
    if (lowerVertex) {
        delete[] lowerVertex;
	}

    if (upperVertex) {
        delete[] upperVertex;
    }

    if (roundVertex) {
        delete[] roundVertex;
    }


}


void CylinderMesh::render ()
{
    // render lower part
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, lowerVertex);
    glDrawArrays(GL_TRIANGLE_FAN, 0, slices);
    glDisableClientState(GL_VERTEX_ARRAY);

    // render upper part
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, upperVertex);
    glDrawArrays(GL_TRIANGLE_FAN, 0, slices);
    glDisableClientState(GL_VERTEX_ARRAY);

    // render round part
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, roundVertex);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, slices * 2);
    glDisableClientState(GL_VERTEX_ARRAY);
}
