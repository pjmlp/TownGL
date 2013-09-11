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
#include "glos.h"
#include <GL/glew.h>
#include <GL/glaux.h>
#include <math.h>

#include "pi.h"
#include "draw.h"


// Internal functions prototypes.

static void DrawArc (GLfloat depth);
static void DrawRoof ();
static void DrawSolidBox(GLfloat width, GLfloat height, GLfloat depth);
static void DrawCylinder(GLdouble radius, GLdouble height);
static void DrawCone(GLdouble radius, GLdouble height);
static void DrawSolidTunnel ();
static void DrawSolidArcTunnel ();
static void DrawSolidBuilding ();
static void DrawSolidWindmill (GLfloat angle);

// Public functions implementations


/**
 * Draws the tunnel
 */
void DrawSolidTunnel ()
{
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix ();

    // Left wall
    glTranslatef (-5, 0, 0);
    DrawSolidBox (1.0f, 1.0f, 5.0f);

    // Right wall
    glTranslatef (10, 0, 0);
    DrawSolidBox (1.0f, 1.0f, 5.0f);

    // Ceiling
    glTranslatef (-5, 0.55f, 0);
    DrawSolidBox (11, 0.10f, 5);

  
  glPopMatrix ();
}

/**
 *  Draws the tunnel
 */
void DrawSolidArcTunnel ()
{
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix ();

    // ceiling
    DrawArc (2.5);
    DrawArc (-2.5);
    DrawRoof ();

    // left wall
    glTranslatef (-5, 0, 0);
    DrawSolidBox (1.0f, 1.0f, 5.0f);

    // right wall
    glTranslatef (10, 0, 0);
    DrawSolidBox (1.0f, 1.0f, 5.0f);
  
  glPopMatrix ();
}


/**
 * Buildings
 */
void DrawSolidBuilding ()
{
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix ();

    DrawSolidBox (2.0f, 8.0f, 2.0f);

  glPopMatrix ();
}

/*
 * Desenha um chão sólido
 */
void DrawSolidFloor ()
{
  GLUquadricObj* diskObj;

  glMatrixMode(GL_MODELVIEW);
  glPushMatrix ();

    glColor3f (0.2f, 0.3f, 0.5f);
    glRotatef (-90, 1, 0, 0);
    diskObj = gluNewQuadric ();
    gluDisk(diskObj, 0, 50, 10, 20);
    gluDeleteQuadric(diskObj);
  
  glPopMatrix ();
}


/*
 * Desenha a estrada 
 */
void DrawSolidRoad ()
{
  GLUquadricObj* roadObj;

  glMatrixMode(GL_MODELVIEW);
  glPushMatrix ();

    glColor3f (0, 0, 0);
    glTranslatef (0, 0.1f, 0);
    glRotatef (-90, 1, 0, 0);
    roadObj = gluNewQuadric ();
    gluDisk(roadObj, 9, 11, 25, 25);
    gluDeleteQuadric(roadObj);
  
  glPopMatrix ();
}





/*
 * Desenha um moínho sólido
 * O ângulo é em graus
 */
void DrawSolidWindmill (GLfloat angle)
{
  GLfloat length = 0.75, lastX, lastY, x, y;
	GLint i;
	BOOL isFlag = FALSE;

  glMatrixMode(GL_MODELVIEW);
  glPushMatrix ();


  /* Desenha a base do moínho */
  glColor3f (0.4f, 0.5f, 0);  /* Castanho */
  DrawCylinder (1, 1);

  /* Desenha o telhado */
  glColor3f (1, 0, 0);   /* Vermelho */
  glPushMatrix ();
    glTranslatef (0, 1, 0);
    glRotatef (-90, 1, 0, 0);
    DrawCone (1, 0.5f);
  glPopMatrix ();

  /* Desenha as velas */
  glColor3f (1.0f, 0.8f, 0.0f);
  glTranslatef (0, 1, 1);
  glRotatef (angle, 0.0f, 0.0f, 1.0f); /* Rotação aplicada às velas */
  glPolygonMode (GL_FRONT, GL_FILL);
	glPolygonMode (GL_BACK, GL_LINE);
  lastX = length;
	lastY = 0.0;
  

  /* Desenha as velas */
  
	for (i = 1; i <= 12; i++) 
	{
	  glBegin (GL_POLYGON);
      glVertex2f (lastX, lastY);
		  x = length * cos (i * PI / 6);
		  y = length * sin (i * PI / 6);
		  if (isFlag) {
		    glVertex2f (x, y);
			  glVertex2f (0.0, 0.0);
		  }
		  else {
			  glVertex2f (0.0, 0.0);
			  glVertex2f (x, y);
		  }
		glEnd ();
		lastX = x;
		lastY = y;
		isFlag = !isFlag;
	}
  
  glPopMatrix ();
}



