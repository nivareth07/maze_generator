#include "../include/maze_functions.h"
#include "../include/render.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_timer.h>
#include <SDL3/SDL_video.h>
#include <cstddef>
#include <stack>
#include <stdexcept>

static SDL_Window *main_window;
static SDL_Renderer *main_renderer;
static bool running = true;
std::stack<std::pair<int, int>> path;
Maze::Maze_object main_maze(8, 200, 200, 30);
int cells_visited = 0;

enum class Mode { Crafting, Solving };

void update();
void input() {
  SDL_Event input_events;
  while (SDL_PollEvent(&input_events)) {
    switch (input_events.type) {
    case SDL_EVENT_QUIT: {
      running = false;
      break;
    }
    case SDL_EVENT_KEY_DOWN: {
      if (input_events.key.key == SDLK_C) {
        update();
      } else if (input_events.key.key == SDLK_Q) {
        running = false;
      }
      break;
    }
    default: {
      break;
    }
    }
  }
}

void one_step_carve(int x, int y) {
  if (!main_maze.grid[x][y].visited) {
    main_maze.grid[x][y].visited = true;
    cells_visited++;
  }
  uint8_t possible_choices = 0;
  if (y != 0 && main_maze.grid[x][y - 1].visited == false) {
    possible_choices |= Maze::TOP;
  }
  if (x != (main_maze.m_grid_size - 1) &&
      main_maze.grid[x + 1][y].visited == false) {
    possible_choices |= Maze::RIGHT;
  }
  if (y != (main_maze.m_grid_size - 1) &&
      main_maze.grid[x][y + 1].visited == false) {
    possible_choices |= Maze::BOTTOM;
  }
  if (x != 0 && main_maze.grid[x - 1][y].visited == false) {
    possible_choices |= Maze::LEFT;
  }
  uint8_t chosen_side = Maze::random_choice(possible_choices);
  if (chosen_side == 0) {
    path.pop();
    return;
  }
  if (chosen_side == Maze::TOP) {
    main_maze.grid[x][y].walls &= ~Maze::TOP;
    main_maze.grid[x][y - 1].walls &= ~Maze::BOTTOM;
    path.push(std::pair<int, int>(x, y - 1));
  } else if (chosen_side == Maze::RIGHT) {
    main_maze.grid[x][y].walls &= ~Maze::RIGHT;
    main_maze.grid[x + 1][y].walls &= ~Maze::LEFT;
    path.push(std::pair<int, int>(x + 1, y));
  } else if (chosen_side == Maze::BOTTOM) {
    main_maze.grid[x][y].walls &= ~Maze::BOTTOM;
    main_maze.grid[x][y + 1].walls &= ~Maze::TOP;
    path.push(std::pair<int, int>(x, y + 1));
  } else if (chosen_side == Maze::LEFT) {
    main_maze.grid[x][y].walls &= ~Maze::LEFT;
    main_maze.grid[x - 1][y].walls &= ~Maze::RIGHT;
    path.push(std::pair<int, int>(x - 1, y));
  }
}
void update() {
  if (cells_visited == main_maze.m_grid_size * main_maze.m_grid_size) {
    return;
  }
  if (cells_visited == 0) {
    path.push({0, 0});
    one_step_carve(0, 0);
    return;
  }
  if (path.empty()) {
    return;
  }
  std::pair<int, int> current_cell = path.top();
  one_step_carve(current_cell.first, current_cell.second);
}
void render() {
  SDL_SetRenderDrawColor(main_renderer, 0, 0, 0, 0);
  SDL_RenderClear(main_renderer);

  SDL_SetRenderDrawColor(main_renderer, 255, 255, 0, 0);
  render_cells(main_maze, main_renderer);

  SDL_RenderPresent(main_renderer);
}

int main() {
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    throw std::runtime_error("submodules initilization failed");
  }
  main_window = SDL_CreateWindow("maze", 800, 600, SDL_WINDOW_RESIZABLE);
  if (main_window == NULL) {
    throw std::runtime_error("failed to create window");
  }
  main_renderer = SDL_CreateRenderer(main_window, NULL);
  if (main_renderer == NULL) {
    throw std::runtime_error("failed to create renderer");
  }
  while (running) {
    input();
    render();
  }

  SDL_DestroyWindow(main_window);
  SDL_DestroyRenderer(main_renderer);
  SDL_Quit();
  return 0;
}
