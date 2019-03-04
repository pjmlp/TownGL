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

#include "effect.h"
#include "mesh.h"

Mesh::Mesh(GLint coordinatesPerVertex, RenderMode mode):
coordinatesPerVertex(coordinatesPerVertex), drawMode(mode),
r(0.0f), g(0.0f), b(0.0f), a(0.0f), transform(1.0f), uploaded(false),
bufferObject(0)
{
}

Mesh::~Mesh()
{
    if (bufferObject) {
        glDeleteBuffers(1, &bufferObject);
    }
}

/**
 * Renders the current mesh.
 */
void Mesh::render(Effect& shaders)
{
    if (uploaded && (vertex.size() > 0)) {
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
            shaders.setUniform("color", glm::vec3(r, g, b));
            shaders.setLocalMatrix(transform);
            
            glEnableVertexAttribArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, bufferObject);

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
            glDrawArrays(renderMode, 0, count);

            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glDisableVertexAttribArray(0);
        }
    }
}

/**
 *  Adds a vertex to the mesh with the usual set of (x, y, z) coordinates.
 */
void Mesh::addVertex(GLfloat x, GLfloat y, GLfloat z)
{
    assert(!uploaded);
    vertex.push_back(x);
    vertex.push_back(y);
    vertex.push_back(z);
}

/**
*  Add a vertex vector where the entries are expected to be of the form (x, y, z) coordinates.
*/
void Mesh::addVertices(const std::vector<GLfloat> &vertices)
{
    assert(!uploaded);
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
 * Allows for mesh updates that depend on the current frame.
 */
void  Mesh::update(GLfloat frame)
{
}

/**
 * Local transformation to be used by the mesh when rendering.
 */
void  Mesh::setTransform(const glm::mat4 &transform)
{
    this->transform = transform;
}


/**
 * Uploads the mesh data to the graphics card. After the data is
 * loaded any attempt to add more vertices will terminate the application.
 */
void  Mesh::upload()
{
    glGenBuffers(1, &bufferObject);

    glBindBuffer(GL_ARRAY_BUFFER, bufferObject);
    glBufferData(GL_ARRAY_BUFFER, vertex.size() * sizeof(GLfloat), &vertex[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    uploaded = true;
}