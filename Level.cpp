#include <stdexcept>
#include <iostream>
#include "Level.h"

using namespace std;
using namespace medieval;

Level::Level(int level) : level_(level) {
  player_ = make_shared<Player>(Player(10, 50));
  init();
}

vector<shared_ptr<Sprite>> Level::getList() const noexcept {
  return spriteList_;
}

void Level::evolve() noexcept {
  
  // makes sure player knows if it's touching the ground
  // or a wall before moving them
  player_->touchingGround(spriteList_);

  // moves all of our sprites
  player_->touchingWall(spriteList_);
  for (shared_ptr<Sprite>& s : spriteList_) {
    s->move();
  }
}

weak_ptr<Player> Level::getPlayer() const noexcept {
  return weak_ptr<Player>(player_);
}

bool Level::dead() noexcept {
  // player is dead if they fall off the bottom
  // of the screen
  if(player_->getYCoordinate() > 720) {
    return true;
  }
  return false;
}

bool Level::damaged() noexcept {
  // player takes damage if they touch an obstacle
  return player_->touchingObstacles(spriteList_);
}

bool Level::healed() noexcept {
  // player gains health if they touch a pickup
  return player_->touchingHealth(spriteList_);
}

bool Level::scored() noexcept {
  // player scores if they touch a coin
  return player_->touchingCoin(spriteList_);
}

bool Level::next() const noexcept {
  // player reached end if they reach right side of screen
  return player_->getXCoordinate() > 1080;
}

void Level::resetPlayer() noexcept {
  // resets the player coordinates, stops their momentum
  player_->setX(10);
  player_->setY(50);
  player_->stopV();
  player_->stopH();
  // reinitializes all of the other sprites
  init();
}

