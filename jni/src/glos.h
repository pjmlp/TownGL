/* glos.h -  Contains OpenGL platform specific includes
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
#ifndef GLOS_H_
#define GLOS_H_

#ifdef ANDROID 
    #include <EGL/egl.h>
    #include <GLES/gl.h>

    void gluPerspective (GLfloat fovy, GLfloat aspect,  GLfloat zNear, GLfloat zFar);
    void gluLookAt (GLfloat eyex, GLfloat eyey, GLfloat eyez,
                    GLfloat centerx, GLfloat centery, GLfloat centerz,
                    GLfloat upx, GLfloat upy, GLfloat upz);

    // No Glew on Android, always return true
    #define InitializeGlew() (true)
#else
    #include <GL/glew.h>
    #include <GL/glut.h>

    bool InitializeGlew();
#endif //ANDROID

#endif /* GLOS_H_ */
