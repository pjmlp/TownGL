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

#include <iostream>
#include <SDL.h>

#include "glos.h"
#include <GL/glew.h>


#include "town.h"


// window name
static const char* CAPTION_NAME = "TownGL";


/*** Protótipos das funções privadas ***/
static void Town_OnChar(SDL_Keycode sym);





/*** Funções privadas ***/


/*
* Processa a mensagem WM_CHAR
* Permite rodar a imagem.
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




int main (int argc, char** argv)
{
	atexit(SDL_Quit); // Make sure SDL is always properly terminated

	if (SDL_Init(SDL_INIT_EVERYTHING) < -1) {
		std::cout << "Error initializing SDL " << SDL_GetError() << std::endl;
		return -1;
	}

	SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 5 );
	SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 5 );
	SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 5 );
	SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 );
	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

	SDL_Window *screen = SDL_CreateWindow(CAPTION_NAME,
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		640, 480,
		SDL_WINDOW_FULLSCREEN | SDL_WINDOW_OPENGL);

	if ( screen == NULL ) {
		std::cout << "Couldn't set GL mode: " << SDL_GetError() << std::endl;
		return -1;
	}

	SDL_GLContext glcontext = SDL_GL_CreateContext(screen);

	// Initialize GLEW
	GLenum err = glewInit();
	if (GLEW_OK != err) {
		std::cout << "Couldn't configure GLEW: " << std::endl;
		return -1;
	}
	initializeGL ();

	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_WINDOWEVENT_RESIZED:
			OnResize (event.window.data1, event.window.data2);
			break;

		case SDL_KEYDOWN:
			Town_OnChar(event.key.keysym.sym);
			break;

		default:
			MainLoop();
		}
		SDL_GL_SwapWindow(screen);
	}

	SDL_GL_DeleteContext(glcontext);

	return 0;
}


