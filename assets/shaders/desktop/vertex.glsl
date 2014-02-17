#version 120

uniform sampler2D texture0;
varying vec4 outcolor;
varying vec2 outtexture;

void main()
{
	vec4 color = texture2D(texture0,outtexture);
	gl_FragColor = outcolor * color;
}