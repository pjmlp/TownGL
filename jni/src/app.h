/* app.h -  Application logic
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

#ifndef APP_H_
#define APP_H_

#include <ctime>

#include "glos.h"

#include "world.h"




/**
 * Class responsible for handling the whole application logic.
 */
class Application {
public:
    explicit Application();
    virtual ~Application();
        
    void mainLoop();
    void changeViewPoint();
    void changeLighting();

    void increaseAltitude();
    void decreaseAltitude();
    void onResize(GLsizei w, GLsizei h);
    void project(GLsizei w, GLsizei h);
    void initializeGL();

private:
    // Maximum altitude allowed for the view from above.
    static const GLint MAX_ALTITUDE;

    // Minimum altitude allowed for the view from above.
    static const GLfloat MIN_ALTITUDE;

    // Increment/decrement step for the altitude change.
    static const GLfloat INC_ALTITUDE;

    // Starting altitude when the user changes view mode.
    static const GLint DEFAULT_ALTITUDE;

    // Using the overhead view.
    bool isAbove = false;

    // Current window size
    GLsizei lastWidth, lastHeight;

    // Current altitude
    GLfloat altitude = 0.5;

    // Is the lightning enabled.
    bool isLightOn = true;

    // time at the begining of the frame
    clock_t currentTime;

    // Frame value in terms of time.
    GLfloat currentFrame = 0.0f;

    // The object graph of the 3d World
    World world;
};

#endif //APP_H_
