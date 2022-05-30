#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "headers/standard-functions.hpp"
#include "headers/isometric-builder.hpp"

#include "headers/tile.hpp"
#include "headers/terrain.hpp"

#include <vector>
#include <iostream>

const unsigned int WIDTH = 800, HEIGHT = 600;
char* TITLE = "Isometric builder";

float tileGeom[] = {
	0.0, 0.0, 0.0,
	0.0, 1.0, 0.0,
	1.0, 0.0, 0.0,

	0.0, 1.0, 0.0,
	1.0, 0.0, 0.0,
	1.0, 1.0, 0.0
};

// Vector of tiles to be drawn
std::vector<Tile*> g_tiles;

// Map of textures
std::unordered_map<t_tile, t_texture> g_textureMap;

// Sort tiles into materials
auto quick_sort_tiles(std::vector<Tile*> unsorted) {
	if (unsorted.size() <= 1) return unsorted;
	
	auto midpoint = unsorted[0]->get_type();

	std::vector<Tile*> lowerList; std::vector<Tile*> equalList; std::vector<Tile*> higherList;

	for (auto element : unsorted) {
		if (element->get_type() < midpoint) lowerList.push_back(element);
		else if (element->get_type() == midpoint) equalList.push_back(element);
		else higherList.push_back(element);
	}

	auto sortedLower = quick_sort_tiles(lowerList);
	auto sortedHigher = quick_sort_tiles(higherList);

	auto combinedList = sortedLower; 
	combinedList.insert(combinedList.end(), equalList.begin(), equalList.end()); 
	combinedList.insert(combinedList.end(), sortedHigher.begin(), sortedHigher.end());

	return combinedList;
}

// Draw tiles
void draw_tiles(t_shader shaderProgram, t_buffer VAO) {
	glUseProgram(shaderProgram);
	glBindVertexArray(VAO);
	
	glUniform2fv(glGetUniformLocation(shaderProgram, "resolution"), 1, glm::value_ptr(glm::vec2(WIDTH, HEIGHT)));
	
	glUniform1i(glGetUniformLocation(shaderProgram, "texture"), 0);
	glActiveTexture(GL_TEXTURE0); glBindTexture(GL_TEXTURE_2D, g_textureMap[g_tiles[0]->get_type()]);

	glDrawArraysInstanced(GL_TRIANGLES, 0, sizeof(tileGeom)/sizeof(tileGeom[0]), g_tiles.size());
	glBindVertexArray(0);
}

// Create tile VAO
void gen_tile_geom_VAO(t_buffer& VAO) {
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	t_buffer VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(tileGeom), tileGeom, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(tileGeom[0])*3, (void*)0);
	glEnableVertexAttribArray(0);

	std::vector<float> positionData;
	for (Tile* tile : g_tiles) {
		positionData.push_back(tile->get_coords().x);
		positionData.push_back(tile->get_coords().y);
		positionData.push_back(tile->get_coords().z);
		positionData.push_back(tile->get_depth());
	}
	
	t_buffer cVBO;
	glGenBuffers(1, &cVBO);
	glBindBuffer(GL_ARRAY_BUFFER, cVBO);
	glBufferData(GL_ARRAY_BUFFER, positionData.size() * sizeof(positionData[0]), &positionData[0], GL_STATIC_DRAW);

	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(positionData[0])*4, (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribDivisor(1, 1);

	glBindVertexArray(0);
}

int main() {
	// Initialize GLFW and create a window
	glfwInit();
	auto window = create_window(WIDTH, HEIGHT, TITLE, 0);

	// Bind OpenGL addresses
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	// Set OpenGL viewport size
	glViewport(0, 0, WIDTH, HEIGHT);

	// Create textures
	g_textureMap.insert({GRASS, create_texture("../../resources/textures/grass.png")});
	g_textureMap.insert({STONE, create_texture("../../resources/textures/stone.png")});

	// Add tiles
	for (int i=0; i<10; i++) {
		for (int j=0; j<10; j++) {
			Stone* g = new Stone;
			g->place(glm::vec3(i, j, 0.0));
			g_tiles.push_back(g);
		}
	}

	Stone* g1 = new Stone;
	g1->place(glm::vec3(2.0, 2.0, 1.0));
	g_tiles.push_back(g1);

	Stone* g2 = new Stone;
	g2->place(glm::vec3(2.0, 2.0, 2.0));
	g_tiles.push_back(g2);

	Stone* g3 = new Stone;
	g3->place(glm::vec3(3.0, 2.0, 2.0));
	g_tiles.push_back(g3);

	g_tiles = quick_sort_tiles(g_tiles);

	// Compile shaders
	t_shader shaderProgram = create_shader("../../src/shaders/vert.vert", "../../src/shaders/frag.frag");

	// Generate VAO
	t_buffer VAO;
	gen_tile_geom_VAO(VAO);

	// Game loop
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		draw_tiles(shaderProgram, VAO);

		glfwPollEvents();
		glfwSwapBuffers(window);
	}
	
	for (auto tile : g_tiles) delete tile;

	return 0;
}