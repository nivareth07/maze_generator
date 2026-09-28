#ifndef MAZE_FUNCTIONS_H
#define MAZE_FUNCTIONS_H

#include <cstdint>
#include <ratio>
#include <vector>

namespace Maze {

enum Wall : uint8_t { TOP = 1, RIGHT = 2, BOTTOM = 4, LEFT = 8 };

struct Cell {
  uint8_t walls;
  bool visited;

  // constructor
  Cell();
};

// a wrapper for anything that concerns a single maze
class Maze_object {
private:
public:
  std::vector<std::vector<Cell>> grid;
  int starting_X;
  int starting_Y;
  int m_grid_size;
  int Cell_size;

  Maze_object(int grid_size, int X, int Y, int c_size);
};

uint8_t random_choice(uint8_t possible);

} // namespace Maze

#endif
