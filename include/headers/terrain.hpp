#pragma once

#include "headers/tile.hpp"

class Grass : public Tile {
public:
	void place(glm::vec3 coords);

	Grass();
};