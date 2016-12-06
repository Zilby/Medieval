#ifndef MEDIEVAL_LEVEL_H
#define MEDIEVAL_LEVEL_H

#include <memory>
#include <vector>
#include "Sprite.h"
#include "Player.h"
#include "Balls.h"

namespace medieval {

/**
 * A level class. This class contains all of the details for
 * our levels, including all of the level's sprites such as the
 * platforms, obstacles and the player character. Level contains 
 * methods to move all of the sprites, get the list of sprites,
 * return a weak ptr to the player, interact with the player and
 * change the level. 
 *
 * @author Alex Zilbersher & Ryan Malloney
 */
  
class Level {
public:
  
  /**
   * Construct a level based on the current level. 
   */
  Level(/** The current level */
        int level);
    
  /**
   * Evolve a collection of sprites. This makes them move
   * to their new locations. 
   */
  void evolve() noexcept;

  /**
   * Get the list of sprites.
   * @return the list of sprites.
   */
  std::vector<std::shared_ptr<Sprite>> getList() const noexcept;

  /**
   * Get the player sprite
   * @return a weak pointer to the player sprite
   */
  std::weak_ptr<Player> getPlayer() const noexcept;

  /**
   * Get whether or not the player is dead
   * @return a bool indicating if the player is dead
   */
  bool dead() noexcept;

  /**
   * Get whether or not the player is damaged
   * @return a bool indicating if the player is damaged
   */
  bool damaged() noexcept;

  /**
   * Get whether or not the player picked up health
   * @return a bool indicating if the player got a health pickup
   */
  bool healed() noexcept;

  /**
   * Get whether or not the player picked up a coin
   * @return a bool indicating if the player got a coin
   */
  bool scored() noexcept;

  /**
   * Get whether or not the player reached the end of the level
   * @return a bool indicating if the player reached the end
   */
  bool next() const noexcept;

  /**
   * Resets the position of the player and all other sprites in the 
   * level to their starting position. 
   */
  void resetPlayer() noexcept;
  
private:

  /**
   * The player character. 
   */
  std::shared_ptr<Player> player_;
  
  /** 
   * The collection of sprites. 
   */
  std::vector<std::shared_ptr<Sprite>> spriteList_;

  /**
   * The level number
   */
  int level_;

  /**
   * Adds all the sprites needed for this level to the sprite list. 
   */
  void init() noexcept;
};

}

#endif
