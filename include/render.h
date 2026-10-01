#ifndef RENDER_H
#define RENDER_H

#include "../include/maze_functions.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_render.h>

void render_cells(const Maze::Maze_object &, SDL_Renderer *);
void render_carving_index(const Maze::Maze_object &, std::pair<int, int>,
                          SDL_Renderer *main_renderer);

#endif
