#ifndef MEDIEVAL_SPRITE_H
#define MEDIEVAL_SPRITE_H

namespace medieval {

/**
 * A sprite class. This class represents a basic sprite and is 
 * a super class to more specific instantiations such as fireballs
 * and players. It leaves its move function to be overriden by such 
 * classes. It cointains functions to return its variables, as well
 * as whether it collides with another sprite. The type of sprite is 
 * often identified by its image index. 
 *
 * @author Alex Zilbersher & Ryan Malloney
 */

class Sprite {
public:
  Sprite(/** The index of this sprite's image */
	 int index,
	 /** The x and y coordinates of this sprite */
	 int x, int y,
	 /** The width and height of this sprite */
	 int width, int height);

  /**
   * The x-coordinate of a square containing the sprite.
   * @return The x-coordinate of the sprite.
   */
  int getXCoordinate() const noexcept;

  /**
   * The y-coordinate of a square containing the sprite.
   * @return The y-coordinate of the sprite.
   */
  int getYCoordinate() const noexcept;

  /**
   * The width of the sprite
   * @return The width of the sprite.
   */
  int getWidth() const noexcept;

  /**
   * The height of the sprite
   * @return The height of the sprite.
   */
  int getHeight() const noexcept; 

  /**
   * The angle of the sprite's image
   * @return The angle of the sprite.
   */
  int getAngle() const noexcept;
  
  /**
   * Get the image index of the sprite.
   * @return The index of the image to use for the sprite.
   */
  int getImageIndex() const noexcept;

  /**
   * Determine whether two sprites are hitting each other.
   * @return Whether the two sprites are colliding
   */
  bool hits(/** The other sprite that may be hitting this one. */ 
	    const Sprite& other) const noexcept;

  /**
   * Moves the sprite. The default sprite doesn't move but leaves
   * this method to be overriden. 
   */
  virtual void move() noexcept;

protected:
  
  /** 
   * Index of the image to use for the sprite. 
   */
  int imageIndex_;

  /** 
   * the x coordinate of the sprite. 
   */
  int x_;

  /** 
   * the y coordinate of the sprite. 
   */
  int y_;

  /** 
   * the width of the sprite. 
   */
  int width_;

  /** 
   * the height of the sprite. 
   */
  int height_;

  /** 
   * the angle of the sprite. 
   */
  int angle_ = 0;
  
private:
  
};
}

#endif
