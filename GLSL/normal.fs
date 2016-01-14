#version 150
in vec3 gColor;
out vec4 fragColor;
void main(void) {
	fragColor.rgb = gColor;
	fragColor.a = 1.0;
}