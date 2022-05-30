#version 410 core

in float idIn;

void main() {
	gl_FragColor = vec4(1.0 * (idIn * 0.1), 0.0, 0.0, 1.0);
}