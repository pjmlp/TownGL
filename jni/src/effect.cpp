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
#include <cstdlib>

#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <SDL.h>

#include "glos.h"
#include "effect.h"


Effect::Effect() : id(0), valid(false)
{
}

Effect::~Effect()
{
    if (id != 0) {
        glDeleteProgram(id);
    }
}

void Effect::loadShaders(const std::string& vertexShader, const std::string& fragmentShader)
{
    assert(id == 0);
    id = glCreateProgram();

    GLuint vertex;
    
    GLint status = compileShader(readShaderFile(vertexShader), GL_VERTEX_SHADER, vertex);
    if (status != GL_TRUE) {
        return;
    }

    GLuint fragment;
    status = compileShader(readShaderFile(fragmentShader), GL_FRAGMENT_SHADER, fragment);
    if (status != GL_TRUE) {
        return;
    }
    glAttachShader(id, vertex);
    glAttachShader(id, fragment);

    // bind attribute locations
    // this needs to be done prior to linking
    glBindAttribLocation(id, 0, "position");

    glLinkProgram(id);

    GLint success;
    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if (success == GL_FALSE) {
        const int logLength = 1024;
        auto log = std::unique_ptr<GLchar>(new GLchar[logLength]);


        glGetProgramInfoLog(id, logLength, nullptr, log.get());
        SDL_Log("Error linking shader program: '%s'\n", logLength);
    }

    worldMatrix = glGetUniformLocation(id, "projectionMatrix");
    localMatrix = glGetUniformLocation(id, "modelViewMatrix");
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



GLuint Effect::compileShader(const std::string& source, GLenum type, GLuint& shaderId)
{

    const char * sources[1] = { source.c_str()  };
    GLint lengths[1] = { source.length() };

    shaderId = glCreateShader(type);				
    glShaderSource(shaderId, 1, sources, lengths);
    glCompileShader(shaderId);

    GLint logLength;
    glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &logLength);
    if (logLength > 0)
    {
        auto log = std::unique_ptr<GLchar>(new GLchar[logLength]);
        glGetShaderInfoLog(shaderId, logLength, &logLength, log.get());
        SDL_Log("Shader compile log:\n%s", log);
    }

    GLint status;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE)
    {
        SDL_Log("Failed to compile shader: %s\n", source.c_str());
    }

    return status;
}


void Effect::validate()
{
    assert(id != 0);
    glValidateProgram(id);

    GLint status;
    glGetProgramiv(id, GL_VALIDATE_STATUS, &status);
    if (status == GL_FALSE)
        logError("Programm validation failed");
    valid = (status == GL_TRUE);
}

bool Effect::isValid() const
{
    return valid;
}

void Effect::setWorldMatrix(const glm::mat4& world)
{
   glUniformMatrix4fv(worldMatrix, 1, GL_FALSE, glm::value_ptr(world));
}

void Effect::setLocalMatrix(const glm::mat4& local)
{
    glUniformMatrix4fv(localMatrix, 1, GL_FALSE, glm::value_ptr(local));
}

void Effect::setUniform(const std::string& name, const glm::vec3& data)
{
    GLint  uniform = glGetUniformLocation(id, name.c_str());
    if (uniform == -1) {
        SDL_Log("Could not bind uniform %s\n", name.c_str());
    }
    glUniform3f(uniform, data.x, data.y, data.z);
}

void Effect::logError(const std::string& msg)
{
    GLint length;
    glGetProgramiv(id, GL_INFO_LOG_LENGTH, &length);
    if (length > 0)
    {
        auto log = std::unique_ptr<GLchar>(new GLchar[length]);
        glGetProgramInfoLog(id, length, &length, log.get());
        SDL_Log("%s:\n%s", msg.c_str(), log.get());
    }
}

std::string Effect::readShaderFile(const std::string& filename)
{
    std::string result;
    SDL_RWops *file = SDL_RWFromFile(filename.c_str(), "r");
    if (file == nullptr) {
        SDL_Log("Could not open shader file %s", filename.c_str());
    }
    
    const GLint BUFFER_SIZE = 256;
    char buffer[BUFFER_SIZE + 1];
    memset(buffer, 0, BUFFER_SIZE);
    
    while (SDL_RWread(file, buffer, BUFFER_SIZE, 1) > 0) {
        result.append(buffer);
    }
    result.append(buffer);

    SDL_RWclose(file);

    // Success!
    return result;
}