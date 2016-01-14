#version 150
uniform sampler2D tex;
in vec4 vColor;
in vec2 vTexCoord;
out vec4 fragColor;
void main(void) {
	vec4 texel = texture(tex, vTexCoord);
	fragColor = texel * vColor;
}