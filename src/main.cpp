#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cinttypes>
#include <cassert>

#include "nonogram_problem.hpp"
#include "nonogram_bitmap.hpp"

static std::vector<int> read_blocks_line() {
  std::string line;
  std::getline(std::cin, line);
  std::vector<int> blocks;
  int cnt = 0;
  auto is = std::istringstream(line);

  while (true)
  {
    is >> cnt;
    if (is.fail())
      break;
    blocks.push_back(cnt);
  }
  return blocks;
}

int main() {
  auto szline = read_blocks_line();
  if (szline.size() != 2) {
    std::cerr << "invalid input format. first line should contain [width] [height]" << std::endl;
    return -1;
  }

  int board_w = szline[0];
  int board_h = szline[1];

  std::vector<std::vector<int>> h_blocks;
  std::vector<std::vector<int>> v_blocks;

  for (int y = 0; y < board_h; y++) {
    auto blocks = read_blocks_line();
    h_blocks.push_back(blocks);
  } 

  for (int x = 0; x < board_w; x++) {
    auto blocks = read_blocks_line();
    v_blocks.push_back(blocks);
  } 

  NonogramProblem p(h_blocks, v_blocks);
  NonogramBitmap b(p.width(), p.height());
  p.dump();

  if (p.solve(b)) {
    b.dump();
    return 0;
  }

  std::cout << "failed to solve";
  return 1;
}
