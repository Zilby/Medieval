#include "World.h"

using namespace std;
using namespace medieval;

/**
 * @namespace medieval This package is a 2D platforming game
 * titled Torbjorn's bizarre adventure. It features conventional
 * platforming gameplay with coins and health pickups as well as pits
 * and obstacles. 
 *
 * @author Alexander Zilbersher
 */

/**
 * The main program for our task. This adds all of our images
 * and creates our world. It checks for relevant events to exit. 
 * @return the exit status. Normal status is 0. 
 */

int main() {
  try {

    // Initialize the world

    World world;

    // Add our images to the display

    world.addImage("graphics/background.bmp");
    world.addImage("graphics/title.bmp");
    world.addImage("graphics/playerr.bmp");
    world.addImage("graphics/playerl.bmp");
    world.addImage("graphics/platform.bmp");
    world.addImage("graphics/obstacle.bmp");
    world.addImage("graphics/balls.bmp");
    world.addImage("graphics/pickuph.bmp");
    world.addImage("graphics/pickupc.bmp");
    world.addImage("graphics/lives.bmp");
    world.addImage("graphics/gameover.bmp");
    world.addImage("graphics/win.bmp");

    // Run until quit.
    
    for (;;) {
      
      // Check for relevant events.
      
      switch (world.checkForRelevantEvent()) {
      case RelevantEvent::NONE:
        break;
      case RelevantEvent::QUIT:
        return 0;
      default:
	cerr << "Unexpected event" << endl;
	return 1;
      }
      
      world.refresh();
    }
  } catch (const exception& e) {
    cerr << e.what() << endl;
    return 1;
  }
  
  return 0;
}
