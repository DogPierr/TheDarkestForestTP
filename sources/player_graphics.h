#ifndef THEDARKESTFOREST_SOURCES_PLAYER_GRAPHICS_H_
#define THEDARKESTFOREST_SOURCES_PLAYER_GRAPHICS_H_

#include "dynamic_graphics.h"

class PlayerGraphics: public DynamicGraphics {
 public:
  PlayerGraphics() : DynamicGraphics("../sources/images/rogue.png") {
    sprite_.setTexture(texture_);
    sprite_.setScale(3, 3);
    GenerateFrames();
    states_["stay"] = 0;
    states_["walk"] = 7;
    states_["attack"] = 8;
    states_["die"] = 9;frame;
    state_ = "stay";
    sprite_.setTextureRect(frames_[0][0]);
  }

  void GenerateFrames() override {
    for (int j = 0; j < 10; ++j) {
      frames_.emplace_back(0);
      for (int i = 0; i < 10; ++i) {
        frames_[j].push_back(
            sf::IntRect(9 + i * 32, 1 + j * 32, 20, 31));
      }
    }
    for (int j = 0; j < 10; ++j) {
      inverse_frames_.emplace_back(0);
      for (int i = 0; i < 10; ++i) {
        inverse_frames_[j].push_back(
            sf::IntRect(9 + i * 32 + 20, 1 + j * 32, -20, 31));
      }
    }
  }
};

#endif //THEDARKESTFOREST_SOURCES_PLAYER_GRAPHICS_H_
