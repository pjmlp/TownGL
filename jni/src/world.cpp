/* world.cpp - Model drawing functions for the town
* Copyright (C) 2012 Paulo Pinto
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
#include <cassert>

#include "glos.h"
#include "pi.h"
#include "diskprimitive.h"
#include "boxprimitive.h"
#include "arcprimitive.h"
#include "roofprimitive.h"
#include "cylinderprimitive.h"
#include "primitive.h"
#include "arctunnelprimitive.h"
#include "buildingprimitive.h"
#include "floorprimitive.h"
#include "roadprimitive.h"
#include "tunnelprimitive.h"
#include "windmillprimitive.h"

#include "world.h"

World::World()
{
    objects[0] = new FloorPrimitive();
    objects[1] = new RoadPrimitive();
    objects[2] = new WindmillPrimitive();
    objects[3] = new ArcTunnelPrimitive();
    objects[4] = new TunnelPrimitive();
    objects[5] = new BuildingPrimitive();
    objects[5]->setColor(0, 0, 1, 0);
    objects[6] = new BuildingPrimitive();
    objects[6]->setColor(0, 1, 0, 0);
    objects[7] = new BuildingPrimitive();
    objects[7]->setColor(1, 0, 0, 0);
}

World::~World()
{
    for (int i = 0; i < elems; i++)
        delete objects[i];
}

/**
* Draws the world representing the town.
* @param frame current animation frame.
*/
void World::render(GLfloat frame)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // draws the floor
    objects[0]->render();

    // draws the road
    objects[1]->render();

#if 0
    /* 1� Moinho */
    glPushMatrix();
    glTranslatef(4.2f, 0, 13);
    glRotatef(120, 0, 1, 0);
    objects[2]->update(frame);
    objects[2]->render();
    glPopMatrix();


    /* 2� Moinho */
    glPushMatrix();
    glTranslatef(15, 0, -15);
    objects[2]->render();
    
    glPopMatrix();
#endif

    /* 1� T�nel */
    glPushMatrix();
    glTranslatef(0, 0, -10);
    glScalef(1, 0.5, 0.5);
    glRotatef(90, 0, 1, 0);
    objects[3]->render();
    
    glPopMatrix();

    /* 2� T�nel */
    glPushMatrix();
    glTranslatef(-6, 0, 8);
    glScalef(0.5, 2, 0.5);
    glRotatef(60, 0, 1, 0);
    objects[4]->render();
    glPopMatrix();


    /* 1� Edif�cio */
    glPushMatrix();
    glTranslatef(10, 4, -17);
    objects[5]->render();
    glPopMatrix();

    /* 2� Edif�cio */
    glPushMatrix();
    glTranslatef(-15, 4, -10);
    objects[6]->render();
    glPopMatrix();

    /* 3� Edif�cio */
    glPushMatrix();
    glTranslatef(13, 4, 8);
    objects[7]->render();
    glPopMatrix();


}