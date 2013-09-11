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

#include <GL/glew.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#include "draw.h"
#include "pi.h"
#include "town.h"



/*** Variáveis globais ***/
extern HDC   ghDC;


/* Raio da circunferência */
static const GLfloat RADIUS = 9.5f;

/* Altitude máxima */
static const GLint MAX_ALTITUDE = 100;

/* Altitude miníma */
static const GLfloat MIN_ALTITUDE = 0.5f;

/* Incremento/Decremento da altitude */
static const GLfloat INC_ALTITUDE = 0.5f;

/* Altitude default para a vista por cima */
static const GLint DEFAULT_ALTITUDE = 53;

/* Velocidade máxima */
static const GLint MAX_INC_FRAME = 10;

/* Velocidade miníma */
static const GLint MIN_INC_FRAME = 1;



/*** Variáveis globais a este módulo ***/
static GLboolean isPaused = GL_FALSE;    /* Indica se estamos em modo pausa */
static GLboolean isAbove = GL_FALSE;     /* Indica a posicao de visao */
static GLsizei lastWidth, lastHeight;    /* Dimensões correntes da janela */  
static GLfloat altitude = 0.5;           /* Altitude corrente */  
static GLuint incFrame = 1;              /* Velocidade corrente */  
static GLboolean isLightOn = GL_TRUE;    /* Indica se a iluminação se encontra ligada */
static clock_t currentTime = 0.0f;       /* The current time */
static GLfloat currentFrame = 0.0f;






void initializeGL (void)
{	
  TurnOnLighting ();

  glClearColor (0, 0, 0.5, 0);
  glLineWidth(3);

  currentTime = clock();
}



/*
 * Rotina responsavel pelo ciclo principal
 */
void MainLoop (void)
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


/*
 * Rotina que muda liga/desliga o modo de pausa
 */
void OnPKey (void)
{
  isPaused = !isPaused;
}

/*
 * Rotina que muda o ponto de visão
 */
void OnVKey (void)
{
  isAbove = !isAbove;
  if (isAbove) {
    altitude = DEFAULT_ALTITUDE;
  }
  else {
    altitude = MIN_ALTITUDE;
  }
}

/*
 * Rotina que liga/desliga a iluminação
 */
void OnLKey (void)
{
  if (isLightOn)
    glDisable (GL_LIGHTING);
  else
    glEnable (GL_LIGHTING);
 
  isLightOn = !isLightOn;
}

/*
 * Rotina que restora os valores por omissão
 */
void OnRKey (void)
{
  isLightOn = GL_TRUE;
  isAbove = GL_TRUE;
  altitude = DEFAULT_ALTITUDE;
  incFrame = MIN_INC_FRAME;
  glEnable (GL_LIGHTING);
}


/*
 * Rotina que aumenta a altitude
 */
void OnUpKey (void)
{
  if (altitude < MAX_ALTITUDE || isAbove)
    altitude += INC_ALTITUDE; 
}

/*
 * Rotina que diminui a altitude
 */
void OnDownKey (void)
{
  if (altitude > MIN_ALTITUDE)
    altitude -= INC_ALTITUDE; 
}

/*
 * Rotina que aumenta a velocidade 
 */
void OnIncKey (void)
{
  if (incFrame < MAX_INC_FRAME)
    incFrame++; 
}

/*
 * Rotina que diminui a velocidade
 */
void OnDecKey (void)
{
  if (incFrame > MIN_INC_FRAME)
    incFrame--; 
}


/*
 * Rotina que trata o redimensionamento da janela
 */
void OnResize (GLsizei w, GLsizei h)
{
  h = (h == 0) ? 1 : h;
  glViewport (0, 0, w, h);
	Project (w,h);

  lastWidth = w;
  lastHeight = h;
}

/*
 * Cria a projecção
 */
void Project (GLsizei w, GLsizei h)
{
  GLdouble xEye, yEye, zEye;
  GLdouble xTarget, yTarget, zTarget;
  GLdouble xUpVector, yUpVector, zUpVector;
  static GLdouble angle = 0.0f;
  GLdouble cosAngle, sinAngle;

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  
	if (w <= h) 
	  glScalef (1, (GLfloat)w/(GLfloat)h, 1);
	else 
		glScalef ((GLfloat)h/(GLfloat)w, 1, 1);

  gluPerspective (45, 1, 0.5, 100.0);


  
  /* Coloca a camera no sitio actual */

  angle += 10 * currentFrame;
  if (angle > 360)
    angle -=360;

  cosAngle = cos (UTIL_TO_RADIANS (angle));
  sinAngle = sin (UTIL_TO_RADIANS (angle));

  if (isAbove) { /* Vista de cima */
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
  else { /* Percurso normal */
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

  gluLookAt ( xEye,           yEye,      zEye,   /* Posicao do olho */
              xTarget,     yTarget,   zTarget,   /* Posicao do ponto de referencia */  
              xUpVector, yUpVector, zUpVector);  /* Up Vector */


  /* Transformações referentes às projecções dos objectos */
}


/*
 * Inicializa a iluminação da cena
 */
void TurnOnLighting (void)
{
  GLfloat position[] = {1.0, 1.0, 1.0, 1.0}; /* Vector de Iluminação */
  GLfloat ambient [] = {1.0, 1.0, 1.0, 1.0}; /* RGBA da cor ambiente */

  glShadeModel (GL_SMOOTH); /* Sabemos que é o default mas é só para realçar */
  glEnable (GL_LIGHTING);
  glEnable (GL_LIGHT0);
  glDepthFunc (GL_LESS);
  glEnable (GL_DEPTH_TEST);
  glEnable (GL_COLOR_MATERIAL);
  
  glLightModeli (GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	glLightModelfv (GL_LIGHT_MODEL_AMBIENT, ambient);
  glLightfv (GL_LIGHT0, GL_POSITION, position);
  glColorMaterial (GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
}
