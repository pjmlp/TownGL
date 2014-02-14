/* CylinderPrimitive.h -  Represents a cylinder circle.
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

#ifndef CylinderPrimitive_H_
#define CylinderPrimitive_H_

#include <vector>
#include <memory>

#include "primitive.h"
#include "glos.h"

// forward declarations
class Mesh;

/**
 * Mesh for rendering cylinders
 */
class CylinderPrimitive: public Primitive {
public:
    CylinderPrimitive(GLfloat lowerRadius, GLfloat upperRadius, GLfloat height);
    virtual ~CylinderPrimitive();

    virtual void setTransform(const glm::mat4 &transform) override;
    virtual void setColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a) override;
	virtual void render () override;
private:
    std::vector<std::unique_ptr<Mesh>> meshdata;
};

#endif /* CylinderPrimitive_H_ */
