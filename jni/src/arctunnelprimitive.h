/* arctunnelprimitive.h -  Represents an arc tunnel that can be rendered.
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

#ifndef ARCTUNNELPRIMITIVE_H_
#define ARCTUNNELPRIMITIVE_H_

#pragma once

#include "primitive.h"

/**
 * A tunnel in an arch form.
 */
class ArcTunnelPrimitive: public Primitive {
public:
    ArcTunnelPrimitive(const glm::mat4 &transform);
    virtual ~ArcTunnelPrimitive();
};

#endif /* ARCTUNNELPRIMITIVE_H_ */
