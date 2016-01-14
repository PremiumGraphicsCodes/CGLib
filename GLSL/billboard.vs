#version 150
in vec3 position;
in float density;
out float vDensity;
out float vPointSizeX;
out float vPointSizeY;
uniform mat4 projectionMatrix;
uniform mat4 modelviewMatrix;
uniform float pointSizeX;
uniform float pointSizeY;

void main(void)	{
	gl_Position = projectionMatrix * modelviewMatrix * vec4( position, 1.0 );
	vPointSizeX = pointSizeX / gl_Position.w;
	vPointSizeY = pointSizeY / gl_Position.w;
	vDensity = density;
}
