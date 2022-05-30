#include "headers/terrain.hpp"
#include <iostream>

float calcDepth(glm::vec3 coords) {
	// Distance from some point above the origin to the tile, affects maximum height 
	coords -= glm::vec3(0.0, 0.0, 100.0);
	float len = sqrt(coords.x*coords.x + coords.y*coords.y + coords.z*coords.z);
	// Must be bound between 0.0 and 1.0, effects maximum distance/depth
	return len / 1000000.0;
}

void Grass::place(glm::vec3 coords) {
	set_coords(coords);
	m_depth = calcDepth(coords);
}

Grass::Grass() {
	m_type = GRASS;
}

void Grass::hover() {
	set_hue(glm::vec3(0.2, 0.2, 1.0));
}

void Grass::unhover() {
	set_hue(glm::vec3(0.0, 0.0, 0.0));
}

void Stone::place(glm::vec3 coords) {
	set_coords(coords);
	m_depth = calcDepth(coords);
}

Stone::Stone() {
	m_type = STONE;
}

void Stone::hover() {
	set_hue(glm::vec3(0.2, 0.2, 1.0));
}

void Stone::unhover() {
	set_hue(glm::vec3(0.0, 0.0, 0.0));
}