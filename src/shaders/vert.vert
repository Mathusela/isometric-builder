#version 410 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 coordIn;
layout(location = 2) in vec3 hueIn;

out vec2 uv;
out vec3 hue;

uniform vec2 resolution;

float numInRow = 10.0;

void main() {
	numInRow /= 2;

	vec2 scaled = (position.xy / resolution) * (resolution.x / numInRow);
	scaled -= vec2(0.5*(1/numInRow), 1.0);

	mat3 iso = mat3(
		(1.0/numInRow)/2.0, (1.0/numInRow)*0.35, 0.0,
		-(1.0/numInRow)/2.0, 0.35/(numInRow), 0.0,
		0.0, 0.64/(numInRow), 1.0
	);

	vec2 offset = (vec3(scaled, 0.0) + (iso * coordIn.xyz)).xy; 

	gl_Position =  vec4(offset, coordIn.w, 1.0);

	uv = position.xy;
	hue = hueIn;
}