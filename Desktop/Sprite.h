#ifndef PING_SPRITE_H
#define PING_SPRITE_H

#include <random>

namespace ping {

/**
 * A sprite with a position, velocity, color and image.  Methods are available for
 * the following:
 *
 * <ol>
 * <li>Getters for the position, angle and diameter.
 * <li>Choose a random location for the center of the sprite.
 * <li>Move a sprite at its velocity for a specified period of time (&Delta;t).  If the
 * sprite hits the boundary, then it bounces.
 * <li>Determine whether two sprites are hitting each other.
 * <li>Bounce one sprite off another sprite if they are hitting each other.  The bounce
 * is the standard one for elastic collisions which preserve momentum.  There is a
 * flag indicating that a sprite has bounced.  This is used to ensure that during a
 * single iteration (i.e., during &Delta;t) a sprite bounces only once.  Allowing more
 * than one bounce during an iteration can result in problematic behavior because of
 * round-off errors.
 * <li>Clear the flag indicating that a sprite has bounced.
 * </ol>
 *
 * @author Ken Baclawski
 */
class Sprite {
public:
  /**
   * Construct a random sprite. 
   * @throw domain_error if the arguments are invalid.
   */
  Sprite(/** Random number generator. */ std::mt19937& engine,
	 /** The number of images. */ unsigned int imageCount,
	 /** The minimum diameter of a sprite. */ double minDiameter = 20,
	 /** The maximum diameter of a sprite. */ double maxDiameter = 30,
	 /** The width of the screen in pixels. */ int width = 640,
	 /** The height of the screen in pixels. */ int height = 480);

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
   * The diameter of the sprite.
   * @return The sprite diameter.
   */
  int getDiameter() const noexcept;

  /**
   * The angle of the sprite.
   * @return The sprite angle.
   */
  double getAngle() const noexcept;

  /**
   * Get the image index of the sprite.
   * @return The index of the image to use for the sprite.
   */
  int getImageIndex() const noexcept;

  /**
   * Choose a random location for the sprite.
   */
  void chooseRandomLocation(/** Random number generator. */ 
			    std::mt19937& engine) noexcept;

  /**
   * Move the sprite to a new position as
   * determined by the the specified period of
   * time.
   */
  void move(/** The interval of time during which 
	    the sprite moves. */ double delta) noexcept;

  /**
   * Clear the bounce flag. 
   */
  void clearBounce() noexcept;

  /**
   * Bounce one sprite off each other.  If a bounce
   * should occur, then change the velocities of
   * both sprites so as to conserve momentum.  The
   * mass is the square of the radius.  Once a sprite
   * has bounced, it cannot bounce again during
   * this iteration.
   */
  void bounce(/** The other sprite against which this 
		  sprite may bounce. */ Sprite& other) noexcept;

  /**
   * Determine whether two sprites are hitting each other.
   * @return Whether the two sprites are too close.
   */
  bool hits(/** The other sprite that may be hitting this one. */ 
	    const Sprite& other) const noexcept;

private:
  /** Continuous uniform random distribution. */
  std::uniform_real_distribution<double> realDistribution_;
  /** Discrete uniform random distribution. */
  std::uniform_int_distribution<unsigned int> integerDistribution_;

  /** The radius of the sprite. */
  const double radius_ = 1.0;
  /** The square of the radius of the sprite. This is the mass of the sprite. */
  const double radius2_ = 1.0;

  /** The width of the display in pixels. */
  const int width_ = 640;
  /** The height of the display in pixels. */
  const int height_ = 480;

  /** Index of the image to use for the sprite. */
  const unsigned int imageIndex_ = 0;

  /** The current x-coordinate of the center of the sprite. */
  double cx_ = 0.0;
  /** The current y-coordinate of the center of the sprite. */
  double cy_ = 0.0;

  /** The current x-coordinate of the velocity of the sprite. */
  double vx_ = 0.0;
  /** The current y-coordinate of the velocity of the sprite. */
  double vy_ = 0.0;

  /** The rotation angle. */
  double angle_ = 0.0;
  /** The rotation rate. */
  double rot_ = 0.0;

  /**
   * Whether the sprite bounced in the most recent
   * iteration.  This flag prevents a sprite from
   * bouncing a second time before the sprite moves.
   */
  bool bounced_ = false;
};

}

#endif
