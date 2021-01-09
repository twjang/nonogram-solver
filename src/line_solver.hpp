#pragma once

#include <vector>
#include <cinttypes>
#include "common.hpp"

class LineSolver {
protected:
  std::vector<int> target_blocks;
  std::vector<PixelStatus> initial_state;
  std::vector<uint32_t> fill_count;

  // run dfs
  int search(uint32_t cur_block_idx, int cur_block_cnt, uint32_t cur_loc, PixelStatus prev_pixel);

public:
  LineSolver(std::vector<int> &target_blocks, std::vector<PixelStatus> &initial_state);

  // count updated blocks. returns -1 on error
  int update_state(std::vector<PixelStatus>& state);
};

