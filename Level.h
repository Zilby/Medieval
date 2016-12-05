#ifndef MEDIEVAL_LEVEL_H
#define MEDIEVAL_LEVEL_H

#include <memory>
#include <vector>
#include "Sprite.h"
#include "Player.h"
#include "Balls.h"

namespace medieval {

/**
 * 
 */
class Level {
public:
  /**
   * Construct a collection of random sprites. 
   * @throw domain_error if the arguments are not valid.
   */
  Level(/** The current level */
        int level);
    
  /**
   * Evolve a collection of sprites.
   */
  void evolve() noexcept;

  /**
   * Get the list of sprites.
   * @return A constant reference to the list of sprites.
   */
  std::vector<std::shared_ptr<Sprite>> getList() const noexcept;

  std::weak_ptr<Player> getPlayer() const noexcept;

  bool dead() noexcept;
  
  bool damaged() noexcept;

  bool healed() noexcept;

  bool scored() noexcept;

  void resetPlayer() noexcept;

  void init() noexcept;
  
private:
  std::shared_ptr<Player> player_; 
  /** The collection of sprites. */
  std::vector<std::shared_ptr<Sprite>> spriteList_;
  int level_; 
};

}

#endif
