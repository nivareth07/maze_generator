#include "../include/modes.h"

void Modes::one_step_carve(Maze::Maze_object &main_maze) {
  int &x = main_maze.current_cell.first;
  int &y = main_maze.current_cell.second;
  if (!main_maze.grid[x][y].visited) {
    main_maze.grid[x][y].visited = true;
    main_maze.visited_cells++;
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
    main_maze.path.pop();
    return;
  }
  if (chosen_side == Maze::TOP) {
    main_maze.grid[x][y].walls &= ~Maze::TOP;
    main_maze.grid[x][y - 1].walls &= ~Maze::BOTTOM;
    main_maze.path.push(std::pair<int, int>(x, y - 1));
  } else if (chosen_side == Maze::RIGHT) {
    main_maze.grid[x][y].walls &= ~Maze::RIGHT;
    main_maze.grid[x + 1][y].walls &= ~Maze::LEFT;
    main_maze.path.push(std::pair<int, int>(x + 1, y));
  } else if (chosen_side == Maze::BOTTOM) {
    main_maze.grid[x][y].walls &= ~Maze::BOTTOM;
    main_maze.grid[x][y + 1].walls &= ~Maze::TOP;
    main_maze.path.push(std::pair<int, int>(x, y + 1));
  } else if (chosen_side == Maze::LEFT) {
    main_maze.grid[x][y].walls &= ~Maze::LEFT;
    main_maze.grid[x - 1][y].walls &= ~Maze::RIGHT;
    main_maze.path.push(std::pair<int, int>(x - 1, y));
  }
}

void Modes::carving(Maze::Maze_object &main_maze) {
  int &visited_cells = main_maze.visited_cells;
  int &grid_size = main_maze.m_grid_size;

  if (visited_cells == grid_size * grid_size) {
    return;
  }
  if (visited_cells == 0) {
    main_maze.path.push({0, 0});
    main_maze.current_cell = std::pair<int, int>(0, 0);
    one_step_carve(main_maze);
    return;
  }
  if (main_maze.path.empty()) {
    return;
  }
  main_maze.current_cell = main_maze.path.top();
  one_step_carve(main_maze);
}
