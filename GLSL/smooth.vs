#version 150
in vec3 position;
in vec3 normal;
out vec3 vColor;
out vec3 vNormal;
uniform mat4 projectionMatrix;
uniform mat4 modelviewMatrix;

void main(void) {
	gl_Position = projectionMatrix * modelviewMatrix * vec4( position, 1.0 );
	vColor = vec3(0.0, 0.0, 0.0);
	vNormal = normalize(normal);
}