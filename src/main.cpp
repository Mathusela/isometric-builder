#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "headers/standard-functions.hpp"
#include "headers/isometric-builder.hpp"

#include "headers/tile.hpp"
#include "headers/terrain.hpp"

#include <vector>
#include <iostream>

const unsigned int WIDTH = 300, HEIGHT = 300;
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

// Draw tiles
void draw_tiles(t_shader shaderProgram, t_buffer VAO) {
	glUseProgram(shaderProgram);
	glBindVertexArray(VAO);
	glDrawArraysInstanced(GL_TRIANGLES, 0, sizeof(tileGeom)/sizeof(tileGeom[0]), 100);
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

	Grass* g1 = new Grass; g1->place(glm::vec3(0.0, 0.0, 0.0)); g_tiles.push_back(g1);
	Grass* g2 = new Grass; g2->place(glm::vec3(1.0, 0.0, 0.0)); g_tiles.push_back(g2);
	Grass* g3 = new Grass; g3->place(glm::vec3(2.0, 0.0, 0.0)); g_tiles.push_back(g3);
	Grass* g4 = new Grass; g4->place(glm::vec3(3.0, 0.0, 0.0)); g_tiles.push_back(g4);

	t_shader shaderProgram = create_shader("../../src/shaders/vert.vert", "../../src/shaders/frag.frag");

	t_buffer VAO;
	gen_tile_geom_VAO(VAO);

	// Game loop
	glClearColor(1.0, 1.0, 1.0, 1.0);
	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT);

		draw_tiles(shaderProgram, VAO);

		glfwPollEvents();
		glfwSwapBuffers(window);
	}
	
	delete g1;
	delete g2;
	delete g3;
	delete g4;

	return 0;
}