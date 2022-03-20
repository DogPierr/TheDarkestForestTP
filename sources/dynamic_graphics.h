#ifndef GAMEPROJECTTP_SOURCES_GRAPHICS_H_
#define GAMEPROJECTTP_SOURCES_GRAPHICS_H_

#include "SFML/Graphics.hpp"
#include "entity.h"
#include "static_graphics.h"
#include <map>

class DynamicGraphics : public Graphics {
 public:
  std::vector<std::vector<sf::IntRect>> frames_, inverse_frames_;
  bool is_inverse_ = false;
  sf::Sprite area_;
  float fps_ = 5, current_frame_ = 0;
  std::string state_;
  std::map<std::string, int> states_;

  DynamicGraphics()
      : frames_(0),
        inverse_frames_(0),
        is_inverse_(false),
        fps_(5),
        current_frame_(0),
        state_("stay"),
        states_() {}

  DynamicGraphics(const std::string& image)
      : Graphics(image), frames_(0), inverse_frames_(0), is_inverse_(false), state_(""), states_() {}

  void ChangeFrame(float time) {
    current_frame_ += fps_ * time;
    if (current_frame_ > frames_[states_[state_]].size()) {
      current_frame_ -= frames_[states_[state_]].size();
    }
    if (!is_inverse_) {
      sprite_.setTextureRect(frames_[states_[state_]][current_frame_]);
      return;
    }
    sprite_.setTextureRect(inverse_frames_[states_[state_]][current_frame_]);
  }
  
};

#endif  // GAMEPROJECTTP_SOURCES_GRAPHICS_H_
