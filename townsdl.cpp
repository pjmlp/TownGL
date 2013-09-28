/* townwnd.cpp - OpenGL OS glue for Windows.
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

#include <cstdlib>
#include <SDL.h>

#include <GL/glew.h>


#include "town.h"


/**
* Handles keyboard notifications
* @param sym key code
*/
static void Town_OnChar(SDL_Keycode sym)
{
	switch (sym) {
	case SDLK_p : OnPKey ();
		break;

	case SDLK_v : OnVKey ();
		break;

	case SDLK_l : OnLKey ();
		break;

	case SDLK_a : OnIncKey ();
		break;

	case SDLK_z : OnDecKey ();
		break;

	case SDLK_UP : OnUpKey ();
		break;

	case SDLK_DOWN : OnDownKey ();
		break;

	}
}

/**
* Application entry point.
*/
int main (int argc, char** argv)
{
	atexit(SDL_Quit); // Make sure SDL is always properly terminated

	if (SDL_Init(SDL_INIT_EVERYTHING) < -1) {
		SDL_Log("Error initializing SDL %s\n", SDL_GetError());
		return -1;
	}

	SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 5 );
	SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 5 );
	SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 5 );
	SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 );
	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

	SDL_Window *screen = SDL_CreateWindow("TownGL",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		640, 480,
		SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

	if ( screen == NULL ) {
		SDL_Log("Couldn't set GL mode: %s\n", SDL_GetError());
		return -1;
	}

	SDL_GLContext glcontext = SDL_GL_CreateContext(screen);

	// Initialize GLEW
	GLenum err = glewInit();
	if (GLEW_OK != err) {
		SDL_Log("Couldn't configure GLEW: %s\n", SDL_GetError());
		return -1;
	}
	InitializeGL ();
	OnResize (640, 480);

	bool done = false;
	while (!done) {
		SDL_Event ev;
		while (!done && SDL_PollEvent(&ev)) {
			if (ev.type == SDL_WINDOWEVENT) {
				switch(ev.window.event){
				case SDL_WINDOWEVENT_RESIZED:
					OnResize (ev.window.data1, ev.window.data2);
					break;

				case SDL_WINDOWEVENT_CLOSE:
					done = true;
					break;
				}
			}
			else if (ev.type == SDL_KEYDOWN) {
				Town_OnChar(ev.key.keysym.sym);
			}
		}


		MainLoop();
		SDL_GL_SwapWindow(screen);
	}
	SDL_GL_DeleteContext(glcontext);


	return 0;
}


