#version 101

precision mediump float;
 
uniform vec3 color;

void main()
{
    gl_FragColor = vec4(color,0.0);
}
