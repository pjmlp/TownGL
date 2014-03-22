/* primitive.cpp -  Represents a 3D object that can be rendered.
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

#include "glos.h"
#include "primitive.h"

Primitive::~Primitive()
{
    // nothing to do
}

/**
* Updates the state of each element.
* Affects all imeditate children.
*
* @param frame The current time
*/
void Primitive::update(GLfloat frame)
{
    for (auto& child : children)
        child->update(frame);
}

/**
 * Applies the transformation matrix to the primitive.
 * Affects all imeditate children.
 *
 * @param transform The matrix in column major format, as expected by OpenGL
 */
void Primitive::setTransform(const glm::mat4 &transform)
{
    for (auto& child : children)
        child->setTransform(transform);
}

/**
 * Sets the primitive color. Affects all imeditate children. The standard RGBA values.
 *
 */
void Primitive::setColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
    for (auto& child : children)
        child->setColor(r, g, b, a);
}


/**
 * Renders all imeditate children.
 *
 */
void Primitive::render()
{
    for (auto& child : children)
        child->render();
}


/**
 * Adds a new node to the group
 */
void Primitive::addChild(std::unique_ptr<Node> child)
{
    children.push_back(std::move(child));
}