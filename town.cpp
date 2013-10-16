/* town.cpp - Draws the town.
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
#include <cstdio>
#include <cmath>
#include <ctime>

#include "draw.h"
#include "pi.h"
#include "town.h"



// Global constant declarations


/** circle radius */
static const GLfloat RADIUS = 9.5f;

/** Maximum altitude allowed for the view from above.*/
static const GLint MAX_ALTITUDE = 100;

/** Minimum altitude allowed for the view from above. */
static const GLfloat MIN_ALTITUDE = 0.5f;

/** Increment/decrement step for the altitude change. */
static const GLfloat INC_ALTITUDE = 0.5f;

/** Starting altitude when the user changes view mode. */
static const GLint DEFAULT_ALTITUDE = 53;

/** Maximum speed */
static const GLint MAX_INC_FRAME = 10;

/** Minimum speed */
static const GLint MIN_INC_FRAME = 1;



// Module global variables

/** Is the animation paused. */
static bool isPaused = false;

/** Using the overhead view. */
static bool isAbove = false;

/** Current window size */
static GLsizei lastWidth, lastHeight;

/** Current altitude */
static GLfloat altitude = 0.5;

/** Current speed in terms of frame rate increments. */
static GLuint incFrame = 1;

/** Is the lightning enabled. */
static bool isLightOn = true;

/** time at the begining of the frame */
static clock_t currentTime = 0;

/** Frame value in terms of time. */
static GLfloat currentFrame = 0.0f;





/**
 * Sets the initial configuration of the demo.
 */
void InitializeGL ()
{	
  TurnOnLighting ();

  glClearColor (0, 0, 0.5, 0);
  glLineWidth(3);

  currentTime = clock();
}



/**
 * Updates the application's state
 */
void MainLoop ()
{
  if (!isPaused) {
    clock_t now = clock();
    GLfloat duration = (now - currentTime) / (GLfloat)CLOCKS_PER_SEC;
  
    currentFrame = duration;
    Project (lastWidth, lastHeight);
    DrawWorld (duration);
    glFlush ();

    currentTime = now;
  }
}


/**
 * Stops/starts the application.
 */
void OnPKey ()
{
  isPaused = !isPaused;
}

/**
 * Changes the user's viewpoint
 */
void OnVKey ()
{
  isAbove = !isAbove;
  if (isAbove) {
    altitude = DEFAULT_ALTITUDE;
  }
  else {
    altitude = MIN_ALTITUDE;
  }
}

/**
 * Enables/disables the demo lighting.
 */
void OnLKey ()
{
  if (isLightOn)
    glDisable (GL_LIGHTING);
  else
    glEnable (GL_LIGHTING);
 
  isLightOn = !isLightOn;
}

/**
 * Resets the application settings.
 */
void OnRKey ()
{
  isLightOn = true;
  isAbove = true;
  altitude = DEFAULT_ALTITUDE;
  incFrame = MIN_INC_FRAME;
  glEnable (GL_LIGHTING);
}


/**
 * Increases the viewer's height.
 */
void OnUpKey ()
{
  if (altitude < MAX_ALTITUDE || isAbove)
    altitude += INC_ALTITUDE; 
}

/**
 * Decreases the viewer's height.
 */
void OnDownKey ()
{
  if (altitude > MIN_ALTITUDE)
    altitude -= INC_ALTITUDE; 
}

/**
 * Increases the viewer's speed.
 */
void OnIncKey ()
{
  if (incFrame < MAX_INC_FRAME)
    incFrame++; 
}

/**
 * Decreases the viewer's speed.
 */
void OnDecKey ()
{
  if (incFrame > MIN_INC_FRAME)
    incFrame--; 
}


/**
 * Handles the window resize by the user.
 */
void OnResize (GLsizei w, GLsizei h)
{
  h = (h == 0) ? 1 : h;
  glViewport (0, 0, w, h);
	Project (w,h);

  lastWidth = w;
  lastHeight = h;
}


/**
 * Sets up the OpenGL projection, based on the window size.
 * @param w windows' width
 * @param h windows' height
 */
void Project (GLsizei w, GLsizei h)
{
  GLfloat xEye, yEye, zEye;
  GLfloat xTarget, yTarget, zTarget;
  GLfloat xUpVector, yUpVector, zUpVector;
  static GLfloat angle = 0.0f;
  GLfloat cosAngle, sinAngle;

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  
	if (w <= h) 
	  glScalef (1, (GLfloat)w/(GLfloat)h, 1);
	else 
		glScalef ((GLfloat)h/(GLfloat)w, 1, 1);

  gluPerspective (45, 1, 0.5, 100.0);
  
  // sets the camera on the proper place.

  angle += 10 * currentFrame;
  if (angle > 360)
    angle -=360;

  cosAngle = cos (UTIL_TO_RADIANS (angle));
  sinAngle = sin (UTIL_TO_RADIANS (angle));

  if (isAbove) { /* view from above */
    xTarget = 0;
    yTarget = 0;
    zTarget = 0;
    
    xEye = 0;
    yEye = altitude;
    zEye = 0;
    
    xUpVector = 0.0;
    yUpVector = 0.0;
    zUpVector = -1.0;
  }
  else { /* normal route */
    xEye = RADIUS * cosAngle;
    yEye = altitude;
    zEye = RADIUS * sinAngle;

    xTarget = xEye + cos (UTIL_TO_RADIANS (98 + angle));
    yTarget = altitude;
    zTarget = zEye + sin (UTIL_TO_RADIANS (98 + angle));

    
    xUpVector = 0.0;
    yUpVector = 1.0;
    zUpVector = 0.0;
  }

  gluLookAt ( xEye,           yEye,      zEye,   
              xTarget,     yTarget,   zTarget,   
              xUpVector, yUpVector, zUpVector);  

  // Objects related transformations follow this calls
}


/**
 * Lighting settings
 */
void TurnOnLighting ()
{
  GLfloat position[] = {1.0, 1.0, 1.0, 1.0};
  GLfloat ambient [] = {1.0, 1.0, 1.0, 1.0};

  glShadeModel (GL_SMOOTH);
  glEnable (GL_LIGHTING);
  glEnable (GL_LIGHT0);
  glDepthFunc (GL_LESS);
  glEnable (GL_DEPTH_TEST);
  glEnable (GL_COLOR_MATERIAL);
  
  glLightModelfv (GL_LIGHT_MODEL_AMBIENT, ambient);
  glLightfv (GL_LIGHT0, GL_POSITION, position);
}
