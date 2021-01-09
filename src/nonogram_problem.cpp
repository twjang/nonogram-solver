#include "nonogram_problem.hpp"
#include "line_solver.hpp"

int NonogramProblem::update_h_block(int y, NonogramBitmap& b) {
  std::vector<PixelStatus> line(b.width());
  std::vector<PixelStatus> new_line(b.width());

  for (int x=0; x<b.width(); x++) {
    line[x] = b.at(x, y);
  }

  LineSolver s(h_blocks[y], line);

  int updated = s.update_state(new_line);
  if (updated > 0) {
    for (int x=0; x<b.width(); x++) {
      b.at(x, y) = new_line[x];
    }
  }

  return updated;
}

int NonogramProblem::update_v_block(int x, NonogramBitmap& b) {
  std::vector<PixelStatus> line(b.height());
  std::vector<PixelStatus> new_line(b.height());

  for (int y=0; y<b.height(); y++) {
    line[y] = b.at(x, y);
  }

  LineSolver s(v_blocks[x], line);

  int updated = s.update_state(new_line);
  if (updated > 0) {
    for (int y=0; y<b.height(); y++) {
      b.at(x, y) = new_line[y];
    }
  }
  return updated;
}


bool NonogramProblem::solve(NonogramBitmap& b) {
  int update_cnt;
  do {
    update_cnt = 0;
    for (int x=0; x<b.width(); x++) {
      int res = update_v_block(x, b);
      if (res < 0) return false;
      update_cnt += res;
    }
    for (int y=0; y<b.height(); y++) {
      int res = update_h_block(y, b);
      if (res < 0) return false;
      update_cnt += res;
    }
  } while(update_cnt > 0);

  auto unknown_coord = b.find_unknown();
  if (unknown_coord.first == -1 && unknown_coord.second == -1)
    return true;
  
  NonogramBitmap clone(b);
  clone.at(unknown_coord.first, unknown_coord.second) = Filled;
  if (solve(clone)) {
    b.copy_from(clone);
    return true;
  }

  clone.copy_from(b);
  clone.at(unknown_coord.first, unknown_coord.second) = Unfilled;
  if (solve(clone)) {
    b.copy_from(clone);
    return true;
  }

  return false;
}

void NonogramProblem::dump() {
  std::cout << "[ vertical blocks ]" << std::endl;
  for (int i=0; i<width(); i++) {
    std::vector<int>& blocks = v_blocks[i];
    for (size_t j=0; j < blocks.size(); j++)
      std::cout << blocks[j] << " ";
    std::cout << std::endl;
  }

  std::cout << "[ horizontal blocks ]" << std::endl;
  for (int i=0; i<height(); i++) {
    std::vector<int>& blocks = h_blocks[i];
    for (size_t j=0; j < blocks.size(); j++)
      std::cout << blocks[j] << " ";
    std::cout << std::endl;
  }
}