/* world.cpp - Model drawing functions for the town
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
#include <cmath>
#include <cassert>

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "c++14.h"
#include "glos.h"
#include "pi.h"
#include "diskprimitive.h"
#include "boxprimitive.h"
#include "arcprimitive.h"
#include "roofprimitive.h"
#include "cylinderprimitive.h"
#include "primitive.h"
#include "arctunnelprimitive.h"
#include "tunnelprimitive.h"
#include "windmillprimitive.h"
#include "effect.h"

#include "world.h"


void World::createScene()
{
    glm::mat4 identity;
    glm::mat4 translation = glm::rotate(identity, toRadians(-90.0f), glm::vec3(1, 0, 0));

    // sets the floor
    objects.push_back(std::make_unique<DiskPrimitive>(0.0f, 50.0f, 10));
    objects.back()->setColor(0.2f, 0.3f, 0.5f, 0.0f);
    objects.back()->setTransform(translation);

    // sets the road
    objects.push_back(std::make_unique<DiskPrimitive>(9.0f, 11.0f, 25));
    objects.back()->setColor(0, 0, 0, 0);

    translation = glm::translate(identity, glm::vec3(0, 0.1f, 0));
    glm::mat4 transform = glm::rotate(translation, toRadians(-90.0f), glm::vec3(1, 0, 0));
    objects.back()->setTransform(transform);

    // creates the windmills
    translation = glm::translate(identity, glm::vec3(4.2f, 0.0f, 13.0f));
    objects.push_back(std::make_unique<WindmillPrimitive>(translation));

    translation = glm::translate(identity, glm::vec3(15.0f, 0.0f, -15.0f));
    objects.push_back(std::make_unique<WindmillPrimitive>(translation));

    // creates the tunnels
    translation = glm::translate(identity, glm::vec3(0.0f, 0.0f, -10.0f));
    glm::mat4 scale = glm::scale(translation, glm::vec3(1.0f, 0.5f, 0.5f));
    glm::mat4 rotation = glm::rotate(scale, toRadians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    objects.push_back(std::make_unique<ArcTunnelPrimitive>(rotation));

    translation = glm::translate(identity, glm::vec3(-6.0f, 0.0f, 8.0f));
    scale = glm::scale(translation, glm::vec3(0.5f, 2.0f, 0.5f));
    rotation = glm::rotate(scale, toRadians(60.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    objects.push_back(std::make_unique<TunnelPrimitive>(rotation));

    translation = glm::translate(identity, glm::vec3(10.0f, 4.0f, -17.0f));

    // creates the buildings
    objects.push_back(std::make_unique<BoxPrimitive>(2.0f, 8.0f, 2.0f));
    objects.back()->setTransform(translation);
    objects.back()->setColor(0, 0, 1, 0);

    translation = glm::translate(identity, glm::vec3(-15.0f, 4.0f, -10.0f));
    objects.push_back(std::make_unique<BoxPrimitive>(2.0f, 8.0f, 2.0f));
    objects.back()->setTransform(translation);
    objects.back()->setColor(0, 1, 0, 0);

    translation = glm::translate(identity, glm::vec3(13.0f, 4.0f, 8.0f));
    objects.push_back(std::make_unique<BoxPrimitive>(2.0f, 8.0f, 2.0f));
    objects.back()->setTransform(translation);
    objects.back()->setColor(1, 0, 0, 0);

    // now load the respective shaders
    shaders.loadShaders(VERTEX_SHADER, FRAGMENT_SHADER);
    shaders.validate();
}

/**
* Allows all objects to update their state for the current frame
* @param frame current animation frame.
*/
void World::update(GLfloat frame)
{
    for (auto& obj : objects) {
        obj->update(frame);
    }

}

/**
* Draws the world representing the town.
* @param frame current animation frame.
*/
void World::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glMatrixMode(GL_MODELVIEW);

    if (shaders.isValid()) {
        shaders.bind();

        shaders.setWorldMatrix(worldMatrix);

        for (auto& obj : objects) {
            obj->render(shaders);
        }

        shaders.unbind();
    }

}


void World::setWorldMatrix(const glm::mat4& world)
{
    worldMatrix = world;
}