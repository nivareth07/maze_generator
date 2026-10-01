#include "../include/maze_functions.h"
#include "../include/modes.h"
#include "../include/render.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_timer.h>
#include <SDL3/SDL_video.h>
#include <cstddef>
#include <stdexcept>

static SDL_Window *main_window;
static SDL_Renderer *main_renderer;
static bool running = true;

Maze::Maze_object main_maze(8, 200, 200, 30);

enum class Mode { Carving, Solving };

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

void update() { Modes::carving(main_maze); }
void render() {
  SDL_SetRenderDrawColor(main_renderer, 0, 0, 0, 0);
  SDL_RenderClear(main_renderer);

  SDL_SetRenderDrawColor(main_renderer, 255, 255, 0, 0);
  render_cells(main_maze, main_renderer);
  if (!main_maze.path.empty() &&
      main_maze.visited_cells !=
          (main_maze.m_grid_size * main_maze.m_grid_size)) {
    render_carving_index(main_maze, main_maze.current_cell, main_renderer);
  }

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
