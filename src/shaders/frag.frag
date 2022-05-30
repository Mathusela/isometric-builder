#version 410 core

uniform sampler2D texture;

in vec2 uv;
in vec3 hue;

void main() {
	vec4 col = texture2D(texture, uv);
	col += int(col != vec4(0.0, 0.0, 0.0, 1.0)) * vec4(hue, 0.0) + int(col == vec4(0.0, 0.0, 0.0, 1.0)) * vec4(0.0, 0.0, 0.0, 1.0);
	gl_FragColor = col;

	if (col.a == 0) discard;
}