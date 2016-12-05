#include <vector>
#include <random>
#include <stdexcept>

#include "Sprite.h"

using namespace std;
using namespace ping;

Sprite::Sprite(std::mt19937& engine, unsigned int imageCount,
	       double minDiameter, double maxDiameter,
	       int width, int height) : 

  // Construct the probability distributions

  realDistribution_(0.0, 1.0),
  integerDistribution_(0, imageCount - 1),

  // Randomly select a radius between
  // minDiameter/2 and maxDiameter/2

  radius_{(minDiameter + realDistribution_(engine) * (maxDiameter - minDiameter)) * 0.5},
  radius2_{radius_ * radius_},

  // Initialize the width and height of the window

  width_{width},
  height_{height},

  // Select a random image for the sprite

  imageIndex_{integerDistribution_(engine)},

  // Select random linear and angular velocities

  vx_{realDistribution_(engine) * 1000.00 - 500.0},
  vy_{realDistribution_(engine) * 1000.00 - 500.0},
  rot_{realDistribution_(engine) * 1000.00 - 500.0}
 {

   // Check that the diameters are meaningful

   if (minDiameter < 1.0 || maxDiameter < minDiameter) {
     throw domain_error("Invalid sprite diameter range: from " +
			to_string(minDiameter) + " to " +
			to_string(maxDiameter));
   }

   // Check that the screen dimensions are valid

   if (width_ <= 0 || height_ <= 0) {
     throw domain_error("Invalid screen dimension: " +
			to_string(width_) + " x " +
			to_string(height_));
   }
 } 

int Sprite::getXCoordinate() const noexcept {
  return int(cx_ - radius_ + 0.5);
}

int Sprite::getYCoordinate() const noexcept {
  return int(cy_ - radius_ + 0.5);
}

int Sprite::getDiameter() const noexcept {
  return int(2.0 * radius_ + 0.5);
}

double Sprite::getAngle() const noexcept {
  return angle_;
}

int Sprite::getImageIndex() const noexcept {
  return imageIndex_;
}

void Sprite::chooseRandomLocation(std::mt19937& engine) noexcept {
  cx_ = radius_ + realDistribution_(engine) * (width_ - 2 * radius_);
  cy_ = radius_ + realDistribution_(engine) * (height_ - 2 * radius_);
}

void Sprite::move(double delta) noexcept {

  // Update the position and angle

  cx_ += delta * vx_;
  cy_ += delta * vy_;
  angle_ += delta * rot_;

  // Bounce against walls

  if (cx_ < radius_) {
    cx_ = 2 * radius_ - cx_;
    vx_ = -vx_;
  }
  if (cy_ < radius_) {
    cy_ = 2 * radius_ - cy_;
    vy_ = -vy_;
  }
  if (cx_ > width_ - radius_) {
    cx_ = 2 * (width_ - radius_) - cx_;
    vx_ = -vx_;
  }
  if (cy_ > height_ - radius_) {
    cy_ = 2 * (height_ - radius_) - cy_;
    vy_ = -vy_;
  }
}

void Sprite::clearBounce() noexcept {
  bounced_ = false;
}

void Sprite::bounce(Sprite& other) noexcept {

  // If one of the sprites has already bounced,
  // then do not bounce either one again

  if (bounced_ || other.bounced_) {
    return;
  }

  // If the sprites do not hit each other, then do
  // not bounce them

  if (!hits(other)) {
    return;
  }
  
  // Neither sprite has already bounced, and they
  // are hitting each other.
  
  bounced_ = true;
  other.bounced_ = true;
  
  // Get the masses and deltas.
  
  double m1 = radius2_;
  double m2 = other.radius2_;
  double dx = other.cx_ - cx_;
  double dy = other.cy_ - cy_;
  bool collided = false;

  // They are colliding in this coordinate only if
  // they are approaching each other.
  
  if ((dx >= 0.0 && vx_ > other.vx_) || (dx < 0.0 && vx_ < other.vx_)) {
    
    // Standard formula for an elastic collision.
    
    double vx1 = ((m1 - m2) * vx_ + 2 * m2 * other.vx_) / (m1 + m2);
    double vx2 = (2 * m1 * vx_ + (m2 - m1) * other.vx_) / (m1 + m2);
    vx_ = vx1;
    other.vx_ = vx2;
    collided = true;
  }
  
  // Do the same for the y coordinate.
  
  if ((dy >= 0.0 && vy_ > other.vy_) || (dy < 0.0 && vy_ < other.vy_)) {
    
    // Standard formula for an elastic collision.
    
    double vy1 = ((m1 - m2) * vy_ + 2 * m2 * other.vy_) / (m1 + m2);
    double vy2 = (2 * m1 * vy_ + (m2 - m1) * other.vy_) / (m1 + m2);
    vy_ = vy1;
    other.vy_ = vy2;
    collided = true;
  }

  // Finally, if they collided, then use the same formula for the rotation
  // rates, but using the moment of inertia rather than the mass.

  double mi1 = m1 * radius2_;
  double mi2 = m2 * other.radius2_;
  if (collided) {
    double vrot1 = ((mi1 - mi2) * rot_ + 2 * mi2 * other.rot_) / (mi1 + mi2);
    double vrot2 = (2 * mi1 * rot_ + (mi2 - mi1) * other.rot_) / (mi1 + mi2);
    rot_ = vrot1;
    other.rot_ = vrot2;
  }
}

bool Sprite::hits(const Sprite& other) const noexcept {
  double dx = other.cx_ - cx_;
  double dy = other.cy_ - cy_;
  double dist2 = dx * dx + dy * dy;
  return (dist2 < (other.radius_ + radius_) * (other.radius_ + radius_));
}
