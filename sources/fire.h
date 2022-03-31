#ifndef GAME_ON_SFML_FIRE_H
#define GAME_ON_SFML_FIRE_H

#include "mortal.h"
#include "fire_graphics.h"
#include "static_graphics.h"

class Fire : public Mortal {
 public:
  Fire()
      : background("../sources/images/background.png"), frame("../sources/images/frame.png") {
    graphics_ = new FireGraphics;
    health_ = 50;
    max_health_ = health_;
    x_ = -96;
    y_ = -96;
  }

  bool IsInRadius(Entity* entity) {
    float distance = entity->x_ * entity->x_ + entity->y_ * entity->y_;
    return distance < radius * radius;
  }

  void DrawBackground(sf::RenderWindow& window) {
    background.Draw(window, -500, -500);
  }

  void DrawFrame(sf::RenderWindow& window) { frame.Draw(window, -500, -500); }

  void Update(float time) override { graphics_->ChangeFrame(time); }

 private:
  float radius = 450;
  Graphics background;
  Graphics frame;
};

#endif  // GAME_ON_SFML_FIRE_H
