#version 410 core

uniform sampler2D texture;

in vec2 uv;

void main() {
	vec4 col = texture2D(texture, uv);
	gl_FragColor = col;

	if (col.a == 0) discard;
}