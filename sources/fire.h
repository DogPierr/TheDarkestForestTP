#ifndef GAME_ON_SFML_FIRE_H
#define GAME_ON_SFML_FIRE_H

#include "fire_graphics.h"
#include "mortal.h"
#include "static_graphics.h"

class Fire : public Mortal {
 public:
  Fire() {
    graphics_ = new FireGraphics;
    max_health_ = health_ = 50;
    x_ = -96;
    y_ = -96;
  }

  void Update(float time) override { graphics_->ChangeFrame(time); }

  void Act(GameState* gameState) override {
    health_ -= gameState->GetFireDamage();
    if (health_ <= 0) exit(0);
  }

 private:
  float radius = 450;
};

#endif  // GAME_ON_SFML_FIRE_H
