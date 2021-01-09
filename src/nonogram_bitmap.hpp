#pragma once

#include <cassert>
#include <vector>
#include <string>
#include <iostream>
#include "common.hpp"

class NonogramBitmap
{
protected:
  int w;
  int h;
  std::vector<PixelStatus> pixel_status;
public:
  NonogramBitmap(int w, int h);
  NonogramBitmap(NonogramBitmap& bitmap);

  inline PixelStatus& at(int x, int y) {
    assert(x >= 0 && x < w && y >= 0 && y < h);
    return pixel_status[x * w + y];
  }

  inline int width() {
    return w;
  }

  inline int height() {
    return h;
  }

  void copy_from(NonogramBitmap& b);

  std::string str();
  std::pair<int, int> find_unknown();

  void dump();
};