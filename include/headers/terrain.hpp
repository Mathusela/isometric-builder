#pragma once

#include "headers/tile.hpp"

class Grass : public Tile {
protected:
	void hover();
	void unhover();
	
public:
	void place(glm::vec3 coords);

	Grass();
};

class Stone : public Tile {
protected:
	void hover();
	void unhover();

public:
	void place(glm::vec3 coords);

	Stone();
};