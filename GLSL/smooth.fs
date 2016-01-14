#version 150
in vec3 vColor;
in vec3 vNormal;
out vec4 fragColor;

uniform vec3 lightPosition;
uniform vec3 eyePosition;

void main(void) {
	vec3 s = normalize( lightPosition - eyePosition );
	vec3 n = vNormal;
	vec3 color = vColor;
	vec3 diffuseColor = max(dot(s, n), 0.0) * vec3(0.0, 0.0, 1.0);
	vec3 ambientColor = vec3( 0.2, 0.2, 0.2);

    fragColor = vec4( color + diffuseColor + ambientColor, 1.0);
}