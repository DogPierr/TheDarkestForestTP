#ifndef GAMEPROJECTTP_SOURCES_PLAYER_H_
#define GAMEPROJECTTP_SOURCES_PLAYER_H_

#include "SFML/Graphics.hpp"
#include "cmath"
#include "entity.h"
#include "iostream"
#include "player_graphics.h"
#include "static_graphics.h"
#include "unit.h"

class Player : public Unit {
 public:
  Player(float x, float y, float h, float w, float speed) : Unit() {
    graphics_ = new PlayerGraphics;
    health_ = 100;
    max_health_ = health_;
    is_attacking_ = false;
    is_dead_ = false;
    is_full_dead_ = false;
    damage_ = 10;
    x_ = x;
    y_ = y;
    speed_ = speed;
    line_of_sight_ = {1, 0};
  }

  void Attack(Unit* enemy) {
    std::vector<float> radius_vector(2);
    radius_vector[0] = enemy->x_ - x_;
    radius_vector[1] = enemy->y_ - y_;
    float distance = sqrt((enemy->x_ - x_) * (enemy->x_ - x_) +
                          (enemy->y_ - y_) * (enemy->y_ - y_));
    float angle = (line_of_sight_[0] * radius_vector[0] +
                   line_of_sight_[1] * radius_vector[1]) /
                  distance;
    if (is_attacking_ && graphics_->IsAnimationFinished() &&
        angle >= 0 && distance <= 50) {
      enemy->health_ -= damage_;
    }
  }

  void Update(float time) override {
    KeyboardRead();
    if (!is_full_dead_) {
      graphics_->ChangeFrame(time);
    }
  }

  void Act(GameState* gameState) override {
    if (health_ <= 0) {
      speed_ = 0;
      Die();
      return;
    }
    health_ -= gameState->GetPlayerDamage();
    gameState->GetPlayerData(x_, y_, is_attacking_, graphics_->IsAnimationFinished(), line_of_sight_);
  }

  ~Player() {}

 private:
  void KeyboardRead() {
    if (!is_dead_) {
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !is_attacking_) {
        line_of_sight_ = {0, -1};
        y_ -= speed_;
        graphics_->MoveInDirectionAnimation(line_of_sight_);
      }
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !is_attacking_) {
        line_of_sight_ = {0, 1};
        y_ += speed_;
        graphics_->MoveInDirectionAnimation(line_of_sight_);
      }
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !is_attacking_) {
        line_of_sight_ = {1, 0};
        x_ += speed_;
        graphics_->MoveInDirectionAnimation(line_of_sight_);
      }
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !is_attacking_) {
        line_of_sight_ = {-1, 0};
        x_ -= speed_;
        graphics_->MoveInDirectionAnimation(line_of_sight_);
      }
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        graphics_->AttackAnimation();
        is_attacking_ = true;
      }
      if (!IsKeyPressed() ||
          (IsKeyPressed() && !sf::Keyboard::isKeyPressed(sf::Keyboard::Space) &&
           is_attacking_)) {
        graphics_->StayAnimation();
        is_attacking_ = false;
      }
    }
  }

  static bool IsKeyPressed() {
    return sf::Keyboard::isKeyPressed(sf::Keyboard::W) ||
           sf::Keyboard::isKeyPressed(sf::Keyboard::S) ||
           sf::Keyboard::isKeyPressed(sf::Keyboard::D) ||
           sf::Keyboard::isKeyPressed(sf::Keyboard::A) ||
           sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
  }
};

#endif  // GAMEPROJECTTP_SOURCES_PLAYER_H_
