/* DiskPrimitive.h -  Represents a simple 2D circle.
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

#ifndef DiskPrimitive_H_
#define DiskPrimitive_H_

// for the compilers that support it. a bit faster than include guards
#pragma once

#include "primitive.h"
#include "glos.h"

/**
 * Mesh for rendering circles similar to gluDisk.
 */
class DiskPrimitive: public Primitive {
public:
	DiskPrimitive(GLfloat innerRadius, GLfloat outerRadius, GLint slices);
	virtual ~DiskPrimitive();
};

#endif /* DiskPrimitive_H_ */
