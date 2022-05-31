#include "headers/terrain.hpp"
#include <iostream>

float calcDepth(glm::vec3 coords) {
	// Distance from some point above the origin to the tile, affects maximum height 
	coords -= glm::vec3(0.0, 0.0, 100.0);
	float len = sqrt(coords.x*coords.x + coords.y*coords.y + coords.z*coords.z);
	// Must be bound between 0.0 and 1.0, effects maximum distance/depth
	return len / 1000000.0;
}

void hover_hue(Tile* t, bool on) {
	if (on) t->set_hue(glm::vec3(0.2, 0.2, 1.0));
	else t->set_hue(glm::vec3(0.0, 0.0, 0.0));
}

void interact_hue(Tile* t, bool on) {
	if (on) t->set_hue(glm::vec3(1.0, 0.2, 1.0));
	else t->set_hue(glm::vec3(0.0, 0.0, 0.0));
}



void Grass::place(glm::vec3 coords) {
	set_coords(coords);
	m_depth = calcDepth(coords);
}

Grass::Grass() {
	m_type = GRASS;
}

void Grass::hover() {
	hover_hue(this, true);
}

void Grass::unhover() {
	hover_hue(this, false);
}

void Grass::interact() {
	interact_hue(this, true);
}

void Grass::uninteract() {
	interact_hue(this, false);
}



void Stone::place(glm::vec3 coords) {
	set_coords(coords);
	m_depth = calcDepth(coords);
}

Stone::Stone() {
	m_type = STONE;
}

void Stone::hover() {
	hover_hue(this, true);
}

void Stone::unhover() {
	hover_hue(this, false);
}

void Stone::interact() {
	interact_hue(this, true);
}

void Stone::uninteract() {
	interact_hue(this, false);
}