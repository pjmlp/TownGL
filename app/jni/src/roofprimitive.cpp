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
#include <memory>


#include "glos.h"
#include "pi.h"
#include "mesh.h"

#include "roofprimitive.h"

RoofPrimitive::RoofPrimitive()
{
    const GLint elems = 19;
    GLfloat lastX = 5.5;
    GLfloat lastY = 0.5;

    for (int i = 0; i < elems; i++) {
        GLfloat angle = toRadians(10.0f * (i + 1));
        auto mesh = std::make_unique<Mesh>(3, Mesh::RenderMode::triangle_fan);


        mesh->addVertex(lastX, lastY, 2.5);
        mesh->addVertex(lastX, lastY, -2.5);


        GLfloat x = 5.5f * cos(angle);
        GLfloat y = 0.5f + 5.5f * sin(angle);

        mesh->addVertex(x, y, -2.5);
        mesh->addVertex(x, y, 2.5);

        lastX = x;
        lastY = y;

        mesh->upload();
        addChild(std::move(mesh));
    }
}

RoofPrimitive::~RoofPrimitive()
{
    // Nothing to do
}
