#ifndef THEDARKESTFOREST_SOURCES_FIRE_GRAPHICS_H_
#define THEDARKESTFOREST_SOURCES_FIRE_GRAPHICS_H_

#include "dynamic_graphics.h"

class FireGraphics : public DynamicGraphics {
 public:
  FireGraphics() : DynamicGraphics("../sources/images/CampFire.png") {
    sprite_.setTexture(texture_);
    sprite_.setScale(3, 3);
    GenerateFrames();
    state_ = "burn";
    states_["burn"] = 0;
    sprite_.setTextureRect(frames_[0][0]);
  }

  void GenerateFrames() override {
    for (int j = 0; j < 5; ++j) {
      frames_.emplace_back(0);
      frames_[0].push_back(sf::IntRect (j * 64, 0, 64, 64));
    }
  }
};

#endif //THEDARKESTFOREST_SOURCES_FIRE_GRAPHICS_H_
