#ifndef PING_DISPLAY_H
#define PING_DISPLAY_H

#include <vector>
#include "RelevantEvent.h"

class SDL_Window;
class SDL_Renderer;
class SDL_Texture;

namespace ping {

/**
 * SDL Display.  The purpose of this class is to
 * encapsulate all uses of SDL2 by this program.
 * Note that SDL.h was not included so that other
 * classes will not have direct access to SDL2.
 * All uses of SDL2 must be made through this
 * class.
 *
 * @author Ken Baclawski
 */
class Display {
public:
  /**
   * Create a graphical display with specified size.
   * @throw domain_error if the display could not
   * be created and initialized.
   */
  Display(/** Display width. */ int width = 640,
	  /** Display height. */ int height = 480);

  /**
   * Destruct the graphical display.  This closes
   * the display.
   */
  ~Display();

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
   * Get the number of images.
   */
  unsigned int getImageCount() const noexcept;

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
  void refresh(/** The sprites to display. */ 
	       const Sprites& sprites);

private:
  /** The display window. */
  SDL_Window* window_ = nullptr;

  /** The display rendering tool. */
  SDL_Renderer* renderer_ = nullptr;

  /** The collection of images. */
  std::vector<SDL_Texture*> images_;

  /** The width of the window. */
  const int width_ = 0;

  /** The height of the window. */
  const int height_ = 0;

  /**
   * Clear the background to opaque white.
   */
  void clearBackground();
};

}

#endif
