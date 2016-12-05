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
  player_->touchingGround(spriteList_);
  player_->touchingWall(spriteList_);
  for (shared_ptr<Sprite>& s : spriteList_) {
    s->move();
  }
}

weak_ptr<Player> Level::getPlayer() const noexcept {
  return weak_ptr<Player>(player_);
}

bool Level::dead() noexcept {
  if(player_->getYCoordinate() > 720) {
    return true;
  }
  return false;
}

bool Level::damaged() noexcept {
  return player_->touchingObstacles(spriteList_);
}

bool Level::healed() noexcept {
  return player_->touchingHealth(spriteList_);
}

bool Level::scored() noexcept {
  return player_->touchingCoin(spriteList_);
}

void Level::resetPlayer() noexcept {
  player_->setX(10);
  player_->setY(50);
  player_->stopV();
  player_->stopH();
  init();
}

void Level::init() noexcept {
  // Add the sprites given the level
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
    spriteList_.push_back(make_shared<Balls>(Balls(5, 225, 380, 225, 225, true)));
    spriteList_.push_back(make_shared<Balls>(Balls(5, 500, 320, 500, 500, true)));
    spriteList_.push_back(make_shared<Balls>(Balls(5, 730, 610, 730, 730, true)));
    spriteList_.push_back(make_shared<Balls>(Balls(6, 800, 160, 600, 1000, true)));
  }
}
