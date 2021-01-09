#include "line_solver.hpp"

LineSolver::LineSolver(std::vector<int> &t_, std::vector<PixelStatus> &i_){
  target_blocks = t_;
  initial_state = i_;
  fill_count.resize(initial_state.size(), 0);
}

int LineSolver::update_state(std::vector<PixelStatus> &ns) {
  uint32_t cnt = search(0, 0, 0, Unfilled);
  if (cnt == 0)
    return -1;
  

  int diff = 0;
  ns.resize(initial_state.size(), Unknown);
  for (uint32_t i=0; i < fill_count.size(); i++) {
    if (cnt == fill_count[i]) ns[i] = Filled;
    else if (0 == fill_count[i]) ns[i] = Unfilled;
    else ns[i] = Unknown;
    if (ns[i] != initial_state[i])
      diff++;
  }
  return diff;
}

int LineSolver::search(uint32_t cur_block_idx, int cur_block_cnt, uint32_t cur_loc, PixelStatus prev_pixel)
{
  bool should_unfill = false;
  bool should_fill = false;

  if (target_blocks.size() == 0)
    should_unfill = true;
  else if (cur_block_idx == target_blocks.size())
    should_unfill = true;
  else if (cur_block_cnt == target_blocks[cur_block_idx])
    should_unfill = true;

  if (!should_unfill)
  {
    if (cur_block_cnt > 0 && cur_block_cnt < target_blocks[cur_block_idx])
      should_fill = true;
  }

  if (cur_loc >= initial_state.size()) {
    if (should_unfill && cur_block_idx >= (target_blocks.size() - 1))
      return 1;
    else
      return 0;
  }

  bool try_fill = false;
  bool try_unfill = false;

  switch (initial_state[cur_loc])
  {
  case Unknown:
    try_fill = !should_unfill;
    try_unfill = !should_fill;
  case Filled:
    try_fill = !should_unfill;
    break;
  case Unfilled:
    try_unfill = !should_fill;
    break;
  }

  int success_cnt = 0;
  if (try_fill)
  {
    success_cnt += search(cur_block_idx, cur_block_cnt + 1, cur_loc + 1, Filled);
    fill_count[cur_loc] += success_cnt;
  }

  if (try_unfill)
  {
    if (prev_pixel == Unfilled)
      success_cnt += search(cur_block_idx, 0, cur_loc + 1, Unfilled);
    else
      success_cnt += search(cur_block_idx + 1, 0, cur_loc + 1, Unfilled);
  }

  return success_cnt;
}
