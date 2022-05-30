#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "headers/isometric-builder.hpp"

class Tile {
protected:
	glm::vec3 m_coords;
	t_tile m_type;
	float m_depth;

public:
	glm::vec3 get_coords();
	void set_coords(glm::vec3 coords);

	float get_depth();
	t_tile get_type();

	virtual void interact() {};
	virtual void place(glm::vec3 coords) = 0;

	Tile();
	
};