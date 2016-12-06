#ifndef MEDIEVAL_WORLD_H
#define MEDIEVAL_WORLD_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdexcept>
#include <vector>
#include <string>
#include <iostream>
#include <memory>
#include "RelevantEvent.h"
#include "Sprite.h"
#include "Level.h"
#include "Player.h"

class SDL_Window;
class SDL_Renderer;
class SDL_Texture;

namespace medieval {

/**
 * A world class. This class contains all the details for our
 * world such as variables to indicate the score, player health, 
 * player lives, current level, etc. It has public methods to add an image
 * to be used in the world, destroy the world, close the world, check
 * for relevant events, refresh the world and draw an image in the world. 
 * 
 *
 * @author Alex Zilbersher & Ryan Malloney
 */
  
class World {
  
public:

  /**
   * Construct the world. 
   */
  World();

  /**
   * Destruct the graphical display.  This closes
   * the display.
   */
  ~World();

  /**
   * Close the graphical display and release the
   * resources.
   */
  void close() noexcept;

  /**
   * Add an image to the collection.
   */
  void addImage(/** The location of the file. */
		const std::string& fileLocation) noexcept;

  /**
   * Check for relevant events as specified in the
   * RelevantEvent enumeration.  If quit is
   * requested, the display is closed and deleted.
   * This also detects player inputs and modifies the 
   * world and level accordingly. 
   * @return The relevant event that occurred or
   * None if no relevant event occurred.  If the
   * Quit event occurred, then the display is
   * closed and deleted.
   */
  RelevantEvent checkForRelevantEvent() noexcept;

  /**
   * Refresh the world. Updates all the sprites and
   * makes changes based on what the current status of the 
   * world is. 
   * @throw domain_error if the display could not
   * be refreshed.
   */
  void refresh();

  /**
   * Draws a sprite into the world. 
   * @throw domain_error if unable to render a sprite
   */
  void draw(/** The x and y coordinate to draw the image at */
	    int x, int y,
	    /** The width and height of the image */
	    int width, int height,
	    /** The index of the image. */
	    int index);

  /**
   * Draws text into the world. 
   */
  void drawText(/** The x and y coordinate to draw the text at */
		int x, int y,
		/** The string for the text */
		std::string text,
		/** size of the text */
		int size); 
  
private:

  /** 
   * Indicates if player is told to move left
   */
  bool left_ = false;

  /** 
   * Indicates if player is told to move right
   */
  bool right_ = false;

  /** 
   * The number of lives the player has
   */
  int lives_ = 5;

  /** 
   * The amount of health the player has (max 3)
   */
  int health_ = 3;

  /** 
   * The current time
   */
  int time_ = 0;

  /** 
   * The time counter
   */
  int timeCounter_ = 0;

  /** 
   * The current high score
   */
  int highScore_ = 0;

  /** 
   * The current score
   */
  int score_ = 0;

  /** 
   * The current level number (0 is intro screen, 
   * -1 is gameover screen, -2 is win screen)
   */
  int currentLevel_ = 0;

  /** 
   * The level object, instantiated with the current level
   */
  Level level_ = Level(currentLevel_);

  /** 
   * A weak pointer to the player. This is locked when the world
   * must give the player input
   */
  std::weak_ptr<Player> player_ = level_.getPlayer(); 

  /** 
   * The display window. 
   */
  SDL_Window* window_ = nullptr;

  /** 
   * The display rendering tool. 
   */
  SDL_Renderer* renderer_ = nullptr;

  /** 
   * The collection of images. 
   */
  std::vector<SDL_Texture*> images_;

  /** 
   * The width of the window. 
   */
  const int width_ = 1080;

  /** 
   * The height of the window. 
   */
  const int height_ = 720;

  /** 
   * Our font for the game. 
   */
  TTF_Font* font_;
  
  /** 
   * The color of our font. 
   */
  SDL_Color textColor_;

  /**
   * Clear the background to opaque white.
   */
  void clearBackground();
};
}

#endif
