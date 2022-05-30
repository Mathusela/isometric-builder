#include "headers/tile.hpp"

glm::vec3 Tile::get_coords() {
	return m_coords;
}

void Tile::set_coords(glm::vec3 coords) {
	m_coords = coords;
}

float Tile::get_depth() {
	return m_depth;
}

t_tile Tile::get_type() {
	return m_type;
}

Tile::Tile() {}