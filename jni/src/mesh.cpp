/* mesh.cpp -  Represents a Mesh that can be rendered.
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

#include <cassert>
#include <algorithm>

#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "mesh.h"

Mesh::Mesh(GLint coordinatesPerVertex, RenderMode mode) : coordinatesPerVertex(coordinatesPerVertex), drawMode(mode), g(0.0f), b(0.0f), a(0.0f), transform(1.0f)
{
}

Mesh::~Mesh()
{
}

/**
 * Renders the current mesh.
 */
void Mesh::render()
{
    if (vertex.size() > 0) {
        GLint count = 0;
        GLenum renderMode = GL_TRIANGLES;
        switch (drawMode) {
        case RenderMode::triangles:
            renderMode = GL_TRIANGLES;
            count = vertex.size() / coordinatesPerVertex;
            break;

        case RenderMode::triangle_strip:
            renderMode = GL_TRIANGLE_STRIP;
            count = vertex.size();
            break;

        case RenderMode::triangle_fan:
            renderMode = GL_TRIANGLE_FAN;
            count = vertex.size() / coordinatesPerVertex;
            break;

        case RenderMode::line_strip:
            renderMode = GL_LINE_STRIP;
            count = vertex.size() / coordinatesPerVertex;
            break;

        default:
            assert(false);
        }

        if (count > 0) {
            glPushMatrix();
            glLoadMatrixf(glm::value_ptr(transform));

            glColor4f(r, g, b, a);

            glEnableClientState(GL_VERTEX_ARRAY);

            glVertexPointer(coordinatesPerVertex, GL_FLOAT, 0, &vertex[0]);

            glDrawArrays(renderMode, 0, count);

            glDisableClientState(GL_VERTEX_ARRAY);

            glPopMatrix();
        }
    }
}

/**
 *  Adds a vertex to the mesh with the usual set of (x, y, z) coordinates.
 */
void Mesh::addVertex(GLfloat x, GLfloat y, GLfloat z)
{
    vertex.push_back(x);
    vertex.push_back(y);
    vertex.push_back(z);
}

/**
*  Add a vertex vector where the entries are expected to be of the form (x, y, z) coordinates.
*/
void Mesh::addVertices(const std::vector<GLfloat> &vertices)
{
    vertex.reserve(vertex.size() + vertices.size()); // preallocate memory
    vertex.insert(end(vertex), begin(vertices), end(vertices));
}

/**
 * Set the global color for the whole mesh.
 */
void Mesh::setColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;

}

/**
 * Local transformation to be used by the mesh when rendering.
 */
void  Mesh::setTransform(const glm::mat4 &transform)
{
    this->transform = transform;
}
