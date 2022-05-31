#include "headers/tile.hpp"
#include <iostream>

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

void Tile::update() {
	if (m_hovered) {
		if (!m_wasHovered) onhover();
		hover();
	}
	else if (m_wasHovered) unhover();
	m_wasHovered = m_hovered;
	m_hovered = false;

	if (m_interacted) {
		if (!m_wasInteracted) oninteract();
		interact();
	}
	else if (m_wasInteracted) uninteract();
	m_wasInteracted = m_interacted;
	m_interacted = false;
}

Tile::Tile() {}