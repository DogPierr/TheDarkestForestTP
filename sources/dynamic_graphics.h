#ifndef GAME_ON_SFML_SOURCES_GRAPHICS_H_
#define GAME_ON_SFML_SOURCES_GRAPHICS_H_

#include <map>

#include "SFML/Graphics.hpp"
#include "static_graphics.h"

class DynamicGraphics : public Graphics {
 public:
  DynamicGraphics()
      : frames_(0),
        inverse_frames_(0),
        is_inverse_(false),
        state_("stay"),
        states_() {}

  DynamicGraphics(const std::string& image)
      : Graphics(image),
        frames_(0),
        inverse_frames_(0),
        is_inverse_(false),
        state_(""),
        states_() {}

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

  void ChangeState(std::string&& state) {
    if (state != state_) {
      fps_ = 15;
      current_frame_ = 0;
      state_ = std::move(state);
    }
  }

  bool IsAnimationFinished() {
    if (static_cast<int>(current_frame_) ==
        frames_[states_[state_]].size() - 1) {
      current_frame_ = 0;
      return true;
    }
    return static_cast<int>(current_frame_) ==
           frames_[states_[state_]].size() - 1;
  }

  virtual void GenerateFrames() = 0;
  virtual void MoveInDirectionAnimation(std::vector<float>& line_of_sight) {}
  virtual void AttackAnimation() {}
  virtual void StayAnimation() {}

 protected:
  std::vector<std::vector<sf::IntRect>> frames_, inverse_frames_;
  bool is_inverse_ = false;
  float fps_ = 5, current_frame_ = 0;
  std::string state_;
  std::map<std::string, int> states_;
};

#endif  // GAME_ON_SFML_SOURCES_GRAPHICS_H_
