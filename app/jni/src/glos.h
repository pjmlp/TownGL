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

// for the compilers that support it. a bit faster than include guards
#pragma once

#ifdef __ANDROID__
    #include <EGL/egl.h>
    #include <GLES2/gl2.h>

    // No Glew on Android, always return true
    #define InitializeGlew() (true)

    // shader paths
    #define VERTEX_SHADER  R"(shaders/mobile/vertex.glsl)"
    #define FRAGMENT_SHADER  R"(shaders/mobile/frag.glsl)"

    // OpenGL version
    #define OPEN_GL_PROFILE        SDL_GL_CONTEXT_PROFILE_ES
    #define OPEN_GL_PROFILE_MAJOR  2
    #define OPEN_GL_PROFILE_MINOR  0

#else
    #include <GL/glew.h>

    bool InitializeGlew();

    // shader paths
    #define VERTEX_SHADER  R"(vertex.glsl)"
    #define FRAGMENT_SHADER  R"(frag.glsl)"

    // OpenGL version
    #define OPEN_GL_PROFILE        SDL_GL_CONTEXT_PROFILE_COMPATIBILITY
    #define OPEN_GL_PROFILE_MAJOR  3
    #define OPEN_GL_PROFILE_MINOR  3

#endif //ANDROID

#endif /* GLOS_H_ */
