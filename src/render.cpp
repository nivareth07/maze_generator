#include "../include/maze_functions.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_render.h>

void render_cells(const Maze::Maze_object &main_maze,
                  SDL_Renderer *main_renderer) {
  for (int i = 0; i < main_maze.grid.size(); i++) {
    for (int j = 0; j < main_maze.grid[i].size(); j++) {
      int Cell_size = main_maze.Cell_size;
      int x0 = main_maze.starting_X + (Cell_size * i);
      int y0 = main_maze.starting_Y + (Cell_size * j);
      if (main_maze.grid[i][j].walls & Maze::LEFT) {
        SDL_RenderLine(main_renderer, x0, y0, x0, y0 + Cell_size);
      }
      if (main_maze.grid[i][j].walls & Maze::TOP) {
        SDL_RenderLine(main_renderer, x0, y0, x0 + Cell_size, y0);
      }
      if (main_maze.grid[i][j].walls & Maze::RIGHT) {
        SDL_RenderLine(main_renderer, x0 + Cell_size, y0, x0 + Cell_size,
                       y0 + Cell_size);
      }
      if (main_maze.grid[i][j].walls & Maze::BOTTOM) {
        SDL_RenderLine(main_renderer, x0 + Cell_size, y0 + Cell_size, x0,
                       y0 + Cell_size);
      }
    }
  }
}
