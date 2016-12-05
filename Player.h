#ifndef MEDIEVAL_PLAYER_H
#define MEDIEVAL_PLAYER_H

#include "Sprite.h"
#include <vector>
#include <memory>

namespace medieval {

class Player : public Sprite {
  
public:
  
  Player(int x, int y); 
  
  void move() noexcept override;
  void setX(int x) noexcept;
  void setY(int y) noexcept;
  void setH(int v) noexcept;
  void jump() noexcept; 
  void stopH() noexcept;
  void stopV() noexcept;
  
  bool touchingGround(std::vector<std::shared_ptr<Sprite>> sprites) noexcept;

  bool touchingWall(std::vector<std::shared_ptr<Sprite>> sprites) noexcept;

  bool touchingObstacles(std::vector<std::shared_ptr<Sprite>>& sprites) const noexcept;

  bool touchingHealth(std::vector<std::shared_ptr<Sprite>>& sprites) const noexcept;

  bool touchingCoin(std::vector<std::shared_ptr<Sprite>>& sprites) const noexcept;
  
private:

  bool inAir_ = false;
  int speedH_ = 0;
  int speedV_ = 0;
};
}

#endif
