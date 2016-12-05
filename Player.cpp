#include "Player.h"

#include <iostream>
#include <string>

using namespace std;
using namespace medieval;

Player::Player(int x, int y)
  : Sprite(2, x, y, 80, 80) {}

void Player::move() noexcept {
  if(inAir_) {
    speedV_ += 1;
  }
  
  // flips the player image given their direction
  if(speedH_ > 0) {
    imageIndex_ = 2;
  }
  if (speedH_ < 0) {
    imageIndex_ = 3;
  }
  
  x_ += speedH_;
  y_ += speedV_;
}

void Player::setX(int x) noexcept {
  x_ = x;
}

void Player::setY(int y) noexcept {
  y_ = y;
}

void Player::setH(int v) noexcept {
  speedH_ = v;
}

void Player::jump() noexcept {
  if (!inAir_) {
    speedV_ = -20;
    // to give a little boost to the beginning
    // of the jump
    y_ -= 20;
    inAir_ = true;
  }
}

void Player::stopH() noexcept {
  speedH_ = 0;
}

void Player::stopV() noexcept {
  speedV_ = 0;
}

bool Player::touchingGround(vector<shared_ptr<Sprite>> sprites) noexcept {
  inAir_ = true;
  // checks if the player is moving
  if (speedV_ >= 0) {
    // if the player is it will check through the sprites
    for(shared_ptr<Sprite> s : sprites) {
      // checks if the player's not currently hitting this as a wall
      // and that it's underneath you
      if(!(s->hits(*this) && ((x_ + width_ - (s->getXCoordinate())) < 10) && (s->getImageIndex() == 4)) &&
	 !(s->hits(*this) && (((s->getXCoordinate() + s->getWidth()) - x_) < 10)) &&
	 (s->hits(*this) && ((y_ + height_ - (s->getYCoordinate())) < 35) && (s->getImageIndex() == 4))) {
	// if so it will reset you ycor, your speed and your in air status
	y_ = s->getYCoordinate() - height_ + 1;
	speedV_ = 0;
	inAir_ = false;
	break;
      }
    }
  }
  return inAir_;
}

bool Player::touchingWall(vector<shared_ptr<Sprite>> sprites) noexcept {
  // checks if the player is moving
  if (speedH_ != 0) {
    // if the player is it will check through the sprites
    for(shared_ptr<Sprite> s : sprites) {
      // checks if the player's not currently touching the sprite on the ground,
      // or that you're in the air after recently falling
      if(!(s->hits(*this) && ((y_ + height_ - (s->getYCoordinate())) < 35) && (s->getImageIndex() == 4)) || inAir_) {
	// if moving right it checks if you collide with a wall on the right
	if(speedH_ > 0) {
	  // if you do it will reset your xcor and your speed
	  if(s->hits(*this) && ((x_ + width_ - (s->getXCoordinate())) < 10) && (s->getImageIndex() == 4)) {
	    x_ = s->getXCoordinate() - width_ + 1;
	    speedH_ = 0;
	    return true;
	  }
	  // if moving left it checks if you collide with a wall on the left
	} else {
	  // if you do it will reset your xcor and your speed
	  if(s->hits(*this) && (((s->getXCoordinate() + s->getWidth()) - x_) < 10) && (s->getImageIndex() == 4)) {
	    x_ = s->getXCoordinate() + s->getWidth() - 1;
	    speedH_ = 0;
	    return true;
	  }
	}
      }
    }
  }
  return false;
}

bool Player::touchingObstacles(vector<shared_ptr<Sprite>>& sprites) const noexcept {
  for(auto iter = sprites.begin(); iter != sprites.end(); ++iter) {
    if ((((*iter)->getImageIndex() == 5) || ((*iter)->getImageIndex() == 6)) && ((*iter)->hits(*this))) {
      sprites.erase(iter);
      return true;
    }
  }
  return false;
}

bool Player::touchingHealth(vector<shared_ptr<Sprite>>& sprites) const noexcept {
  for(auto iter = sprites.begin(); iter != sprites.end(); ++iter) {
    if (((*iter)->getImageIndex() == 7) && ((*iter)->hits(*this))) {
      sprites.erase(iter);
      return true;
    }
  }
  return false;
}

bool Player::touchingCoin(vector<shared_ptr<Sprite>>& sprites) const noexcept {
  for(auto iter = sprites.begin(); iter != sprites.end(); ++iter) {
    if (((*iter)->getImageIndex() == 8) && ((*iter)->hits(*this))) {
      sprites.erase(iter);
      return true;
    }
  }
  return false;
}
