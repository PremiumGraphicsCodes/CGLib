#version 150
in vec3 position;
in vec4 color;
out vec4 vColor;

uniform mat4 projectionMatrix;
uniform mat4 modelviewMatrix;

void main(void)
{
	gl_Position = projectionMatrix * modelviewMatrix * vec4( position, 1.0 );
	vColor = color;
}