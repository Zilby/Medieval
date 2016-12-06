#include "Balls.h"
#include <iostream>

using namespace std;
using namespace medieval;

Balls::Balls(int index, int x, int y, int start, int end, bool left) :
  Sprite(index, x, y, 50, 50), start_(start), end_(end), left_(left) {

  // if the ball is given an invalid path, an error will be thrown. 
  if(start > end || x < start || x > end) {
    throw logic_error("Bad path given");
  }
}

void Balls::move() noexcept {

  // will move the ball if the image indicates
  // that it is a moving fireball
  if(imageIndex_ == 6) {
    if(left_) {
      x_ -= 5;
    } else {
      x_ += 5;
    }

    // changes direction once the ball reaches the end
    // of its path
    if(x_ >= end_) {
      left_ = true;
    } else if (x_ <= start_) {
      left_ = false;
    }
    angle_ -= 20;
  } else {

    // will rotate the ball as a stationary obstacle
    // if the image is not that of a moving fireball
    angle_ += 30;
  }
}
