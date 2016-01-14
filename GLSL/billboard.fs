#version 150
in float vDensity;
uniform sampler2D tex;
out vec4 fragColor;

in float gDensity;
in vec2 gTexCoord;

void main(void) {
    vec2 texCoord = gTexCoord;
	vec4 texel = texture(tex, texCoord);
	fragColor = texel;
	fragColor.a *= gDensity;
}