/*
 * Desenha o trajecto
 */
static void DrawTraject ()
{
  int i;
  double x, z;
  GLUquadric *sphere;

  glMatrixMode(GL_MODELVIEW);
  glPushMatrix ();

  sphere = gluNewQuadric();
  glColor3f (1, 0, 1);
  for (i = 0; i < 360; i+=10) {
    glPushMatrix ();
      x = 10 * cos (UTIL_TO_RADIANS (i));
      z = 10 * sin (UTIL_TO_RADIANS (i));
      glTranslatef (x, 0, z);
      //auxSolidSphere (0.5);
      gluSphere(sphere, 0.5, 10, 10);
    glPopMatrix ();
  }
  gluDeleteQuadric(sphere);
  glPopMatrix ();
}

/*
 * Desenha o mundo
 * frame é o frame actual
 */
void DrawWorld (GLfloat frame)
{
  static GLfloat angle = 0.0f;

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode (GL_MODELVIEW);
  glLoadIdentity ();


  /* Ângulo de rotação das velas */
  angle += 10 * frame;
  if (angle > 360)
    angle -= 360;


  /* Desenha o chão */
  DrawSolidFloor ();
  

  /* Desenha a estrada */
  DrawSolidRoad ();

  /* 1º Moinho */
  glPushMatrix ();
    glTranslatef (4.2f, 0, 13);
    glRotatef (120, 0, 1, 0);
    DrawSolidWindmill (angle);
  glPopMatrix ();

  
  /* 2º Moinho */
  glPushMatrix ();
    glTranslatef (15, 0, -15);
    DrawSolidWindmill (angle);
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
    glColor3f (0, 0, 1);
    DrawSolidBuilding ();
    glDisable (GL_NORMALIZE);
  glPopMatrix ();

  /* 2º Edifício */
  glPushMatrix ();
    glEnable (GL_NORMALIZE);
    glTranslatef (-15, 4, -10);
    glColor3f (0, 1, 0);
    DrawSolidBuilding ();
    glDisable (GL_NORMALIZE);
  glPopMatrix ();

  /* 3º Edifício */
  glPushMatrix ();
    glEnable (GL_NORMALIZE);
    glTranslatef (13, 4, 8);
    glColor3f (1, 0, 0);
    DrawSolidBuilding ();
    glDisable (GL_NORMALIZE);
  glPopMatrix ();


  
//  DrawTraject ();
}

// Internal functions implementation



/**
 * Draws an arc. Used by the tunnels in arc form.
 * @param depth How long the arch is.
 */
static void DrawArc (GLfloat depth)
{
  GLfloat lastXTop = 5.5;
  GLfloat lastYTop = 0.5;
  GLfloat lastXBottom = 4.5;
  GLfloat lastYBottom = 0.5;

  const int ELEMS = 19 * 4 * 3;
  GLfloat vertex[ELEMS];
  GLint startingElements[19];
  GLint counts[19];

  int id = 0;
  int idx = 0;
  for (int i = 10; i <= 180; i += 10) {
        vertex[idx++] = lastXBottom;
        vertex[idx++] = lastYBottom;
        vertex[idx++] = depth;


        vertex[idx++] = lastXTop;
        vertex[idx++] = lastYTop;
        vertex[idx++] = depth;


        GLfloat x = 5.5 * cos (UTIL_TO_RADIANS (i));
        GLfloat y = 0.5 + 5.5 * sin (UTIL_TO_RADIANS (i));

        vertex[idx++] = x;
        vertex[idx++] = y;
        vertex[idx++] = depth;

        lastXTop = x;
        lastYTop = y;

        x = 4.5 * cos (UTIL_TO_RADIANS (i));
        y = 0.5 + 4.5 * sin (UTIL_TO_RADIANS (i));

        vertex[idx++] = x;
        vertex[idx++] = y;
        vertex[idx++] = depth;

        lastXBottom = x;
        lastYBottom = y;

        startingElements[id] = id * 4;
        counts [id++] = 4;
    }

    glPolygonMode (GL_FRONT_AND_BACK, GL_FILL);

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertex);
    glMultiDrawArrays(GL_POLYGON, const_cast<const GLint*>(startingElements), const_cast<const GLint*>(counts), id);
    glDisableClientState(GL_VERTEX_ARRAY);
}


/**
 * Draws the tunnel roof. Used by the tunnels in rectangular form.
 * @param depth How long the arch is.
 */
