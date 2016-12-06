#ifndef MEDIEVAL_PLAYER_H
#define MEDIEVAL_PLAYER_H

#include "Sprite.h"
#include <vector>
#include <memory>

namespace medieval {

/**
 * A player class. This class is a subclass of Sprite, and implements
 * methods that allow for user input for movement. It overrides Sprite's 
 * move method and has functions to set its x and y coordinates, its horizontal
 * momentum, tell it to jump, top its horizontal or vertical velocity and indicate if
 * it is touching the ground, touching a wall, touching obstacles, health, and coins
 * and respond appropriately. 
 *
 * @author Alex Zilbersher & Ryan Malloney
 */
  
class Player : public Sprite {
  
public:

  /**
   * Construct a Player.
   */
  Player(/** The x and y coordinates of this player */
	 int x, int y); 

  /**
   * Moves the player given its velocities
   */
  void move() noexcept override;

  /**
   * Sets the player's x coordinate
   */
  void setX(int x) noexcept;
  
  /**
   * Sets the player's y coordinate
   */
  void setY(int y) noexcept;

  /**
   * Sets the player's horizontal velocity
   */
  void setH(int v) noexcept;

  /**
   * Tells the player to jump
   */
  void jump() noexcept;

  /**
   * Stops the player's horizontal momentum
   */
  void stopH() noexcept;

  /**
   * Stops the player's vertical momentum
   */
  void stopV() noexcept;

  /**
   * Determines if the player is touching the ground and responds 
   * accordingly. 
   * @return whether the player is touching the ground
   */
  bool touchingGround(/** The list of sprites to check if touching */
		      std::vector<std::shared_ptr<Sprite>> sprites) noexcept;

  /**
   * Determines if the player is touching a wall and responds 
   * accordingly. 
   * @return whether the player is touching a wall
   */
  bool touchingWall(/** The list of sprites to check if touching */
		    std::vector<std::shared_ptr<Sprite>> sprites) noexcept;

  /**
   * Determines if the player is touching an obstacle and responds 
   * accordingly
   * @return whether the player is touching an obstacle
   */
  bool touchingObstacles(/** The list of sprites to check if touching */
			 std::vector<std::shared_ptr<Sprite>>& sprites) const noexcept;

  /**
   * Determines if the player is touching a health pickup and responds
   * accordingly. 
   * @return whether the player is a health pickup
   */
  bool touchingHealth(/** The list of sprites to check if touching */
		      std::vector<std::shared_ptr<Sprite>>& sprites) const noexcept;

  /**
   * Determines if the player is touching a coin and responds 
   * accordingly. 
   * @return whether the player is touching a coin
   */
  bool touchingCoin(/** The list of sprites to check if touching */
		    std::vector<std::shared_ptr<Sprite>>& sprites) const noexcept;
  
private:

  /**
   * Whether or not the player is in the air. 
   */
  bool inAir_ = false;

  /**
   * The player's horizontal momentum
   */
  int speedH_ = 0;

  /**
   * The player's vertical momentum
   */
  int speedV_ = 0;
};
}

#endif
