#include "Balls.h"
#include <iostream>

using namespace std;
using namespace medieval;

Balls::Balls(int index, int x, int y, int start, int end, bool left) :
  Sprite(index, x, y, 50, 50), start_(start), end_(end), left_(left) {
  if(start > end || x < start || x > end) {
    throw logic_error("Bad path given");
  }
}

void Balls::move() noexcept {
  if(imageIndex_ == 6) {
    if(left_) {
      x_ -= 5;
    } else {
      x_ += 5;
    }
    if(x_ >= end_) {
      left_ = true;
    } else if (x_ <= start_) {
      left_ = false;
    }
    angle_ -= 20;
  } else {
    angle_ += 30;
  }
}
