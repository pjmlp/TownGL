#version 330
 
uniform mat4 modelViewMatrix, projectionMatrix;
 
layout (location = 0) in vec4 position;
 
void main()
{
    gl_Position = projectionMatrix * modelViewMatrix * position ;
}
