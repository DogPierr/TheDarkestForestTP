#ifndef GAME_ON_SFML_SOURCES_WATER_SLIME_H_
#define GAME_ON_SFML_SOURCES_WATER_SLIME_H_

#include "map.h"
#include "entity.h"
#include "slime_graphics.h"
#include "cmath"
#include "player.h"
#include "SFML/Graphics.hpp"

class WaterSlime : public Unit {
 public:
  WaterSlime(float x, float y, float h, float w, float speed) : Unit() {
    graphics_ = new SlimeGraphics;
    line_of_sight_ = {1, 0};
    health_ = 20;
    max_health_ = health_;
    damage_ = 5;
    target_ = nullptr;
    x_ = x;
    y_ = y;
    speed_ = speed;
    is_attacking_ = false;
  }

  void Update(float time) override {
    if (health_ <= 0) {
      speed_ = 0;
      Die();
    } else {
      if (target_ != nullptr) {
        MoveToTarget();
      }
      if (target_->health_ <= 0) {
        target_ = nullptr;
      }
    }
    if (!is_full_dead_) {
      graphics_->ChangeFrame(time);
    }
  }

  void SetTarget(Mortal* target) {
    target_ = target;
  }

  bool IsInRadius(Entity* entity) {
    float distance = sqrt((entity->x_ - x_) * (entity->x_ - x_) + (entity->y_ - y_) * (entity->y_ - y_));
    return distance < radius;
  }

 private:
  const float radius = 100;
  bool is_attacking_;
  int damage_;
  Mortal* target_;

  void MoveToTarget() {
    float cos_alpha = ScalarProduct()[0];
    float sin_alpha = ScalarProduct()[1];
    float s = ScalarProduct()[2];

    SetDirection(cos_alpha);
    graphics_->MoveInDirectionAnimation(line_of_sight_);

    if (s < 50) {
      Attack();
      return;
    }
    is_attacking_ = false;

    float dx_ = speed_ * cos_alpha;
    float dy_ = speed_ * sin_alpha;

    x_ += dx_;
    y_ += dy_;
  }

  void Attack() {
    if (is_attacking_) {
      if (graphics_->IsAnimationFinished()) {
        target_->health_ -= damage_;
      }
      return;
    }
    graphics_->AttackAnimation();
    is_attacking_ = true;
  }

  std::vector<float> ScalarProduct() {
    float s = sqrt((target_->y_ - y_) * (target_->y_ - y_) + (target_->x_ - x_) * (target_->x_ - x_));
    float cos_alpha = (target_->x_ - x_) / s;
    float sin_alpha = (target_->y_ - y_) / s;

    return {cos_alpha, sin_alpha, s};
  }

  void SetDirection(float cos_alpha) {
    if (cos_alpha < 0) {
      line_of_sight_ = {-1, 0};
    } else {
      line_of_sight_ = {1, 0};
    }
  }

};

#endif //GAME_ON_SFML_SOURCES_WATER_SLIME_H_