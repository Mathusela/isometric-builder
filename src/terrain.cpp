#include "headers/terrain.hpp"
#include <iostream>

void Grass::place(glm::vec3 coords) {
	set_coords(coords);
}

Grass::Grass() {
	m_type = GRASS;
}