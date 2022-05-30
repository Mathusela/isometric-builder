#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

const unsigned int WIDTH = 300, HEIGHT = 300;
const char* TITLE = "Isometric builder";

int main() {
	// Initialize GLFW and create a window
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	auto window = glfwCreateWindow(WIDTH, HEIGHT, TITLE, nullptr, nullptr);

	glfwMakeContextCurrent(window);

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