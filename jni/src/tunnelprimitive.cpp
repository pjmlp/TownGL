/* tunnelprimitive.cpp -  Represents a tunnel that can be rendered.
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

#include "glos.h"

#include "tunnelprimitive.h"


TunnelPrimitive::TunnelPrimitive()
{
    objects[0] = new BoxPrimitive(1.0f, 1.0f, 5.0f);
    objects[1] = new BoxPrimitive(1.0f, 1.0f, 5.0f);
    objects[2] = new BoxPrimitive(11, 0.10f, 5);

    for (int i = 0; i < elems; i++)
        objects[i]->setColor(1.0f, 0.8f, 0.0f, 0.0f); //yellow
}

TunnelPrimitive::~TunnelPrimitive()
{
    for (int i = 0; i < elems; i++)
        delete objects[i];
}

void TunnelPrimitive::render()
{
    glPushMatrix();

    // Left wall
    glTranslatef(-5, 0, 0);
    objects[0]->render();

    // Right wall
    glTranslatef(10, 0, 0);
    objects[1]->render();

    // Ceiling
    glTranslatef(-5, 0.55f, 0);
    objects[2]->render();


    glPopMatrix();
}