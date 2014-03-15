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
#include <memory>

#include "c++14.h"
#include "glos.h"
#include "pi.h"
#include "mesh.h"
#include "diskprimitive.h"


/**
 * @param innerRadius the inner radius of the circle from the center.
 * @param outerRadius the outer radius of the circle from the center.
 * @param slices the amount of slices to cut the circle when calculating the vertices. Must be at least 1.
 */
DiskPrimitive::DiskPrimitive(GLfloat innerRadius, GLfloat outerRadius, GLint slices)
{
	assert(slices > 0);
    const GLfloat step = 2 * PI / static_cast<GLfloat>(slices);

    auto mesh = std::make_unique<Mesh>(3, Mesh::RenderMode::triangles);
    for (int i = 0; i < slices; i++) {
        GLfloat angle = i * step;
        GLfloat nextAngle = (i + 1 ) * step;

        mesh->addVertex(outerRadius * cos(angle), outerRadius * sin(angle), 0);
        mesh->addVertex(innerRadius * cos(angle), innerRadius * sin(angle), 0);
        mesh->addVertex(outerRadius * cos(nextAngle), outerRadius * sin(nextAngle), 0);

        mesh->addVertex(outerRadius * cos(nextAngle), outerRadius * sin(nextAngle), 0);
        mesh->addVertex(innerRadius * cos(angle), innerRadius * sin(angle), 0);
        mesh->addVertex(innerRadius * cos(nextAngle), innerRadius * sin(nextAngle), 0);
    }
    addChild(std::move(mesh));
}

DiskPrimitive::~DiskPrimitive()
{

}