static void DrawRoof ()
{
  GLfloat lastX = 5.5;
  GLfloat lastY = 0.5;

  const int ELEMS = 19 * 4 * 3;
  GLfloat vertex[ELEMS];
  GLint startingElements[19];
  GLint counts[19];

  int id = 0;
  int idx = 0;

  for (int i = 10; i <= 180; i += 10) {
        vertex[idx++] = lastX;
        vertex[idx++] = lastY;
        vertex[idx++] = 2.5;


        vertex[idx++] = lastX;
        vertex[idx++] = lastY;
        vertex[idx++] = -2.5;


      GLfloat x = 5.5 * cos (UTIL_TO_RADIANS (i));
      GLfloat y = 0.5 + 5.5 * sin (UTIL_TO_RADIANS (i));

        vertex[idx++] = x;
        vertex[idx++] = y;
        vertex[idx++] = -2.5;

        vertex[idx++] = x;
        vertex[idx++] = y;
        vertex[idx++] = 2.5;

      lastX = x;
      lastY = y;

      startingElements[id] = id * 4;
      counts [id++] = 4;
  }

    glPolygonMode (GL_FRONT_AND_BACK, GL_FILL);

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertex);
    glMultiDrawArrays(GL_POLYGON, const_cast<const GLint*>(startingElements), const_cast<const GLint*>(counts), id);
    glDisableClientState(GL_VERTEX_ARRAY);

}

/**
 * Draws a box
 */
static void DrawSolidBox(GLfloat width, GLfloat height, GLfloat depth)
{
    static const GLfloat vertex[] = {
    -1.0f,-1.0f,-1.0f, 
    -1.0f,-1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f, 
    1.0f, 1.0f,-1.0f, 
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f, 
    1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
    1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
    1.0f,-1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f,-1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f,-1.0f, 1.0f
    };


    glPushMatrix();
    glScalef(width/2, height/2, depth/2);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertex);
    glDrawArrays(GL_TRIANGLES, 0, 12*3);
    glDisableClientState(GL_VERTEX_ARRAY);
    glPopMatrix();
}


/**
 * Cylinder drawing
 *
 * @param radius the circle radius
 * @param height the circle height
 */
void DrawCylinder(GLdouble radius, GLdouble height)
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
    for(int i=0; i<slices; i++) {
        vertex[idx++] = x + cos((float)i/slices * 2 *PI)*radius;
        vertex[idx++] = y;
        vertex[idx++] = z+sin((float)i/slices * 2 * PI)*radius;
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
    for(int i=0; i<slices; i++) {
        vertex[idx++] = x + cos((float)i/slices * 2 *PI)*radius;
        vertex[idx++] = y + height;
        vertex[idx++] = z+sin((float)i/slices * 2 * PI)*radius;
    }

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertex);
    glDrawArrays(GL_TRIANGLE_FAN, 0, slices);
    glDisableClientState(GL_VERTEX_ARRAY);


    idx = 0;
    // the rest
    for(int i=0; i<slices; i++) {
        vertex[idx++] = x + cos((float)i/slices * 2 *PI)*radius;
        vertex[idx++] = y;
        vertex[idx++] = z+sin((float)i/slices * 2 * PI)*radius;

        vertex[idx++] = x + cos((float)i/slices * 2 *PI)*radius;
        vertex[idx++] = y + height;
        vertex[idx++] = z+sin((float)i/slices * 2 * PI)*radius;
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
void DrawCone(GLdouble radius, GLdouble height)
{
    auxSolidCone (radius, height);
#if 0
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
    for(int i=0; i<slices; i++) {
        vertex[idx++] = x + cos((float)i/slices * 2 *PI)*radius;
        vertex[idx++] = y;
        vertex[idx++] = z+sin((float)i/slices * 2 * PI)*radius;
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
    for(int i=0; i<slices; i++) {
        vertex[idx++] = x;
        vertex[idx++] = y + height;
        vertex[idx++] = z;
    }

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertex);
    glDrawArrays(GL_TRIANGLE_FAN, 0, slices);
    glDisableClientState(GL_VERTEX_ARRAY);


    idx = 0;
    // the rest
    /*
    for(int i=0; i<slices; i++) {
        vertex[idx++] = x + cos((float)i/slices * 2 *PI)*radius;
        vertex[idx++] = y;
        vertex[idx++] = z+sin((float)i/slices * 2 * PI)*radius;

        vertex[idx++] = x + cos((float)i/slices * 2 *PI)*radius;
        vertex[idx++] = y + height;
        vertex[idx++] = z+sin((float)i/slices * 2 * PI)*radius;
    }
*/

     for(int i=0; i<slices; i++) {
        vertex[idx++] = x + cos((float)i/slices * 2 *PI)*radius;
        vertex[idx++] = y;
        vertex[idx++] = z+sin((float)i/slices * 2 * PI)*radius;

        vertex[idx++] = x;
        vertex[idx++] = y + height;
        vertex[idx++] = z;
    }


    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertex);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, slices * 2);
    glDisableClientState(GL_VERTEX_ARRAY);
#endif

}