void Level::init() noexcept {
  // Adds the sprites given the level
  spriteList_.clear();
  if(level_ == 1) {
    spriteList_.push_back(player_);
    spriteList_.push_back(make_shared<Sprite>(Sprite(4, -50, 670, 50, 50)));
    spriteList_.push_back(make_shared<Sprite>(Sprite(4, 0, 670, 50, 50)));
    spriteList_.push_back(make_shared<Sprite>(Sprite(4, 50, 670, 50, 50)));
    spriteList_.push_back(make_shared<Sprite>(Sprite(4, 100, 670, 50, 50)));
    spriteList_.push_back(make_shared<Sprite>(Sprite(4, 150, 670, 50, 50)));
    spriteList_.push_back(make_shared<Sprite>(Sprite(4, 200, 670, 50, 50)));
    spriteList_.push_back(make_shared<Sprite>(Sprite(4, 150, 620, 50, 50)));
    spriteList_.push_back(make_shared<Sprite>(Sprite(4, 150, 570, 50, 50)));
    spriteList_.push_back(make_shared<Sprite>(Sprite(4, 350, 520, 50, 50)));
    spriteList_.push_back(make_shared<Sprite>(Sprite(4, 400, 520, 50, 50)));
    spriteList_.push_back(make_shared<Sprite>(Sprite(4, 450, 520, 50, 50)));
    spriteList_.push_back(make_shared<Sprite>(Sprite(4, 350, 570, 50, 50)));
    spriteList_.push_back(make_shared<Sprite>(Sprite(4, 400, 570, 50, 50)));
    spriteList_.push_back(make_shared<Sprite>(Sprite(4, 450, 570, 50, 50)));
    spriteList_.push_back(make_shared<Sprite>(Sprite(4, 350, 330, 50, 50)));
    spriteList_.push_back(make_shared<Sprite>(Sprite(4, 400, 330, 50, 50)));
    spriteList_.push_back(make_shared<Sprite>(Sprite(4, 450, 330, 50, 50)));
    spriteList_.push_back(make_shared<Sprite>(Sprite(4, 600, 230, 50, 50)));
    spriteList_.push_back(make_shared<Sprite>(Sprite(4, 650, 230, 50, 50)));
    spriteList_.push_back(make_shared<Sprite>(Sprite(4, 700, 230, 50, 50)));
    spriteList_.push_back(make_shared<Sprite>(Sprite(4, 750, 230, 50, 50)));
    spriteList_.push_back(make_shared<Sprite>(Sprite(4, 800, 230, 50, 50)));
    spriteList_.push_back(make_shared<Sprite>(Sprite(4, 850, 230, 50, 50)));
    spriteList_.push_back(make_shared<Sprite>(Sprite(4, 900, 230, 50, 50)));
    spriteList_.push_back(make_shared<Sprite>(Sprite(4, 950, 230, 50, 50)));
    spriteList_.push_back(make_shared<Sprite>(Sprite(4, 1000, 230, 50, 50)));
    spriteList_.push_back(make_shared<Sprite>(Sprite(4, 1050, 230, 50, 50)));
    spriteList_.push_back(make_shared<Sprite>(Sprite(4, 150, 190, 50, 50)));
    spriteList_.push_back(make_shared<Sprite>(Sprite(4, 200, 190, 50, 50)));
    spriteList_.push_back(make_shared<Sprite>(Sprite(4, 250, 190, 50, 50)));
    spriteList_.push_back(make_shared<Sprite>(Sprite(4, 600, 670, 50, 50)));
    spriteList_.push_back(make_shared<Sprite>(Sprite(4, 650, 670, 50, 50)));
    spriteList_.push_back(make_shared<Sprite>(Sprite(4, 700, 670, 50, 50)));
    spriteList_.push_back(make_shared<Sprite>(Sprite(7, 650, 620, 50, 50)));
    spriteList_.push_back(make_shared<Sprite>(Sprite(8, 200, 120, 50, 50)));
    spriteList_.push_back(make_shared<Sprite>(Sprite(8, 800, 160, 50, 50)));
    spriteList_.push_back(make_shared<Balls>(Balls(5, 225, 380, 225, 225, true)));
    spriteList_.push_back(make_shared<Balls>(Balls(5, 500, 320, 500, 500, true)));
    spriteList_.push_back(make_shared<Balls>(Balls(5, 730, 610, 730, 730, true)));
    spriteList_.push_back(make_shared<Balls>(Balls(6, 800, 160, 600, 1000, true)));
  } else if(level_ == 2) {
    spriteList_.push_back(player_);
    spriteList_.push_back(make_shared<Sprite>(Sprite(4, -50, 230, 50, 50)));
    spriteList_.push_back(make_shared<Sprite>(Sprite(4, 0, 230, 50, 50)));
    spriteList_.push_back(make_shared<Sprite>(Sprite(4, 50, 230, 50, 50)));
    spriteList_.push_back(make_shared<Sprite>(Sprite(4, 100, 230, 50, 50)));
    spriteList_.push_back(make_shared<Sprite>(Sprite(4, 150, 230, 50, 50)));
    spriteList_.push_back(make_shared<Sprite>(Sprite(4, 100, 430, 50, 50)));
    spriteList_.push_back(make_shared<Sprite>(Sprite(4, 150, 430, 50, 50)));
    spriteList_.push_back(make_shared<Sprite>(Sprite(4, 450, 400, 50, 50)));
    spriteList_.push_back(make_shared<Sprite>(Sprite(4, 500, 400, 50, 50)));
    spriteList_.push_back(make_shared<Sprite>(Sprite(4, 550, 400, 50, 50)));
    spriteList_.push_back(make_shared<Sprite>(Sprite(4, 600, 400, 50, 50)));
    spriteList_.push_back(make_shared<Sprite>(Sprite(4, 650, 350, 50, 50)));
    spriteList_.push_back(make_shared<Sprite>(Sprite(4, 600, 350, 50, 50)));
    spriteList_.push_back(make_shared<Sprite>(Sprite(4, 600, 300, 50, 50)));
    spriteList_.push_back(make_shared<Sprite>(Sprite(4, 600, 250, 50, 50)));
    spriteList_.push_back(make_shared<Sprite>(Sprite(4, 475, 650, 50, 50)));
    spriteList_.push_back(make_shared<Sprite>(Sprite(4, 525, 650, 50, 50)));
    spriteList_.push_back(make_shared<Sprite>(Sprite(4, 575, 650, 50, 50)));
    spriteList_.push_back(make_shared<Sprite>(Sprite(4, 100, 650, 50, 50)));
    spriteList_.push_back(make_shared<Sprite>(Sprite(4, 150, 650, 50, 50)));
    spriteList_.push_back(make_shared<Sprite>(Sprite(4, 750, 520, 50, 50)));
    spriteList_.push_back(make_shared<Sprite>(Sprite(4, 800, 520, 50, 50)));
    spriteList_.push_back(make_shared<Sprite>(Sprite(4, 850, 520, 50, 50)));
    spriteList_.push_back(make_shared<Sprite>(Sprite(4, 900, 520, 50, 50)));
    spriteList_.push_back(make_shared<Sprite>(Sprite(4, 950, 520, 50, 50)));
    spriteList_.push_back(make_shared<Sprite>(Sprite(4, 1000, 520, 50, 50)));
    spriteList_.push_back(make_shared<Sprite>(Sprite(4, 1050, 520, 50, 50)));
    spriteList_.push_back(make_shared<Sprite>(Sprite(4, 1100, 520, 50, 50)));
    spriteList_.push_back(make_shared<Sprite>(Sprite(8, 125, 370, 50, 50)));
    spriteList_.push_back(make_shared<Sprite>(Sprite(8, 650, 280, 50, 50)));
    spriteList_.push_back(make_shared<Sprite>(Sprite(7, 125, 590, 50, 50)));
    spriteList_.push_back(make_shared<Balls>(Balls(5, 600, 180, 600, 600, true)));
    spriteList_.push_back(make_shared<Balls>(Balls(5, 60, 370, 60, 60, true)));	
    spriteList_.push_back(make_shared<Balls>(Balls(6, 300, 190, 220, 500, true)));
    spriteList_.push_back(make_shared<Balls>(Balls(6, 350, 620, 230, 400, false)));
    spriteList_.push_back(make_shared<Balls>(Balls(6, 700, 280, 680, 870, true)));
  }
}
