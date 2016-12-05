#ifndef MEDIEVAL_WORLD_H
#define MEDIEVAL_WORLD_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdexcept>
#include <vector>
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

class World {
  
public:

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
   * @return The relevant event that occurred or
   * None if no relevant event occurred.  If the
   * Quit event occurred, then the display is
   * closed and deleted.
   */
  RelevantEvent checkForRelevantEvent() noexcept;

  /**
   * Refresh the display.
   * @throw domain_error if the display could not
   * be refreshed.
   */
  void refresh();

  void draw(int x, int y, int width, int height, int index); 
  
private:

  bool alive_ = true;
  bool gameLose_ = false;
  bool gameWin_ = false;
  bool pause_ = false;
  bool left_ = false;
  bool right_ = false;
  int lives_ = 5;
  int health_ = 3;
  int time_ = 0;
  int highScore_ = 0;
  int bestTime_ = -1;
  double score_ = 0;
  int currentLevel_ = 0;
  Level level_ = Level(currentLevel_);
  std::weak_ptr<Player> player_ = level_.getPlayer(); 

  /** The display window. */
  SDL_Window* window_ = nullptr;

  /** The display rendering tool. */
  SDL_Renderer* renderer_ = nullptr;

  /** The collection of images. */
  std::vector<SDL_Texture*> images_;

  /** The width of the window. */
  const int width_ = 1080;

  /** The height of the window. */
  const int height_ = 720;

  /**
   * Clear the background to opaque white.
   */
  void clearBackground();
};
}

#endif
