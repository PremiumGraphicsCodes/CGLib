#version 150
in vec3 position;
in vec3 vector;
out vec3 vColor;
out vec3 vVector;
void main(void) { 
	gl_Position = vec4( position, 1.0 );
	vVector = vector;
	vColor = vec3( 0.0, 0.0, 1.0);
}
