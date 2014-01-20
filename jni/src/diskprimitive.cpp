/* DiskPrimitive.cpp -  Represents a simple 2D circle.
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


#include "diskprimitive.h"
#include "pi.h"

/**
 * @param innerRadius the inner radius of the circle from the center.
 * @param outerRadius the outer radius of the circle from the center.
 * @param slices the amount of slices to cut the circle when calculating the vertices. Must be at least 1.
 */
DiskPrimitive::DiskPrimitive(GLfloat innerRadius, GLfloat outerRadius, GLint slices) : mesh(2, Mesh::RenderMode::triangle_strip)
{
	assert(slices > 0);
    const GLfloat step = 2 * PI / slices;
    GLint vertexCount = 4 * (slices + 1);
    mesh.reserveMeshSize(vertexCount);

    GLint idx = 0;
    for (int i = 0; i <= slices; i++) {
        GLfloat angle = i * step;

        mesh.addVertex(outerRadius * cos(angle), outerRadius * sin(angle));

        mesh.addVertex(innerRadius * cos(angle), innerRadius * sin(angle));

    }
}

DiskPrimitive::~DiskPrimitive()
{

}

void DiskPrimitive::setColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
    mesh.setColor(r, g, b, a);
}

void DiskPrimitive::render()
{
    mesh.render();
}