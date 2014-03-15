/* mesh.h -  Represents a Mesh that can be rendered.
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

#ifndef MESH_H_
#define MESH_H_

#pragma once

#include <vector>
#include <memory>

#include <glm/mat4x4.hpp>

#include "glos.h"

#include "node.h"

/**
 * Represents a generic mesh object.
 */
class Mesh : public Node {
public:
    enum class RenderMode { triangles, triangle_strip, triangle_fan, line_strip };

    explicit Mesh(GLint coordinatesPerVertex, RenderMode mode);
	virtual ~Mesh();

	virtual void render () override;

    void addVertex(GLfloat x, GLfloat y, GLfloat z);
    void addVertices(const std::vector<GLfloat> &vertices);

    void setColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a) override;


    void setTransform(const glm::mat4 &transform) override;

private:
    GLint coordinatesPerVertex;
    RenderMode drawMode;

    std::vector<GLfloat> vertex;

    GLfloat r, g, b, a;

    glm::mat4 transform;
};

#endif /* MESH_H_ */
