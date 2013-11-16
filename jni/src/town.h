/* townwnd.h -  Draws the town.
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

#ifndef TOWN_H_
#define TOWN_H_

#include "glos.h"
#include <SDL.h>

void DescribeProgram ();
void MainLoop (SDL_Window *screen);
void ChangePauseMode ();
void ChangeViewPoint ();
void ChangeLighting ();
void ResetSettings ();
void IncreaseAltitude ();
void DecreaseAltitude ();
void IncreaseSpeed ();
void DecreaseSpeed ();
void OnResize (GLsizei w, GLsizei h);
void Project (GLsizei w, GLsizei h);
void TurnOnLighting ();
void InitializeGL ();

#endif //TOWN_H_
