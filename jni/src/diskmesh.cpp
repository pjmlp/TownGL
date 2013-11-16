/* diskmesh.cpp -  Represents a simple 2D circle.
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


#include "diskmesh.h"
#include "pi.h"

/**
 * @param innerRadius the inner radius of the circle from the center.
 * @param outerRadius the outer radius of the circle from the center.
 * @param slices the amount of slices to cut the circle when calculating the vertices. Must be at least 1.
 */
DiskMesh::DiskMesh(GLfloat innerRadius, GLfloat outerRadius, GLint slices):vertex(0) {
	assert(slices > 0);
	const GLfloat STEP = 2 * PI / slices;
	VERTEX_COUNT = 4 * (slices + 1);
    vertex = new GLfloat [VERTEX_COUNT];

	GLint idx = 0;
    for (int i = 0; i <= slices; i++) {
		GLfloat angle = i * STEP;

		vertex[idx++] = outerRadius * cos (angle);
		vertex[idx++] = outerRadius * sin (angle);

		vertex[idx++] = innerRadius * cos (angle);
		vertex[idx++] = innerRadius * sin (angle);

	}
}

DiskMesh::~DiskMesh() {
	if (vertex) {
		delete[] vertex;
	}
}


void DiskMesh::render ()
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_FLOAT, 0, vertex);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, VERTEX_COUNT);
    glDisableClientState(GL_VERTEX_ARRAY);
}
