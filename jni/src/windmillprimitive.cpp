/* windmillprimitive.cpp -  Represents a Windmill that can be rendered.
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

#include <cmath>

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "glos.h"
#include "pi.h"
#include "windmillprimitive.h"

WindmillPrimitive::WindmillPrimitive() : base(1, 1, 1), roof(1, 0, 0.5f), drawAngle(0.0f)
{
    base.setColor(0.4f, 0.5f, 0, 0);  // brown

    glm::mat4 identity;
    glm::mat4 transform = glm::translate (identity, glm::vec3(0, 1, 0));
    roof.setTransform(transform);
    roof.setColor(1, 0, 0, 0);   // red

}

WindmillPrimitive::~WindmillPrimitive()
{

}

void WindmillPrimitive::update(GLfloat frame)
{
    /* temporary move here, this code should be removed when the framerate is fixed */
    drawAngle += 10 * frame;
    if (drawAngle > 360)
        drawAngle -= 360;

}

void WindmillPrimitive::render()
{
    GLfloat length = 0.75, lastX, lastY, x, y;
    GLint i;
    bool isFlag = false;

    glPushMatrix();


    // draws the base
    base.render();

    // draws the roof
   // glPushMatrix();
   // glTranslatef(0, 1, 0);
    roof.render();
  //  glPopMatrix();
#if 0
    // draws the sails
    glColor4f(1.0f, 0.8f, 0.0f, 0.0f);
    glTranslatef(0, 1, 1);
    glRotatef(drawAngle, 0.0f, 0.0f, 1.0f); //rotation applied to the sails
    lastX = length;
    lastY = 0.0;

    const GLint VERTEX_COUNT = 3;
    const GLint POINTS = 2;
    const GLint SLICES = 12;
    const int ELEMS = SLICES * VERTEX_COUNT * POINTS;
    GLfloat vertex[ELEMS];
    GLfloat countour[ELEMS];

    int idxx = 0;
    int idx = 0;

    for (i = 1; i <= SLICES; i++)
    {
        vertex[idx++] = lastX;
        vertex[idx++] = lastY;

        GLfloat angle = 2 * i * PI / SLICES;
        x = length * cos(angle);
        y = length * sin(angle);

        if (isFlag) {
            vertex[idx++] = x;
            vertex[idx++] = y;

            vertex[idx++] = 0;
            vertex[idx++] = 0;
        }
        else {
            vertex[idx++] = 0;
            vertex[idx++] = 0;

            vertex[idx++] = x;
            vertex[idx++] = y;
        }

        countour[idxx++] = lastX = x;
        countour[idxx++] = lastY = y;
        isFlag = !isFlag;
    }

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(POINTS, GL_FLOAT, 0, vertex);
    for (int i = 0; i < SLICES; i++) {
        if (i % 2 == 0)
            glDrawArrays(GL_TRIANGLES, i * VERTEX_COUNT, VERTEX_COUNT);
    }
    glDisableClientState(GL_VERTEX_ARRAY);
    /*
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(POINTS, GL_FLOAT, 0, countour);
    glDrawArrays(GL_LINE_STRIP, 0, idxx);
    glDisableClientState(GL_VERTEX_ARRAY);
    */
#endif
    glPopMatrix();
}
