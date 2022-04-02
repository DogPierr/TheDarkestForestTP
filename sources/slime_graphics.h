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

  void MoveInDirectionAnimation(std::vector<float>& line_of_sight) override {
    if (line_of_sight == std::vector<float>{0, -1} or line_of_sight == std::vector<float>{0, 1}) {
      state_ = "walk";
      fps_ = 5;
    }
    if (line_of_sight == std::vector<float>{1, 0}) {
      state_ = "walk";
      fps_ = 5;
      is_inverse_ = false;
    }
    if (line_of_sight == std::vector<float>{-1, 0}) {
      state_ = "walk";
      fps_ = 5;
      is_inverse_ = true;
    }
  }

  void AttackAnimation() override {
    fps_ = 12;
    state_ = "attack";
  }
};


#endif //THEDARKESTFOREST_SOURCES_SLIME_GRAPHICS_H_
