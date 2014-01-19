/* arctunnelprimitive.cpp -  Represents an arc tunnel that can be rendered.
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

#include "boxmesh.h"
#include "arcmesh.h"
#include "roofmesh.h"

#include "arctunnelprimitive.h"

ArcTunnelPrimitive::ArcTunnelPrimitive():
modelData(nullptr), elems(5)
{
    modelData = new Primitive*[elems];
    modelData[0] =  new ArcMesh(2.5);
    modelData[1] =  new ArcMesh(-2.5);
    modelData[2] = new RoofMesh();
    modelData[3] = new BoxMesh(1.0f, 1.0f, 5.0f);
    modelData[4] = new BoxMesh(1.0f, 1.0f, 5.0f);
}

ArcTunnelPrimitive::~ArcTunnelPrimitive()
{
    if (modelData != nullptr) {
        for (int i = 0; i < elems; i++)
        if (modelData[i] != nullptr) {
            delete modelData[i];
            modelData[i] = nullptr;
        }
        delete[] modelData;
    }
}


void ArcTunnelPrimitive::render()
{
    if (modelData != nullptr) {
        glPushMatrix();
        for (int i = 0; i < elems; i++) {
            switch (i) {
            case 3:  // left wall
                glTranslatef(-5, 0, 0);
                break;

            case 4:  // right wall
                glTranslatef(10, 0, 0);
                break;
            }
            modelData[i]->render();
        }
    }
}