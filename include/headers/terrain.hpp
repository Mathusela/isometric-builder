#pragma once

#include "headers/tile.hpp"

class Grass : public Tile {
public:
	void place(glm::vec3 coords);

	Grass();
};

class Stone : public Tile {
public:
	void place(glm::vec3 coords);

	Stone();
};