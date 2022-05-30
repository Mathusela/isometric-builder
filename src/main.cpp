#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "headers/standard-functions.hpp"

#include <iostream>

const unsigned int WIDTH = 300, HEIGHT = 300;
char* TITLE = "Isometric builder";

int main() {
	// Initialize GLFW and create a window
	glfwInit();
	auto window = create_window(WIDTH, HEIGHT, TITLE, 0);

	// Bind OpenGL addresses
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	// Set OpenGL viewport size
	glViewport(0, 0, WIDTH, HEIGHT);

	// Game loop
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	return 0;
}