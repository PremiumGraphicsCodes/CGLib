#version 150
in vec3 position;
in vec4 color;
in vec2 texCoord;
out vec4 vColor;
out vec2 vTexCoord;

uniform mat4 projectionMatrix;
uniform mat4 modelviewMatrix;

void main(void)
{
	gl_Position = projectionMatrix * modelviewMatrix * vec4( position, 1.0 );
	vColor = color;
	vTexCoord = texCoord;
}