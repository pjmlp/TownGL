/* draw.cpp - Model drawing functions for the town
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
#include "diskmesh.h"
#include "boxmesh.h"
#include "arcmesh.h"
#include "roofmesh.h"

#include "draw.h"


// Internal functions prototypes.

static void DrawCylinder(GLfloat radius, GLfloat height);
static void DrawCylinder(GLfloat lowerRadius, GLfloat upperRadius, GLfloat height);
static void DrawCone(GLfloat radius, GLfloat height);
static void DrawSolidTunnel ();
static void DrawSolidArcTunnel ();
static void DrawSolidBuilding ();
static void DrawSolidWindmill (GLfloat frame);

// Public functions implementations


/**
 * Draws the tunnel
 */
void DrawSolidTunnel ()
{
  BoxMesh leftWall(1.0f, 1.0f, 5.0f);
  BoxMesh rightWall(1.0f, 1.0f, 5.0f);
  BoxMesh ceiling(11, 0.10f, 5);

  glPushMatrix ();

    // Left wall
    glTranslatef (-5, 0, 0);
	leftWall.render();

    // Right wall
    glTranslatef (10, 0, 0);
	rightWall.render();

    // Ceiling
    glTranslatef (-5, 0.55f, 0);
	ceiling.render();


  glPopMatrix ();
}

/**
 *  Draws the tunnel
 */
void DrawSolidArcTunnel ()
{
	BoxMesh leftWall(1.0f, 1.0f, 5.0f);
	BoxMesh rigthWall(1.0f, 1.0f, 5.0f);
    ArcMesh frontArc(2.5);
    ArcMesh backArc(-2.5);
    RoofMesh roof;

    

  glPushMatrix ();
  
    // ceiling
  frontArc.render();
  backArc.render();
  roof.render();

    // left wall
    glTranslatef (-5, 0, 0);
	leftWall.render();

    // right wall
    glTranslatef (10, 0, 0);
	rigthWall.render();
  
  glPopMatrix ();
}


/**
 * Buildings
 */
void DrawSolidBuilding ()
{
  glPushMatrix ();

  BoxMesh building (2.0f, 8.0f, 2.0f);
  building.render();

  glPopMatrix ();
}

/**
 * Draws the floor, so that there is a nice separation between the global color,
 * road and floor.
 */
void DrawSolidFloor ()
{
	DiskMesh disk(0, 50, 10);
  glPushMatrix ();

    glColor4f (0.2f, 0.3f, 0.5f, 0.0f);
    glRotatef (-90, 1, 0, 0);
	disk.render();
  
  glPopMatrix ();
}


/**
 * Draws a circular road around the buildings.
 */
void DrawSolidRoad ()
{
	DiskMesh disk(9, 11, 25);
  glPushMatrix ();

    glColor4f (0, 0, 0, 0);
    glTranslatef (0, 0.1f, 0);
    glRotatef (-90, 1, 0, 0);
    disk.render();
  
  glPopMatrix ();
}





/**
 * Draws a windmill
 * @param frame the current animation frame
 */
void DrawSolidWindmill (GLfloat frame)
{
	/* temporary move here, this code should be removed when the framerate is fixed */
	static GLfloat drawAngle = 0.0f;    
	drawAngle += 10 * frame;
	if (drawAngle > 360)
		drawAngle -= 360;

  GLfloat length = 0.75, lastX, lastY, x, y;
	GLint i;
	bool isFlag = false;

  glPushMatrix ();


  // draws the base
  glColor4f (0.4f, 0.5f, 0, 0);  // brown
  DrawCylinder (1, 1);

  // draws the roof
  glColor4f (1, 0, 0, 0);   // red
  glPushMatrix ();
    glTranslatef (0, 1, 0);
    glRotatef (-90, 1, 0, 0);
    DrawCone (1, 0.5f);
  glPopMatrix ();

  // draws the sails
  glColor4f (1.0f, 0.8f, 0.0f, 0.0f);
  glTranslatef (0, 1, 1);
  glRotatef(drawAngle, 0.0f, 0.0f, 1.0f); //rotation applied to the sails
  lastX = length;
	lastY = 0.0;
  
    const GLint VERTEX_COUNT = 3;
    const GLint POINTS = 2;
    const GLint SLICES = 12;
	const int ELEMS = SLICES * VERTEX_COUNT * POINTS;
	GLfloat vertex[ELEMS];
    GLfloat countour[ELEMS];

	int idxx = 0;
	int idx = 0;

	for (i = 1; i <= SLICES; i++) 
	{
		vertex[idx++] = lastX;
		vertex[idx++] = lastY;

        GLfloat angle = 2 * i * PI / SLICES;
		x = length * cos (angle);
		y = length * sin (angle);

		if (isFlag) {
			vertex[idx++] = x;
			vertex[idx++] = y;

			vertex[idx++] = 0;
			vertex[idx++] = 0;
		}
		else {
			vertex[idx++] = 0;
			vertex[idx++] = 0;

			vertex[idx++] = x;
			vertex[idx++] = y;
		}

		countour[idxx++] = lastX = x;
		countour[idxx++] = lastY = y;
		isFlag = !isFlag;
	}

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(POINTS, GL_FLOAT, 0, vertex);
	for (int i = 0; i < SLICES; i++) {
        if (i % 2 == 0)
            glDrawArrays(GL_TRIANGLES, i * VERTEX_COUNT, VERTEX_COUNT);
	}
    glDisableClientState(GL_VERTEX_ARRAY);
	/*
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(POINTS, GL_FLOAT, 0, countour);
    glDrawArrays(GL_LINE_STRIP, 0, idxx);
    glDisableClientState(GL_VERTEX_ARRAY);
	*/
  glPopMatrix ();
}



