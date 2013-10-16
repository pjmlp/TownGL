/* glos.cpp -  Contains OpenGL platform specific includes
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

#include <cmath>


/**
 * OpenGL ES implementation of the well known GLU helper function.
 */
void gluPerspectiveES (GLfloat fovy, GLfloat aspect,  GLfloat zNear, GLfloat zFar)
{
    /*
    // Start in projection mode.
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    double xmin, xmax, ymin, ymax;
    ymax = zNear * tan(fovy * PI / 360.0);
    ymin = -ymax;
    xmin = ymin * aspect;
    xmax = ymax * aspect;

    glFrustum (xmin, xmax, ymin, ymax, zNear, zFar);*/

    GLfloat range=zNear*tan(fovy*0.008841941282883074f);
    aspect*=range;
    glFrustum(-aspect,aspect,-range,range,zNear,zFar);
}
