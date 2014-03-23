/* primitive.h -  Represents a 3D object that can be rendered.
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

#ifndef PRIMITIVE_H_
#define PRIMITIVE_H_

// for the compilers that support it. a bit faster than include guards
#pragma once

#include <vector>
#include <memory>

#include <glm/fwd.hpp>

#include "glos.h"

#include "node.h"

/**
 * A 3D geometry object to be drawn.
 * Similar to nodes in 3D scene graphs
 */
class Primitive: public Node {
public:
    virtual ~Primitive();

    virtual void setTransform(const glm::mat4 &transform) override;
    virtual void setColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a) override;
    virtual void update(GLfloat frame) override;
    virtual void render(Effect& shaders) override;

    void addChild(std::unique_ptr<Node> child);

private:
    std::vector<std::unique_ptr<Node>> children;
};

#endif /* PRIMITIVE_H_ */
