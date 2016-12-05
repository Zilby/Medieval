#ifndef MEDIEVAL_SPRITE_H
#define MEDIEVAL_SPRITE_H

namespace medieval {

/**
 * Default sprite is a platform
 *
 */
class Sprite {
public:
  Sprite(int index, int x, int y, int width, int height);

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

  int getWidth() const noexcept;

  int getHeight() const noexcept; 

  int getAngle() const noexcept;
  
  /**
   * Get the image index of the sprite.
   * @return The index of the image to use for the sprite.
   */
  int getImageIndex() const noexcept;

  /**
   * Determine whether two sprites are hitting each other.
   * @return Whether the two sprites are too close.
   */
  bool hits(/** The other sprite that may be hitting this one. */ 
	    const Sprite& other) const noexcept;

  virtual void move() noexcept;

protected:
  /** Index of the image to use for the sprite. */
  int imageIndex_;

  int x_;
  int y_;

  int width_;
  int height_;
  int angle_ = 0;
  
private:
  
};
}

#endif
