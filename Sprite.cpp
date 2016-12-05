#include <vector>
#include <stdexcept>

#include "Sprite.h"

using namespace std;
using namespace medieval;

Sprite::Sprite(int index,
	       int x, int y,
	       int width, int height) :
  imageIndex_(index), x_(x), y_(y),
  width_(width), height_(height) {} 

int Sprite::getXCoordinate() const noexcept {
  return x_;
}

int Sprite::getYCoordinate() const noexcept {
  return y_;
}

int Sprite::getWidth() const noexcept {
  return width_;
}

int Sprite::getHeight() const noexcept {
  return height_;
}

int Sprite::getAngle() const noexcept {
  return angle_;
}

int Sprite::getImageIndex() const noexcept {
  return imageIndex_;
}

void Sprite::move() noexcept {}

bool Sprite::hits(const Sprite& other) const noexcept {
  vector<int> hitbox1 = {x_, x_ + width_, y_, y_ + width_};
  vector<int> hitbox2 = {other.getXCoordinate(),
			 other.getXCoordinate() + other.getWidth(),
			 other.getYCoordinate(),
			 other.getYCoordinate() + other.getHeight()};
  return (hitbox1.at(0) < hitbox2.at(1) &&
	  hitbox1.at(1) > hitbox2.at(0) &&
	  hitbox1.at(2) < hitbox2.at(3) &&
	  hitbox1.at(3) > hitbox2.at(2));  
}
