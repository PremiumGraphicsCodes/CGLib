#version 150
in vec4 vColor;
out vec4 fragColor;
void main(void) {
    vec2 coord = gl_PointCoord * 2.0 - 1.0;
    float distSquared = 1.0 -dot(coord, coord);
    if( distSquared < 0.0 ) {
        discard;
    }
	fragColor.rgba = vColor;
    fragColor.a = sqrt(distSquared) * vColor.a;
}