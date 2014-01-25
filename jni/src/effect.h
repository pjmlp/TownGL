/* effect.h -  Represents a set of shader effects.
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

#ifndef EFFECT_H_
#define EFFECT_H_

#include <string>

#include <glm/fwd.hpp>

#include "glos.h"


class Effect final {
public:
    explicit Effect();
    ~Effect();

    void loadShaders(const std::string& vertexShader, const std::string& fragmentShader);

    GLuint getProgramId();

    void bind();
    void unbind();

    void setWorldMatrix(const glm::mat4& world);
    void setLocalMatrix(const glm::mat4& local);

private:
    void logError();
    GLuint id;
};

#endif /* EFFECT_H_ */
