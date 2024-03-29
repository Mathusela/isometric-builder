#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "headers/standard-functions.hpp"
#include "headers/isometric-builder.hpp"

#include "headers/tile.hpp"
#include "headers/terrain.hpp"

#include <vector>
#include <iostream>

const unsigned int WIDTH = 1200, HEIGHT = 800;
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

// Map of num of each tile type
std::unordered_map<t_tile, int> g_countMap;

// Number of tiles in row
float g_numInRow = 10.0;

// Displacement in world
glm::vec2 g_worldPos = glm::vec2(0.0, 0.0);

// Draw tiles
void draw_tiles(t_shader shaderProgram, t_buffer VAO, t_tile type) {
	glUseProgram(shaderProgram);
	glBindVertexArray(VAO);
	
	glUniform2fv(glGetUniformLocation(shaderProgram, "resolution"), 1, glm::value_ptr(glm::vec2(WIDTH, HEIGHT)));
	
	glUniform1i(glGetUniformLocation(shaderProgram, "texture"), 0);
	glActiveTexture(GL_TEXTURE0); glBindTexture(GL_TEXTURE_2D, g_textureMap[type]);

	glUniform1f(glGetUniformLocation(shaderProgram, "numInRowUni"), g_numInRow);

	glUniform2fv(glGetUniformLocation(shaderProgram, "worldPos"), 1, glm::value_ptr(g_worldPos));

	glDrawArraysInstanced(GL_TRIANGLES, 0, sizeof(tileGeom)/sizeof(tileGeom[0]), g_countMap[type]);
	glBindVertexArray(0);
}

// Update Coord VBO
void update_coord_VBO(t_buffer& cVBO, t_tile type) {
	std::vector<float> positionData;
	for (Tile* tile : g_tiles) {
		if (tile->get_type() == type) {
			positionData.push_back(tile->get_coords().x);
			positionData.push_back(tile->get_coords().y);
			positionData.push_back(tile->get_coords().z);
			positionData.push_back(tile->get_depth());
			positionData.push_back(tile->get_hue().x);
			positionData.push_back(tile->get_hue().y);
			positionData.push_back(tile->get_hue().z);
		}
	}
	if (positionData.size() == 0) return;
	
	glBindBuffer(GL_ARRAY_BUFFER, cVBO);
	glBufferData(GL_ARRAY_BUFFER, positionData.size() * sizeof(positionData[0]), &positionData[0], GL_DYNAMIC_DRAW);
}

// Create tile VAO
void gen_tile_VAO(t_buffer& VAO, t_buffer& cVBO, t_tile type) {
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
		if (tile->get_type() == type) {
			positionData.push_back(tile->get_coords().x);
			positionData.push_back(tile->get_coords().y);
			positionData.push_back(tile->get_coords().z);
			positionData.push_back(tile->get_depth());
			positionData.push_back(tile->get_hue().x);
			positionData.push_back(tile->get_hue().y);
			positionData.push_back(tile->get_hue().z);
		}
	}
	if (positionData.size() == 0) return;
	
	glGenBuffers(1, &cVBO);
	glBindBuffer(GL_ARRAY_BUFFER, cVBO);
	glBufferData(GL_ARRAY_BUFFER, positionData.size() * sizeof(positionData[0]), &positionData[0], GL_DYNAMIC_DRAW);

	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(positionData[0])*7, (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribDivisor(1, 1);

	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(positionData[0])*7, (void*)(4 * sizeof(positionData[0])));
	glEnableVertexAttribArray(2);
	glVertexAttribDivisor(2, 1);

	glBindVertexArray(0);
}

// Handle input
void handle_keyboard(GLFWwindow* window, float deltaTime) {
	float zoomSpeed = 3.5 * deltaTime;
	float moveSpeed = 3.5 * deltaTime;

	if(glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) if (g_numInRow <= 20.0) g_numInRow += zoomSpeed;
	if(glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) if (g_numInRow >= 3.0) g_numInRow -= zoomSpeed;
	
	if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) g_worldPos -= glm::vec2(0.0, moveSpeed);
	if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) g_worldPos += glm::vec2(0.0, moveSpeed);
	if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) g_worldPos += glm::vec2(moveSpeed, 0.0);
	if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) g_worldPos -= glm::vec2(moveSpeed, 0.0);
} 

