/* BoxPrimitive.h -  Represents a box
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

#ifndef BoxPrimitive_H_
#define BoxPrimitive_H_

#include "mesh.h"
#include "primitive.h"

class BoxPrimitive :	public Primitive
{
public:
	BoxPrimitive(GLfloat width, GLfloat height, GLfloat depth);
	virtual ~BoxPrimitive();

    virtual void setColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a) override;
	virtual void render() override;
private:
	GLfloat width, height, depth;
    Mesh mesh;
};

#endif /* BoxPrimitive_H_ */