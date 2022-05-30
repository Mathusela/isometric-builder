#pragma once

#include <string>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

GLFWwindow* create_window(unsigned int width, unsigned int height, char* title, unsigned int MSAA);

unsigned int create_texture(std::string imagePath);

unsigned int create_framebuffer(std::vector<unsigned int*> texturesOut, unsigned int width, unsigned int height);

std::string import_shader_source(std::string inputPath);

unsigned int create_shader(std::string vertexShaderPath, std::string fragmentShaderPath);