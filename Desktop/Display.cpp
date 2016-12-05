#include <SDL2/SDL.h>
#include <stdexcept>
#include <iostream>

#include "Sprite.h"
#include "Sprites.h"
#include "Display.h"

using namespace std;
using namespace ping;

Display::Display(int width, int height)
  : width_(width), height_(height) {

  // Initialize SDL2

  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    throw domain_error(string("SDL Initialization failed due to: ") + SDL_GetError());
  }

  // Construct the screen window

  window_ = SDL_CreateWindow("Display", SDL_WINDOWPOS_UNDEFINED, 
                             SDL_WINDOWPOS_UNDEFINED, 
                             width_, height_, SDL_WINDOW_SHOWN);
  if (!window_) {
    close();
    throw domain_error(string("Unable to create the window due to: ") + SDL_GetError());
  }

  // Construct the renderer

  renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (!renderer_) {
    close();
    throw domain_error(string("Unable to create the renderer due to: ") + SDL_GetError());
  }

  // Clear the window

  clearBackground();
}

Display::~Display() {
  close();
}

void Display::close() noexcept {

  // Delete the SDL2 resources in reverse order of
  // their construction, starting with the images

  for (SDL_Texture* image : images_) {
    if (image) {
      SDL_DestroyTexture(image);
    }
  }

  // Clear the collection of images to ensure
  // idempotence

  images_.clear();

  // Destroy the renderer and window, and set the
  // variables to nullptr to ensure idempotence

  if (renderer_) {
    SDL_DestroyRenderer(renderer_);
    renderer_ = nullptr;
  }
  if (window_) {
    SDL_DestroyWindow(window_);
    window_ = nullptr;
  }

  // The last step is to quit SDL

  SDL_Quit();
}

void Display::addImage(const string& fileLocation) noexcept {
  if (renderer_) {

    // Load the image from the file

    SDL_Surface* imageSurface = SDL_LoadBMP(fileLocation.c_str());
    if (imageSurface) {

      // Convert the image to a texture

      SDL_Texture* imageTexture = 
	SDL_CreateTextureFromSurface(renderer_, imageSurface);
      if (imageTexture) {

	// Add the image to the collection

        images_.push_back(imageTexture);
      } else {
        cerr << "Unable to load the image file at " << fileLocation
             << " due to: " << SDL_GetError() << endl;
      } 

      // The surface is not longer needed

      SDL_FreeSurface(imageSurface);
    } else {
      cerr << "Unable to load the image file at " << fileLocation
           << " due to: " << SDL_GetError() << endl;
    }
  }
}

unsigned int Display::getImageCount() const noexcept {
  return images_.size();
}

RelevantEvent Display::checkForRelevantEvent() noexcept {

  // Remove all events from the queue

  SDL_Event event;
  while (SDL_PollEvent(&event) != 0) {
    if (event.type == SDL_QUIT) {

      // If the window is Xed out, close the
      // window and return the quit event

      close();
      return RelevantEvent::QUIT;
    }
  }

  // Ignore all other events

  return RelevantEvent::NONE;
}

void Display::refresh(const Sprites& sprites) {
  if (renderer_) {

    // Clear the window
    
    clearBackground();

    // Draw all of the sprites

    for (const Sprite& sprite : sprites.getList()) {

      // The location of the sprite is a square

      SDL_Rect destination = { sprite.getXCoordinate(), sprite.getYCoordinate(), 
                               sprite.getDiameter(), sprite.getDiameter() };

      // Get the image index and check that it is valid

      unsigned int imageIndex = sprite.getImageIndex();
      if (imageIndex >= 0 && imageIndex < images_.size()) {

	// Get the image for the sprite

        SDL_Texture* imageTexture = images_.at(imageIndex);
        if (imageTexture) {

	  // Render the image at the location,
	  // rotated by its angle

          if (SDL_RenderCopyEx(renderer_, imageTexture, nullptr,
                               &destination, sprite.getAngle(), 
                               nullptr, SDL_FLIP_NONE) != 0) {
            close();
            throw domain_error(string("Unable to render a sprite due to: ")
                               + SDL_GetError());
          }
        } else {
	  close();
          throw domain_error("Missing image texture at index "
                             + to_string(imageIndex));          
        }
      } else {
	close();
        throw domain_error("Invalid image index " 
                           + to_string(imageIndex));
      }
    }
    SDL_RenderPresent(renderer_);
  }
}

void Display::clearBackground() {
  if (renderer_) {
    
    // Clear the window to opaque white
    
    if (SDL_SetRenderDrawColor(renderer_, 0xff, 0xff, 0xff, 0xff) != 0) {
      close();
      throw domain_error(string("Unable to set the background color due to: ")
                         + SDL_GetError());
    }
    if (SDL_RenderClear(renderer_) != 0) {
      close();
      throw domain_error(string("Unable to set the background color due to: ")
                         + SDL_GetError());
    }
  }
}
