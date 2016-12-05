#include <stdexcept>

#include "Sprites.h"

using namespace std;
using namespace ping;

Sprites::Sprites(unsigned int imageCount, unsigned int spriteCount,
		 double minDiameter, double maxDiameter, 
		 int width, int height) {

  // Validate parameters

  if (spriteCount < 1) {
    throw domain_error("There are no sprites");
  }
  if (imageCount < 1) {
    throw domain_error("There are no images for drawing sprites");
  }    
  if (minDiameter < 1.0 || maxDiameter < minDiameter) {
    throw domain_error("Invalid sprite diameter range: from " + 
		       to_string(minDiameter) + " to " + 
		       to_string(maxDiameter));
  }
  if (width <= 0 || height <= 0) {
    throw domain_error("Invalid screen dimension: " + 
		       to_string(width) + " x " + to_string(height));
  }

  // Reserve enough space for all of the sprites

  spriteList_.reserve(spriteCount);

  // Construct the array of sprites without
  // specifying their locations

  for (unsigned int i = 0; i < spriteCount; ++i) {
    spriteList_.push_back(Sprite(engine_, imageCount, 
				 minDiameter, maxDiameter, 
				 width, height));
  }

  // Now place the sprites

  for (auto iter1 = spriteList_.begin(); iter1 != spriteList_.end(); ++iter1) {

    // Place one sprite.  If the sprite hits any
    // other sprite, then try again.  If it takes
    // too many tries, then the screen is presumed
    // to be too full.

    bool hitsAnotherSprite = false;
    for (unsigned int n = 0; n < 100; ++n) {

      // Choose a random location for the sprite

      iter1->chooseRandomLocation(engine_);

      // Determine whether this sprite has hit one
      // of the sprites that have already been
      // placed

      hitsAnotherSprite = false;
      for (auto iter2 = spriteList_.begin(); iter2 != iter1; ++iter2) {
	if (iter1->hits(*iter2)) {
	  hitsAnotherSprite = true;
	  break;
	}
      }

      // If this sprite did not hit another one,
      // go on to place the next sprite

      if (!hitsAnotherSprite) {
	break;
      }
    }

    // If the loop completed without successfully
    // placing the sprite, then the window cannot
    // contain all of the sprites

    if (hitsAnotherSprite) {
      throw domain_error("The window cannot contain all of the requested sprites");
    }
  }
}

const std::vector<Sprite>& Sprites::getList() const noexcept {
  return spriteList_;
}

void Sprites::evolve(double delta) noexcept {
      
  // Clear the bounce flags.
      
  for (Sprite& sprite : spriteList_) {
    sprite.clearBounce();
  }
      
  // Bounce the sprites.  Each unordered pair of
  // sprites is bounced if they hit one another.
      
  for (auto iter1 = spriteList_.begin(); iter1 != spriteList_.end(); ++iter1) {
    for (auto iter2 = spriteList_.begin(); iter2 != iter1; ++iter2) {
      iter1->bounce(*iter2);
    }
  }
      
  // Move the sprites.
  
  for (Sprite& sprite : spriteList_) {
    sprite.move(delta);
  }
}
