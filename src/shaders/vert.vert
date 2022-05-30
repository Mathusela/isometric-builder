#version 410 core

layout(location = 0) in vec3 position;
out float idIn;

void main() {
	gl_Position = vec4(position - vec3(gl_InstanceID*0.1, 0.0, 0.0), 1.0);
	idIn = gl_InstanceID;
}