int prevMouseState = GLFW_RELEASE;
void handle_mouse(GLFWwindow* window, int WIDTH, int HEIGHT) {
	float numInRow = g_numInRow;
	numInRow = numInRow/2.0f;
	double x, y;
	glfwGetCursorPos(window, &x, &y);
	x /= WIDTH/2; x += -1.0; y /= HEIGHT/2; y = 1.0 - y;

	// TODO: If I can do the inverse of this to the mouse position I can use hash mapping to speed this up and directly access the hovered tiles
	glm::mat3 iso = {glm::vec3 {(1.0/numInRow)/2.1, (1.0/numInRow)*0.36, 0.0},
					 glm::vec3 {-(1.0/numInRow)/2.1, 0.36/(numInRow), 0.0},
					 glm::vec3 {0.0, 0.69/(numInRow), 1.0}};

	auto scaledBL = ((glm::vec2(0, 0) + g_worldPos) / glm::vec2(WIDTH, HEIGHT))*(WIDTH/numInRow) - glm::vec2(0.5 * (1.0/numInRow), 1.0);
	auto scaledTR = ((glm::vec2(1, 1) + g_worldPos) / glm::vec2(WIDTH, HEIGHT))*(WIDTH/numInRow) - glm::vec2(0.5 * (1.0/numInRow), 1.0);

	std::vector<Tile*> hoveredTiles;
	std::vector<unsigned int> indexArr;
	unsigned int count = 0;
	for (auto tile : g_tiles) {
		glm::vec3 isoBL = glm::vec3(scaledBL.x, scaledBL.y, 0.0) + (iso * tile->get_coords());
		glm::vec3 isoTR = glm::vec3(scaledTR.x, scaledTR.y, 0.0) + (iso * tile->get_coords());

		if (x >= isoBL.x && x <= isoTR.x && y >= isoBL.y && y <= isoTR.y) {hoveredTiles.push_back(tile); indexArr.push_back(count);}
		count++;
	}

	// FIXME: Tiles under other tiles are covered up by the corners of other tiles
	if (hoveredTiles.size() != 0) {
		auto minDepth = hoveredTiles[0]->get_depth();
		unsigned int closestIndex;
		Tile* closestTile;
		
		unsigned int count = 0;
		for (auto hovered : hoveredTiles) {
			if (hovered->get_depth() <= minDepth) {
				closestTile = hovered;
				closestIndex = count;
				minDepth = hovered->get_depth();
			}
			count++;
		}
		closestIndex = indexArr[closestIndex];

		closestTile->set_hovered();
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS) {
			closestTile->set_interacted();
			if (prevMouseState == GLFW_RELEASE && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) closestTile->remove(g_tiles, closestIndex);
			else if (prevMouseState == GLFW_RELEASE) closestTile->build(g_tiles, closestTile->get_type());
		}
	}

	for (auto tile : g_tiles) tile->update();
	prevMouseState = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1);
}

void handle_input(GLFWwindow* window, int WIDTH, int HEIGHT, float deltaTime) {
	handle_keyboard(window, deltaTime);
	handle_mouse(window, WIDTH, HEIGHT);
}

// Count the number of each tile type
void gen_count_map() {
	for (int i=GRASS; i<TILE_END; i++) {
		int count = 0;
		for (auto tile : g_tiles) if (tile->get_type() == i) count++;
		g_countMap.insert({(t_tile)i, count});
	}
}

float prevTime = 0;

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
	for (int i=0; i<30; i++) {
		for (int j=0; j<30; j++) {
			Stone* g = new Stone;
			g->place(glm::vec3(i, j, 0.0));
			g_tiles.push_back(g);
		}
	}

	for (int i=0; i<30; i++) {
		for (int j=0; j<30; j++) {
			Grass* g = new Grass;
			g->place(glm::vec3(i, j, 1.0));
			g_tiles.push_back(g);
		}
	}

	for (int i=2; i<5; i++) {
		Stone* g = new Stone;
		g->place(glm::vec3(0.0, 0.0, i));
		g_tiles.push_back(g);
	}

	// Compile shaders
	t_shader shaderProgram = create_shader("../../src/shaders/vert.vert", "../../src/shaders/frag.frag");

	// Generate count map
	gen_count_map();

	// Generate VAO
	std::vector<t_buffer> VAOs;
	std::vector<t_buffer> VBOs;
	for (int i=GRASS; i<TILE_END; i++) {
		t_buffer VAO, VBO;
		gen_tile_VAO(VAO, VBO, (t_tile)i);
		VAOs.push_back(VAO); VBOs.push_back(VBO);
	}

	glfwSwapInterval(0);

	// Game loop
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	while (!glfwWindowShouldClose(window)) {
		// Delta time
		float deltaTime = glfwGetTime() - prevTime;
		prevTime = glfwGetTime();

		// Clear
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		// Draw
		for (int i=GRASS; i<TILE_END; i++) draw_tiles(shaderProgram, VAOs[i], (t_tile)i);

		// Input and update positions
		handle_input(window, WIDTH, HEIGHT, deltaTime);
		for (int i=GRASS; i<TILE_END; i++) update_coord_VBO(VBOs[i], (t_tile)i);

		// Poll events and refresh display
		glfwPollEvents();
		glfwSwapBuffers(window);
	}
	
	// Clean up
	for (auto tile : g_tiles) delete tile;

	return 0;
}