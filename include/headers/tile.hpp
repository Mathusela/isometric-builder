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
	bool m_hovered = false, m_wasHovered = false;
	virtual void hover() {};
	virtual void unhover() {};
	glm::vec3 m_hue = glm::vec3(0.0, 0.0, 0.0);

public:
	glm::vec3 get_coords();
	void set_coords(glm::vec3 coords);

	float get_depth();
	t_tile get_type();

	void set_hovered() {m_hovered = true;}
	void update();
	virtual void interact() {};
	virtual void place(glm::vec3 coords) = 0;

	glm::vec3 get_hue() {return m_hue;}
	void set_hue(glm::vec3 hue) {m_hue = hue;}

	Tile();
	
};