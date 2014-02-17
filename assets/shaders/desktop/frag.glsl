#version 120

uniform mat4 modelview;
attribute vec4 position;
attribute vec3 normal;
attribute vec3 color;
attribute vec2 texture;
varying vec4 outcolor;
varying vec2 outtexture;

void main()
{
	gl_Position = modelview * position;
	vec4 light = vec4(-20,0,-40,0) * modelview;
	vec3 lightDir = light.xyz;

	float cosAngIncidence = dot(normalize(normal), normalize(lightDir));
	cosAngIncidence = clamp(cosAngIncidence, 0, 1);
	outcolor = vec4(color,1.0) * cosAngIncidence + vec4(0.1,0.1,0.1,1.0);
	outtexture = texture;
}