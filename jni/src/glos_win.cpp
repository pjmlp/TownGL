/* glos_win.cpp -  Contains OpenGL platform specific issues for Windows
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

#include "SDL.h"

/**
 * Used for Glew Initialization on Windows.
 */
bool InitializeGlew()
{
	// Initialize GLEW
	GLenum err = glewInit();
	return (GLEW_OK == err);
}

GLint showOpenGLError(const char *file, const GLint line)
{

    GLenum glErr;
    GLint    retCode = 0;

    glErr = glGetError();
    if (glErr != GL_NO_ERROR)
    {
        SDL_Log("glError in file %s @ line %d: %s\n",
            file, line, gluErrorString(glErr));
        retCode = 1;
    }
    return retCode;
}