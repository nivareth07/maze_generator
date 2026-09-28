#include "../include/maze_functions.h"
#include <random>

Maze::Cell::Cell() {
  visited = false;
  walls = TOP | RIGHT | BOTTOM | LEFT;
}

Maze::Maze_object::Maze_object(int grid_size, int X, int Y, int c_size) {
  grid.assign(grid_size, std::vector<Cell>(grid_size));
  m_grid_size = grid_size;
  starting_X = X;
  starting_Y = Y;
  Cell_size = c_size;
}

std::mt19937 &rng() {
  static std::mt19937 gen{std::random_device{}()};
  return gen;
}
uint8_t Maze::random_choice(uint8_t possible) {
  uint8_t options[4];
  int count = 0;
  for (Maze::Wall flag : {Maze::TOP, Maze::RIGHT, Maze::BOTTOM, Maze::LEFT}) {
    if (possible & flag)
      options[count++] = flag;
  }
  if (count == 0) {
    return 0;
  }
  std::uniform_int_distribution<int> distrib(0, count - 1);
  return options[distrib(rng())];
}
