/* town.cpp - Draws the town.
* Copyright (C) 2012 Paulo Pinto
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
#include <cstdio>
#include <cmath>
#include <ctime>
#include <SDL.h>

#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "world.h"
#include "pi.h"
#include "app.h"

// Initialize constant fields
// Maximum altitude allowed for the view from above.
const GLint Application::MAX_ALTITUDE = 100;

// Minimum altitude allowed for the view from above.
const GLfloat Application::MIN_ALTITUDE = 0.5f;

// Increment/decrement step for the altitude change.
const GLfloat Application::INC_ALTITUDE = 0.5f;

// Starting altitude when the user changes view mode.
const GLint Application::DEFAULT_ALTITUDE = 53;

Application::Application() : currentTime(clock())
{
}

Application::~Application()
{
    // Nothing to do
}

/**
 * Sets the initial configuration of the demo.
 */
void Application::initializeGL()
{
     glDepthFunc(GL_LESS);
     glEnable(GL_DEPTH_TEST);

     glClearColor(0, 0, 0.5, 0);
     glLineWidth(3);

    world.createScene();
}



/**
 * Updates the application's state
 */
void Application::mainLoop()
{
    clock_t now = clock();
    GLfloat duration = (now - currentTime) / static_cast<GLfloat>(CLOCKS_PER_SEC);

    currentFrame = duration;
    project(lastWidth, lastHeight);
    world.update(duration);
    world.render();

    currentTime = now;
}


/**
 * Changes the user's viewpoint
 */
void Application::changeViewPoint()
{
    isAbove = !isAbove;
    altitude = isAbove ? DEFAULT_ALTITUDE : MIN_ALTITUDE;
}

/**
 * Enables/disables the demo lighting.
 */
void Application::changeLighting()
{
    isLightOn = !isLightOn;
}

/**
 * Increases the viewer's height.
 */
void Application::increaseAltitude()
{
    if (altitude < MAX_ALTITUDE || isAbove)
        altitude += INC_ALTITUDE;
}

/**
 * Decreases the viewer's height.
 */
void Application::decreaseAltitude()
{
    if (altitude > MIN_ALTITUDE)
        altitude -= INC_ALTITUDE;
}

/**
 * Handles the window resize by the user.
 */
void Application::onResize(GLsizei w, GLsizei h)
{
    h = (h == 0) ? 1 : h;
    glViewport(0, 0, w, h);
    project(w, h);

    lastWidth = w;
    lastHeight = h;
}


/**
 * Sets up the OpenGL projection, based on the window size.
 * @param w windows' width
 * @param h windows' height
 */
void Application::project(GLsizei w, GLsizei h)
{
    GLfloat xEye, yEye, zEye;
    GLfloat xTarget, yTarget, zTarget;
    GLfloat xUpVector, yUpVector, zUpVector;
    static GLfloat angle = 0.0f;
    GLfloat cosAngle, sinAngle;

    glm::mat4 identity;
    glm::mat4 scale;


    if (w <= h)
        scale = glm::scale(identity, glm::vec3(1, static_cast<GLfloat>(w) / static_cast<GLfloat>(h), 1));
    else
        scale = glm::scale(identity, glm::vec3(static_cast<GLfloat>(h) / static_cast<GLfloat>(w), 1, 1));

    const GLfloat aspect = 1.0f;
    const GLfloat fovy = 45;
    const GLfloat zNear = 0.5f;
    const GLfloat zFar = 100.0f;
    const GLfloat height = zNear*tan(fovy*0.008841941282883074f);
    const GLfloat width = height * aspect;
    glm::mat4 frustum = glm::frustum(-width, width, -height, height, zNear, zFar);



    // sets the camera on the proper place.

    angle += 10 * currentFrame;
    if (angle > 360)
        angle -= 360;

    cosAngle = cos(toRadians(angle));
    sinAngle = sin(toRadians(angle));

    if (isAbove) { /* view from above */
        xTarget = 0;
        yTarget = 0;
        zTarget = 0;

        xEye = 0;
        yEye = altitude;
        zEye = 0;

        xUpVector = 0.0;
        yUpVector = 0.0;
        zUpVector = -1.0;
    }
    else { /* normal route */
        const GLfloat radius = 9.5f;
        xEye = radius * cosAngle;
        yEye = altitude;
        zEye = radius * sinAngle;

        xTarget = xEye + cos(toRadians(98 + angle));
        yTarget = altitude;
        zTarget = zEye + sin(toRadians(98 + angle));


        xUpVector = 0.0;
        yUpVector = 1.0;
        zUpVector = 0.0;
    }

    glm::mat4 lookAt = glm::lookAt(glm::vec3(xEye, yEye, zEye),
        glm::vec3(xTarget, yTarget, zTarget),
        glm::vec3(xUpVector, yUpVector, zUpVector));


    glm::mat4 camera = scale * frustum * lookAt;
    world.setWorldMatrix(camera);
}
