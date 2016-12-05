#ifndef MEDIEVAL_BALLS_H
#define MEDIEVAL_BALLS_H

#include "Sprite.h"
#include <stdexcept>

namespace medieval {

class Balls : public Sprite {
  
public:

  Balls(int index, int x, int y, int start, int end, bool left);
    
  void move() noexcept override;
    
private:
  int start_;
  int end_;
  bool left_;
};
}

#endif
