#ifndef THEDARKESTFOREST_SOURCES_SLIME_GRAPHICS_H_
#define THEDARKESTFOREST_SOURCES_SLIME_GRAPHICS_H_

#include "dynamic_graphics.h"

class SlimeGraphics : public DynamicGraphics {
 public:
  SlimeGraphics() : DynamicGraphics("../sources/images/water_slime.png") {
    sprite_.setTexture(texture_);
    sprite_.setScale(3, 3);
    GenerateFrames();
    states_["walk"] = 2;
    states_["attack"] = 3;
    states_["die"] = 4;
    sprite_.setTextureRect(frames_[2][0]);
  }

  void GenerateFrames() {
    for (int j = 0; j < 5; ++j) {
      inverse_frames_.emplace_back(0);
      for (int i = 0; i < 10; ++i) {
        inverse_frames_[j].push_back(sf::IntRect(10 + i * 32, 172 + j * 32, 12, 20));
      }
    }
    for (int j = 0; j < 5; ++j) {
      frames_.emplace_back(0);
      for (int i = 0; i < 10; ++i) {
        frames_[j].push_back(sf::IntRect(10 + i * 32 + 12, 172 + j * 32, -12, 20));
      }
    }
  }
};


#endif //THEDARKESTFOREST_SOURCES_SLIME_GRAPHICS_H_
