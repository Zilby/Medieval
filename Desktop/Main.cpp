#include <ctime>
#include <iostream>
#include <stdexcept>

#include "Sprites.h"
#include "Display.h"

using namespace std;
using namespace ping;

/**
 * @namespace ping The ping package displays a box
 * full of bouncing and rotating images.  The
 * images have random sizes.  They are initially
 * placed randomly in the box with random
 * velocities.  The images then evolve by bouncing
 * elastically against each other and the walls.
 * The mass of an image is its area.  The elastic
 * collisions preserve both linear and angular
 * momentum so that the energy is conserved.
 *
 * @author Ken Baclawski
 */

/**
 * Main program for the bouncing image display.
 * @return The status code. Status code 0 means
 * the program succeeds, and nonzero status code
 * means the program failed.
 */
int main() {
  try {

    // Initialize the graphical display

    Display display;

    // Add some images to the display

    display.addImage("full-portrait.bmp");
    display.addImage("full-portrait_1_.bmp");

    // Construct the sprite collection

    Sprites sprites(display.getImageCount());

    // Run until quit.
    
    for (;;) {
      
      // Check for relevant events.
      
      switch (display.checkForRelevantEvent()) {
      case RelevantEvent::NONE:
        break;
      case RelevantEvent::QUIT:
        return 0;
      default:
	cerr << "Unexpected event" << endl;
	return 1;
      }
      
      // Move the sprites and draw the new ones.

      sprites.evolve();
      display.refresh(sprites);
    }
  } catch (const exception& e) {
    cerr << e.what() << endl;
    return 1;
  }
}
