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
#include "roofprimitive.h"


static const int ELEMS = 19 * 4 * 3;
static GLfloat vertex[ELEMS];

RoofPrimitive::RoofPrimitive()
{
    GLfloat lastX = 5.5;
    GLfloat lastY = 0.5;

    int id = 0;
    int idx = 0;

    for (int i = 10; i <= 180; i += 10) {
        ::vertex[idx++] = lastX;
        ::vertex[idx++] = lastY;
        ::vertex[idx++] = 2.5;


        ::vertex[idx++] = lastX;
        ::vertex[idx++] = lastY;
        ::vertex[idx++] = -2.5;


        GLfloat x = 5.5f * cos(UTIL_TO_RADIANS(static_cast<GLfloat>(i)));
        GLfloat y = 0.5f + 5.5f * sin(UTIL_TO_RADIANS(static_cast<GLfloat>(i)));

        ::vertex[idx++] = x;
        ::vertex[idx++] = y;
        ::vertex[idx++] = -2.5;

        ::vertex[idx++] = x;
        ::vertex[idx++] = y;
        ::vertex[idx++] = 2.5;

        lastX = x;
        lastY = y;
        id++;
    }
}

RoofPrimitive::~RoofPrimitive()
{
}

void RoofPrimitive::render()
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, ::vertex);
    for (int i = 0; i < 19; i++) {
        glDrawArrays(GL_TRIANGLE_FAN, i * 4, 4);
    }
    glDisableClientState(GL_VERTEX_ARRAY);
}