/*
 * Desenha o mundo
 * frame é o frame actual
 */
void DrawWorld (GLfloat frame)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode (GL_MODELVIEW);
  glLoadIdentity ();

  /* Desenha o chão */
  DrawSolidFloor ();
  

  /* Desenha a estrada */
  DrawSolidRoad ();

  /* 1º Moinho */
  glPushMatrix ();
    glTranslatef (4.2f, 0, 13);
    glRotatef (120, 0, 1, 0);
    DrawSolidWindmill (frame);
  glPopMatrix ();

  
  /* 2º Moinho */
  glPushMatrix ();
    glTranslatef (15, 0, -15);
    DrawSolidWindmill (frame);
  glPopMatrix ();

  /* 1º Túnel */
  glPushMatrix ();
    glEnable (GL_NORMALIZE);
    glTranslatef (0, 0, -10);
    glScalef (1, 0.5, 0.5);
    glRotatef (90, 0, 1, 0);

    DrawSolidArcTunnel ();
    glDisable (GL_NORMALIZE);
  glPopMatrix ();

  /* 2º Túnel */
  glPushMatrix ();
    glEnable (GL_NORMALIZE);
    glTranslatef (-6, 0, 8);
    glScalef (0.5, 2, 0.5);
    glRotatef (60, 0, 1, 0);
    DrawSolidTunnel ();
    glDisable (GL_NORMALIZE);
  glPopMatrix ();


  /* 1º Edifício */
  glPushMatrix ();
    glEnable (GL_NORMALIZE);
    glTranslatef (10, 4, -17);
    glColor4f (0, 0, 1, 0);
    DrawSolidBuilding ();
    glDisable (GL_NORMALIZE);
  glPopMatrix ();

  /* 2º Edifício */
  glPushMatrix ();
    glEnable (GL_NORMALIZE);
    glTranslatef (-15, 4, -10);
    glColor4f (0, 1, 0, 0);
    DrawSolidBuilding ();
    glDisable (GL_NORMALIZE);
  glPopMatrix ();

  /* 3º Edifício */
  glPushMatrix ();
    glEnable (GL_NORMALIZE);
    glTranslatef (13, 4, 8);
    glColor4f (1, 0, 0, 0);
    DrawSolidBuilding ();
    glDisable (GL_NORMALIZE);
  glPopMatrix ();


  
//  DrawTraject ();
}

// Internal functions implementation





void DrawCylinder(GLfloat radius, GLfloat height)
{
	DrawCylinder(radius, radius, height);
}

/**
 * Cylinder drawing
 *
 * @param radius the circle radius
 * @param height the circle height
 */
void DrawCylinder(GLfloat lowerRadius, GLfloat upperRadius, GLfloat height)
{
    const int slices = 20;
    const GLfloat x = 0.0f;
    const GLfloat y = 0.0f;
    const GLfloat z = 0.0f;

    const int ELEMS = (slices + 1) * 3 * 2;
    GLfloat vertex[ELEMS];

    int idx = 0;
    // bottom circle
    vertex[idx++] = x;
    vertex[idx++] = y;
    vertex[idx++] = z;
    for(int i=0; i<=slices; i++) {
        GLfloat angle = static_cast<GLfloat>(i) / slices * 2 * PI;
        vertex[idx++] = x + cos(angle)*lowerRadius;
        vertex[idx++] = y;
        vertex[idx++] = z+sin(angle)*lowerRadius;
    }

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertex);
    glDrawArrays(GL_TRIANGLE_FAN, 0, slices);
    glDisableClientState(GL_VERTEX_ARRAY);


    idx = 0;
    // top circle
    vertex[idx++] = x;
    vertex[idx++] = y + height;
    vertex[idx++] = z;
    for(int i=0; i<=slices; i++) {
        GLfloat angle = static_cast<GLfloat>(i) / slices * 2 * PI;
        vertex[idx++] = x + cos(angle)*upperRadius;
        vertex[idx++] = y + height;
        vertex[idx++] = z+sin(angle)*upperRadius;
    }

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertex);
    glDrawArrays(GL_TRIANGLE_FAN, 0, slices);
    glDisableClientState(GL_VERTEX_ARRAY);


    idx = 0;
    // the rest
    for(int i=0; i<=slices; i++) {
        GLfloat angle = static_cast<GLfloat>(i) / slices * 2 * PI;
        vertex[idx++] = x + cos(angle)*lowerRadius;
        vertex[idx++] = y;
        vertex[idx++] = z+sin(angle)*lowerRadius;

        vertex[idx++] = x + cos(angle)*upperRadius;
        vertex[idx++] = y + height;
        vertex[idx++] = z+sin(angle)*upperRadius;
    }

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertex);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, slices * 2);
    glDisableClientState(GL_VERTEX_ARRAY);

}

/**
 * Cone drawing
 * @param radius the radius of the cone base
 * @param height the cone's height
 */
void DrawCone(GLfloat radius, GLfloat height)
{
	
    /*
  GLUquadric *cone;

  cone = gluNewQuadric();
  gluCylinder (cone, radius, 0, height, 20, 20);

  gluDeleteQuadric(cone);
  */

#if 0
	DrawCylinder(radius, 0, height);
#endif

}

