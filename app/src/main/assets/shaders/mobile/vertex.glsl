#version 100
 
uniform mat4 modelViewMatrix, projectionMatrix;
 
attribute vec4 position;
 
void main()
{
    gl_Position = projectionMatrix * modelViewMatrix * position ;
}
