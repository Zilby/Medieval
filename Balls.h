#ifndef MEDIEVAL_BALLS_H
#define MEDIEVAL_BALLS_H

#include "Sprite.h"
#include <stdexcept>

namespace medieval {

/**
 * A fireball class. This class is a subclass of the sprite
 * class that overrides its move function to allow for rotation 
 * of the image and movement along a fixed path. 
 *
 * @author Alex Zilbersher & Ryan Malloney
 */ 
  
class Balls : public Sprite {
  
public:

  /**
   * Construct a Ball.
   * @throw domain_error if the arguments are not valid.
   */
  Balls(/** The index of this ball's image */
	int index,
	/** The x and y coordinates of this ball */
	int x, int y,
	/** The start and end coordinates of this ball's path */
	int start, int end,
	/** The direction this ball is going in */
	bool left);

  /**
   * Moves the ball given the start and end coordinates
   * instantiated in the constructor. This will be done
   * differently depending on the given image index, 
   * which will also determine the ball's rotation. 
   */
  void move() noexcept override;
    
private:
  
  /**
   * The x coordinate of the start of this ball's path
   */
  int start_;

  /**
   * The x coordinate of the end of this ball's path
   */
  int end_;

  /**
   * A bool to indicate if the ball is moving left (or right)
   */
  bool left_;
};
}

#endif
