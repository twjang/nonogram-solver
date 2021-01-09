#pragma once

#include <vector>
#include "common.hpp"
#include "nonogram_bitmap.hpp"

class NonogramProblem 
{
protected:
  std::vector<std::vector<int>> h_blocks; //horizontal blocks
  std::vector<std::vector<int>> v_blocks; //vertical blocks

public:
  NonogramProblem(std::vector<std::vector<int>>& h_blocks_, std::vector<std::vector<int>> v_blocks_) {
    h_blocks = h_blocks_;
    v_blocks = v_blocks_;
  }

  inline int width() {
    return v_blocks.size();
  }

  inline int height() {
    return h_blocks.size();
  }
  
  int update_v_block(int x, NonogramBitmap& b);
  int update_h_block(int y, NonogramBitmap& b);

  bool solve(NonogramBitmap& b);
  void dump();
};