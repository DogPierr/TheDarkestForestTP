#ifndef GAME_ON_SFML_FIRE_H
#define GAME_ON_SFML_FIRE_H

#include "mortal.h"
#include "static_graphics.h"

class Fire : public Mortal {
 public:
  Fire()
      : background("../sources/images/background.png"), frame("../sources/images/frame.png") {
    health_ = 50;
    max_health_ = health_;
    graphics_.state_ = "burn";
    graphics_.states_["burn"] = 0;
    x_ = -96;
    y_ = -96;
    h_ = 64;
    w_ = 64;
    GenerateFrames();
    graphics_.sprite_.setTextureRect(graphics_.frames_[0][0]);
  }

  void GenerateFrames() {
    graphics_ = DynamicGraphics("../sources/images/CampFire.png");
    graphics_.sprite_.setTexture(graphics_.texture_);
    graphics_.sprite_.setScale(3, 3);
    graphics_.frames_.emplace_back(0);
    for (int j = 0; j < 5; ++j) {
      graphics_.frames_[0].push_back(sf::IntRect (j * 64, 0, 64, 64));
    }
  }

  bool IsInRadius(Entity* entity) {
    float distance = entity->x_ * entity->x_ + entity->y_ * entity->y_;
    return distance < radius * radius;
  }

  void DrawBackground(sf::RenderWindow& window) {
    background.Draw(window, -500, -500);
  }

  void DrawFrame(sf::RenderWindow& window) { frame.Draw(window, -500, -500); }

  void Update(float time) override { graphics_.ChangeFrame(time); }

 private:
  float radius = 450;
  Graphics background;
  Graphics frame;
};

#endif  // GAME_ON_SFML_FIRE_H
