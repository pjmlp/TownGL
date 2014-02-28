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
#include <cstring>
#include <SDL.h>

#include "glos.h"


#include "town.h"


/**
* Handles keyboard notifications
* @param sym key code
* @param paused the current pause state.
* @param done out parameter to let the application know it is time to finish execution
*/
static void HandleKeys(SDL_Keycode sym, bool &paused, bool &done)
{
	switch (sym) {
    case SDLK_p: paused = !paused;
		break;

	case SDLK_v : ChangeViewPoint ();
		break;

	case SDLK_l : ChangeLighting ();
		break;

	case SDLK_UP : IncreaseAltitude ();
		break;

	case SDLK_DOWN : DecreaseAltitude ();
		break;

	case SDLK_ESCAPE :
        done = true;
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

	int modeCount;
	if ( (modeCount = SDL_GetNumDisplayModes(0)) < 1) {
		SDL_Log("Couldn't not query number of available display modes: %s\n", SDL_GetError());
		return -1;
	}

    // Query the window mode
	SDL_DisplayMode mode;
	if (SDL_GetDisplayMode(0, 0, &mode) < 0) {
		SDL_Log("Couldn't not query display modes: %s\n", SDL_GetError());
		return -1;
	}

	SDL_Log("mode: %d x %d\n", mode.w, mode.h);

	SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 5 );
	SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 5 );
	SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 5 );
	SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 );
	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

    int width, height;
    Uint32 flags;

    if (argc > 1 && strncmp(argv[1], "-w", 2) == 0) {
        width = 800;
        height = 600;
        flags = SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL;
    }
    else {
        width = mode.w;
        height = mode.h;
        flags = SDL_WINDOW_FULLSCREEN | SDL_WINDOW_OPENGL;
    }

    SDL_Window *screen = SDL_CreateWindow("TownGL",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        width, height, flags);

	if ( screen == nullptr ) {
		SDL_Log("Couldn't set GL mode: %s\n", SDL_GetError());
		return -1;
	}

	SDL_GLContext glcontext = SDL_GL_CreateContext(screen);

	if (!InitializeGlew()) {
		SDL_Log("Couldn't configure GLEW: %s\n", SDL_GetError());
		return -1;
	}
    
	InitializeGL ();
	OnResize (mode.w, mode.h);

	bool done = false;
    bool paused = false;
	while (!done) {
		SDL_Event ev;
		while (!done && SDL_PollEvent(&ev)) {
			if (ev.type == SDL_WINDOWEVENT) {
				switch(ev.window.event){
				case SDL_WINDOWEVENT_SIZE_CHANGED:
				case SDL_WINDOWEVENT_RESIZED:
					OnResize (ev.window.data1, ev.window.data2);
					break;

				case SDL_WINDOWEVENT_CLOSE:
					done = true;
					break;
				}
			}
			else if (ev.type == SDL_KEYDOWN) {
				HandleKeys(ev.key.keysym.sym, paused, done);
			} else if (ev.type == SDL_FINGERDOWN) {
                paused = !paused;
			} else if (ev.type == SDL_FINGERMOTION) {
				if (ev.tfinger.dy > 0) {
					IncreaseAltitude();
				} else if (ev.tfinger.dy < 0) {
					DecreaseAltitude();
				}
			} else if (ev.type == SDL_QUIT) {
				done = true;
			}
		}
        if (!paused) {
            MainLoop();
            SDL_GL_SwapWindow(screen);
        }
	}
	SDL_GL_DeleteContext(glcontext);


	return 0;
}


