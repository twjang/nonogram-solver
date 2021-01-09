#include <iostream>

#include "nonogram_bitmap.hpp"

NonogramBitmap::NonogramBitmap(NonogramBitmap& bitmap) {
  w = bitmap.w;
  h = bitmap.h;
  pixel_status = bitmap.pixel_status;
}

NonogramBitmap::NonogramBitmap(int w_, int h_) {
  w = w_;
  h = h_;
  pixel_status = std::vector<PixelStatus>(w_ * h_, Unknown);
}

std::string NonogramBitmap::str() {
  std::string res = "";
  for (int y=0; y < h; y++) {
    for (int x=0; x < w; x++) {
      std::string ch;
      switch(at(x, y)) {
        case Unknown:
          ch = "??";
          break;
        case Filled:
          ch = "\u2b1b";
          break;
        case Unfilled:
          ch = "\u2b1c";
          break;
      }
      res += ch;
    }
    res += "\n";
  }
  return res;
}

std::pair<int, int> NonogramBitmap::find_unknown(){
  for (int y=0; y<h; y++) {
    for (int x = 0; x < w; x++) {
      if (at(x,y) == Unknown)
        return std::make_pair(x, y);
    }
  }
  return std::make_pair(-1, -1);
}

void NonogramBitmap::copy_from(NonogramBitmap& b) {
  assert(w == b.width());
  assert(h == b.height());
  std::copy(b.pixel_status.begin(), b.pixel_status.end(), pixel_status.begin());
}

void NonogramBitmap::dump() {
    std::cout << str() << std::endl;
}