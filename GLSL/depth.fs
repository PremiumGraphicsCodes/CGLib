#version 150
//in float depth;
out vec4 fragColor;

void main() {
	fragColor.rgb = vec3(gl_FragCoord.z);
	fragColor.a = 1.0;
}