#ifndef GAME_ON_SFML_SOURCES_WATER_SLIME_H_
#define GAME_ON_SFML_SOURCES_WATER_SLIME_H_

#include "SFML/Graphics.hpp"
#include "cmath"
#include "entity.h"
#include "map.h"
#include "player.h"
#include "slime_graphics.h"

class WaterSlime : public Unit {
public:
  WaterSlime(float x, float y, float h, float w, float speed) : Unit() {
    graphics_ = new SlimeGraphics;
    line_of_sight_ = {1, 0};
    health_ = 20;
    max_health_ = health_;
    damage_ = 5;
    x_ = x;
    y_ = y;
    speed_ = speed;
    is_attacking_ = false;
  }

  void Update(float time) {
    if (!is_full_dead_) {
      graphics_->ChangeFrame(time);
    }
  }

  void Act(GameState *gameState) override {
    if (health_ <= 0) {
      speed_ = 0;
      Die();
      return;
    }
    auto [is_attacking, target_x, target_y] = gameState->SetSlimeTarget(x_, y_);
    is_attacking = is_attacking_;
    target_x_ = target_x;
    target_y_ = target_y;
    MoveToTarget();
    if (is_attacking_) {
      Attack();
    }
    health_ -= gameState->SlimeDamage(x_, y_);
  }

private:
  const float radius = 100;
  int damage_;

  void MoveToTarget() {
    float cos_alpha = ScalarProduct()[0];
    float sin_alpha = ScalarProduct()[1];
    float s = ScalarProduct()[2];

    SetDirection(cos_alpha);
    graphics_->MoveInDirectionAnimation(line_of_sight_);

    if (is_attacking_)
      return;

    float dx_ = speed_ * cos_alpha;
    float dy_ = speed_ * sin_alpha;

    x_ += dx_;
    y_ += dy_;
  }

  void Attack() {
    if (is_attacking_) {
      graphics_->AttackAnimation();
      return;
    }
  }

  std::vector<float> ScalarProduct() {
    float s = sqrt((target_y_ - y_) * (target_y_ - y_) +
                   (target_x_ - x_) * (target_x_ - x_));
    float cos_alpha = (target_x_ - x_) / s;
    float sin_alpha = (target_y_ - y_) / s;

    return {cos_alpha, sin_alpha, s};
  }

  void SetDirection(float cos_alpha) {
    if (cos_alpha < 0) {
      line_of_sight_ = {-1, 0};
    } else {
      line_of_sight_ = {1, 0};
    }
  }

  float target_x_;
  float target_y_;
  bool is_attacking_;
};

#endif // GAME_ON_SFML_SOURCES_WATER_SLIME_H_