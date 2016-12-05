#include "World.h"

using namespace std;
using namespace medieval;

/**
 * @namespace medieval Blah
 *
 * @author Alexander Zilbersher
 */

/**
 * The main program for our task. 
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
