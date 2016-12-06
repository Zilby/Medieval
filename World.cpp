#include "World.h"

using namespace std;
using namespace medieval;

World::World() {

  // Initialize SDL2

  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    throw domain_error(string("SDL Initialization failed due to: ") + SDL_GetError());
  }

  // Initialize ttf
  
  if (TTF_Init() < 0) {
    throw domain_error(string("TTF init failed"));
  }

  // Initialize our ttf font
  
  textColor_ = { 255, 255, 255, 0 };
  font_ = TTF_OpenFont("graphics/font.ttf", 50);
  if (!font_) {
    throw domain_error ("Couldn't find graphics/font.ttf");
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

World::~World() {
  close();
}

void World::close() noexcept {

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

  TTF_Quit();
  SDL_Quit();
}

void World::addImage(const string& fileLocation) noexcept {
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

RelevantEvent World::checkForRelevantEvent() noexcept {

  // Remove all events from the queue

  SDL_Event event;
  while (SDL_PollEvent(&event) != 0) {
    switch( event.type ){
      /* Look for a keypress */
    case SDL_QUIT:
      // If the window is Xed out, close the
      // window and return the quit event

      close();
      return RelevantEvent::QUIT;
    case SDL_KEYDOWN:
      switch( event.key.keysym.sym ){
	
	// moves player based on user input
      case SDLK_LEFT:
	left_ = true;
	right_ = false;
	(player_.lock())->setH(-8);
	break;
      case SDLK_RIGHT:
	left_ = false;
	right_ = true;
	(player_.lock())->setH(8);
	break;
      case SDLK_UP:
	(player_.lock())->jump();
	break;
      default:
	break;
      }
      break;
    case SDL_KEYUP:
      if(currentLevel_ == 0 || currentLevel_ == -1 || currentLevel_ == -2) {

	// progresses the game if on a menu screen and spacebar is clicked
	switch( event.key.keysym.sym ){
	case SDLK_SPACE:
	  ++currentLevel_;
	  if (currentLevel_ == -1) {
	    ++currentLevel_;
	  }
	  level_ = Level(currentLevel_);
	  player_ = level_.getPlayer();
	  right_ = false;
	  left_ = false;
	  break;
	default:
	  break;
	}
      }	else {
	switch( event.key.keysym.sym ){
	  
	  // stops movement of player based on user input
	case SDLK_LEFT:
	  left_ = false;
	  (player_.lock())->stopH();
	  break;
	case SDLK_RIGHT:
	  right_ = false;
	  (player_.lock())->stopH();
	  break;
	default:
	  break;
	}
	break;
      default:
	break;
      }
    }
  }
  // Ignore all other events
  
  return RelevantEvent::NONE;
}

void World::refresh() {
  if (renderer_) {
    
    // Clear the window
    
    clearBackground();

    // Game over if out of lives
    
    if(lives_ == 0) {
      currentLevel_ = -1;
      level_ = Level(currentLevel_);
      player_ = level_.getPlayer();
      lives_ = 5;
      health_ = 3;
    }
    // if on title screen
    if(currentLevel_ == 0) {
      // Draw the title screen
      
      draw(0, 0, 1080, 720, 1);
      score_ = 0; 
    } // if on game over screen
    else if(currentLevel_ == -1) {
      // Draw the game over screen
      
      draw(0, 0, 1080, 720, 10);
      // Draw score
      
      drawText(635, 590, to_string(score_), 2);
      
    } // if on win screen
    else if(currentLevel_ == -2) {
      // Draw the win screen
      
      draw(0, 0, 1080, 720, 11);
      // Draw score
      drawText(640, 400, to_string(score_), 3);

      // Draw high score
      drawText(900, 580, "High Score: " + to_string(highScore_), 2);
      
    } else {
      
      // Draw the background
      draw(0, 0, 1080, 720, 0);

      // Add to time
      ++timeCounter_;
      if(timeCounter_ > 40) {
	++time_;
	timeCounter_ = 0;
      }

      // Draw time
      drawText(1040, 10, "Time: " + to_string(time_), 1);
      
      // Draw lives
      for(int x = lives_; x > 0; --x) {
	draw((x * 55) - 40, 20, 50, 50, 9);
      }

      // Draw health
      for(int x = health_; x > 0; --x) {
	draw((x * 55) - 18, 70, 50, 50, 7);
      }

      // Draw score
      drawText(1040, 60, to_string(score_), 1);
			 
      // Move the player and all the other sprites
      if(left_) {
	(player_.lock())->setH(-8);
      } else if (right_) {
	(player_.lock())->setH(8);
      }
      level_.evolve();

      // If the player takes damage reduce one health
      if(level_.damaged()) {
	--health_;
	score_ -= 10;
      }

      // If the player picks up health, heal them
      if(level_.healed()) {
	if(health_ < 3) {
	  ++health_;
	}
      }

      // If the player picks up a coin, add score
      if(level_.scored()) {
	score_ += 25;
      }

      // If the player is dead reset health, reduce lives, lose score and reset player
      if(level_.dead() || health_ <= 0) {
	--lives_;
	health_ = 3;
	level_.resetPlayer();
	score_ -= 50;
      }
      
      // Draw all of the sprites

      for (const shared_ptr<Sprite>& sprite : level_.getList()) {
	
	// The location of the sprite is a square

	SDL_Rect destination = { sprite->getXCoordinate(), sprite->getYCoordinate(), 
				 sprite->getWidth(), sprite->getHeight() };

	// Get the image index and check that it is valid

	unsigned int imageIndex = sprite->getImageIndex();
	if (imageIndex >= 0 && imageIndex < images_.size()) {

	  // Get the image for the sprite

	  SDL_Texture* imageTexture = images_.at(imageIndex);
	  if (imageTexture) {

	    // Render the image at the location,
	    // rotated by its angle

	    if (SDL_RenderCopyEx(renderer_, imageTexture, nullptr,
				 &destination, sprite->getAngle(), 
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
    }
    SDL_RenderPresent(renderer_);
  }

  // if the next level is reached proceed to next level or
  // win screen if last level is reached
  if(level_.next()) {
      score_ += 100;
      if(currentLevel_ == 2) {
	currentLevel_ = -2;
	level_ = Level(currentLevel_);
	player_ = level_.getPlayer();
	score_ += (lives_ * 50) + (health_ * 10) + (100 - time_);
	if(highScore_ < score_) {
	  highScore_ = score_;
	}
	lives_ = 5;
	health_ = 3;
      } else {
	++currentLevel_;
	level_ = Level(currentLevel_);
	player_ = level_.getPlayer();
      }
    }
}

void World::clearBackground() {
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

void World::draw(int x, int y, int width, int height, int index) {
  SDL_Rect destination = { x, y, width, height };

  // Get the image for the background

  SDL_Texture* imageTexture = images_.at(index);
  if (imageTexture) {

    // Render the image at the location,
    // rotated by its angle

    if (SDL_RenderCopyEx(renderer_, imageTexture, nullptr,
			 &destination, 0, 
			 nullptr, SDL_FLIP_NONE) != 0) {
      close();
      throw domain_error(string("Unable to render a sprite due to: ")
			 + SDL_GetError());
    }
  } else {
    close();
    throw domain_error("Missing image texture at index "
		       + to_string(index));          
  }
}

void World::drawText(int x, int y, string text, int size) {
  SDL_Surface* textSurface = TTF_RenderText_Solid(font_, text.c_str(), textColor_);
  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer_, textSurface);
  int text_width = textSurface->w * size;
  int text_height = textSurface->h * size;
  SDL_FreeSurface(textSurface);
  SDL_Rect destination = { x - text_width, y, text_width, text_height };
  SDL_RenderCopy(renderer_, texture, NULL, &destination);
  SDL_DestroyTexture(texture);
}
