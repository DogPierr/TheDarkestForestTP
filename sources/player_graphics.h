#ifndef THEDARKESTFOREST_SOURCES_PLAYER_GRAPHICS_H_
#define THEDARKESTFOREST_SOURCES_PLAYER_GRAPHICS_H_

#include "dynamic_graphics.h"

class PlayerGraphics : public DynamicGraphics {
public:
  PlayerGraphics()
      : DynamicGraphics("../sources/images/rogue.png"),
        background("../sources/images/background.png"),
        frame("../sources/images/frame.png") {
    sprite_.setTexture(texture_);
    sprite_.setScale(3, 3);
    background.SetScale(0.3);
    frame.SetScale(0.3);
    GenerateFrames();
    states_["stay"] = 0;
    states_["walk"] = 7;
    states_["attack"] = 8;
    states_["die"] = 9;
    state_ = "stay";
    sprite_.setTextureRect(frames_[0][0]);
  }

  void Draw(sf::RenderWindow &window, GameState *gameState, float x,
            float y) override {
    std::cout << gameState->IsPlayerOutside() << '\n';
    if (gameState->IsPlayerOutside()) {
      background.Draw(window, gameState, -102 + x, -102 + y);
      frame.Draw(window, gameState, -102 + x, -102 + y);
    }
    sprite_.setPosition(x, y);
    window.draw(sprite_);
  }

  void GenerateFrames() override {
    for (int j = 0; j < 10; ++j) {
      frames_.emplace_back(0);
      for (int i = 0; i < 10; ++i) {
        frames_[j].push_back(sf::IntRect(9 + i * 32, 1 + j * 32, 20, 31));
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

  void MoveInDirectionAnimation(std::vector<float> &line_of_sight) override {
    if (line_of_sight == std::vector<float>{0, -1} ||
        line_of_sight == std::vector<float>{0, 1}) {
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

  void StayAnimation() override {
    fps_ = 5;
    state_ = "stay";
  }

private:
  Graphics background;
  Graphics frame;
};

#endif // THEDARKESTFOREST_SOURCES_PLAYER_GRAPHICS_H_
