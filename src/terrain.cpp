#include "headers/terrain.hpp"
#include <iostream>

void Grass::place(glm::vec3 coords) {
	set_coords(coords);
	m_depth = coords.z / 100.0;
}

Grass::Grass() {
	m_type = GRASS;
}

void Stone::place(glm::vec3 coords) {
	set_coords(coords);
	m_depth = coords.z / 100.0;
}

Stone::Stone() {
	m_type = STONE;
}