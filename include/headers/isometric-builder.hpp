#pragma once

#include <unordered_map>
#include <vector>

enum t_tile {GRASS, STONE, TILE_END};
using t_texture = unsigned int;
using t_shader = unsigned int;
using t_buffer = unsigned int;

extern std::unordered_map<t_tile, t_texture> g_textureMap;
extern std::unordered_map<t_tile, int> g_countMap;