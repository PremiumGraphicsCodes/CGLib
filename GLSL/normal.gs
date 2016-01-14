#version 150
layout( points ) in;
layout(line_strip, max_vertices = 2) out;
//layout( points, max_vertices = 1 ) out;
uniform mat4 projectionMatrix;
uniform mat4 modelviewMatrix;
uniform float scale;
in vec3 vColor[];
in vec3 vVector[];
out vec3 gColor;

void main() {
	gl_Position = projectionMatrix * modelviewMatrix * gl_in[0].gl_Position;
	gColor = vColor[0];
	EmitVertex();
	gl_Position = projectionMatrix * modelviewMatrix * ( gl_in[0].gl_Position + vec4( vVector[0], 0.0 ) * scale );
	gColor = vColor[0];
	EmitVertex();
	EndPrimitive();
}