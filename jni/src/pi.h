/* pi.h -  Pi related utility methods
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
#ifndef PI_H_
#define PI_H_

// for the compilers that support it. a bit faster than include guards
#pragma once

const GLfloat PI = 3.1415926535897932384626433832795f;

inline GLfloat toRadians(GLfloat angle) { return angle * PI / 180; }

#endif /* PI_H_ */