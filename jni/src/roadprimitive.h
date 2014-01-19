/* roadprimitive.h -  Represents a road that can be rendered.
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

#ifndef ROADPRIMITIVE_H_
#define ROADPRIMITIVE_H_

#include "primitive.h"
#include "diskmesh.h"

/**
* Draws a circular road around the buildings.
*/
class RoadPrimitive: public Primitive {
public:
    RoadPrimitive();
    virtual ~RoadPrimitive();

	virtual void render () override;

private:
    DiskMesh road;
};

#endif /* ROADPRIMITIVE_H_ */
