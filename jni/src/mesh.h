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

#include "glos.h"

class Mesh {
public:
    enum class RenderMode { triangles, triangle_strip, triangle_fan };

    explicit Mesh();
    explicit Mesh(GLint coordinatesPerVertex, RenderMode mode);
	virtual ~Mesh();

	virtual void render ();

    void reserveMeshSize(GLint count);
    void addVertex(GLfloat x, GLfloat y);
    void addVertex(GLfloat x, GLfloat y, GLfloat z);
    void addVertices(const GLfloat *vertices, GLint size);

    void setColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a);

private:
    GLint coordinatesPerVertex;
    RenderMode drawMode;

    GLint idx;
    GLfloat *vertex;
    GLint vertexCount;

    GLfloat r, g, b, a;
};

#endif /* MESH_H_ */
