/* effect.cpp -  Represents a set of shader effects.
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
#include <memory>

#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <SDL.h>

#include "glos.h"
#include "effect.h"


Effect::Effect()
{
    id = glCreateProgram();
}

Effect::~Effect()
{
    if (id != 0) {
        glDeleteProgram(id);
    }
}

void Effect::loadShaders(const std::string& vertexShader, const std::string& fragmentShader)
{
}

GLuint Effect::getProgramId()
{
    return id;
}

void Effect::bind()
{
    assert(id != 0);
    glUseProgram(id);
}

void Effect::unbind()
{
    glUseProgram(0);
}

void Effect::setWorldMatrix(const glm::mat4& world)
{

}

void Effect::setLocalMatrix(const glm::mat4& local)
{

}

void Effect::logError()
{
    GLint length;
    glGetProgramiv(id, GL_INFO_LOG_LENGTH, &length);
    if (length > 0)
    {
        auto log = std::unique_ptr<GLchar>(new GLchar[length]);
        glGetProgramInfoLog(id, length, &length, log.get());
        SDL_Log("Program link log:\n%s", log.get());
    }
}