#version 150
layout( points ) in;
layout( triangle_strip, max_vertices = 4) out;
in float vDensity[];
in float vPointSizeX[];
in float vPointSizeY[];
uniform mat4 projectionMatrix;
uniform mat4 modelviewMatrix;

out float gDensity;
out	vec2 gTexCoord;

void main() {
	vec4 center = projectionMatrix * modelviewMatrix * gl_in[0].gl_Position;
	float pointSizeX = vPointSizeX[0];
	float pointSizeY = vPointSizeY[0];

	gl_Position.x = center.x - pointSizeX;
	gl_Position.y = center.y + pointSizeY;
	gDensity = vDensity[0];
	gTexCoord = vec2( 0.0, 1.0);
	EmitVertex();
 
	gl_Position.x = center.x - pointSizeX;
	gl_Position.y = center.y - pointSizeY;
	gDensity = vDensity[0];
	gTexCoord = vec2( 0.0, 0.0);
	EmitVertex();
 
	gl_Position.x = center.x + pointSizeX;
	gl_Position.y = center.y + pointSizeY;
	gDensity = vDensity[0];
	gTexCoord = vec2( 1.0, 1.0);
	EmitVertex();
 
	gl_Position.x = center.x + pointSizeX;
	gl_Position.y = center.y - pointSizeY;
	gDensity = vDensity[0];
	gTexCoord = vec2( +1.0, 0.0);
	EmitVertex();
}