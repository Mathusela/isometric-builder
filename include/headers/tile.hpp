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
	bool m_interacted = false, m_wasInteracted = false;
	virtual void hover() {}; virtual void unhover() {}; virtual void onhover() {};
	virtual void interact() {}; virtual void uninteract() {}; virtual void oninteract() {};
	
	glm::vec3 m_hue = glm::vec3(0.0, 0.0, 0.0);

public:
	glm::vec3 get_coords();
	void set_coords(glm::vec3 coords);

	float get_depth();
	t_tile get_type();

	void set_hovered() {m_hovered = true;}
	void set_interacted() {m_interacted = true;}
	void update();
	virtual void place(glm::vec3 coords) = 0;
	virtual void build(std::vector<Tile*>& tiles, t_tile type);
	virtual void remove(std::vector<Tile*>& tiles, unsigned int index);

	glm::vec3 get_hue() {return m_hue;}
	void set_hue(glm::vec3 hue) {m_hue = hue;}

	Tile();
	
};