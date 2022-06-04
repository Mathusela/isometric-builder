#include "headers/tile.hpp"
#include "headers/terrain.hpp"
#include <iostream>

Tile* factory(t_tile type) {
	switch (type) {
		case GRASS:
			return new Grass;
		case STONE:
			return new Stone;
		default:
			return new Grass;
	}
}


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

void Tile::build(std::vector<Tile*>& tiles, t_tile type) {
	auto newCoords = get_coords() + glm::vec3(0.0, 0.0, 1.0);
	bool placeable = true;
	for (auto tile : tiles) if (tile->get_coords() == newCoords) placeable = false;
	if (!placeable) return;
	auto t = factory(type);
	t->place(newCoords);
	tiles.push_back(t);
	g_countMap[type] += 1;
}

void Tile::remove(std::vector<Tile*>& tiles, unsigned int index) {
	auto ptr = tiles[index];
	tiles.erase(tiles.begin() + index);
	g_countMap[get_type()]--;
	delete ptr;
}

Tile::Tile() {}