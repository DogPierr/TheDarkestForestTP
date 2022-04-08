#ifndef GAME_ON_SFML_SOURCES_MORTAL_H_
#define GAME_ON_SFML_SOURCES_MORTAL_H_

#include "SFML/Graphics.hpp"
#include "entity.h"

class Mortal : public Entity {
 public:
  float health_;

  Mortal() : health_bar_(sf::Vector2f(health_bar_width_, health_bar_height_)) {
    health_bar_.setFillColor(sf::Color::Green);
  }

  void Draw(sf::RenderWindow& window, GameState* gameState) override {
    if (!gameState->IsVisible(x_, y_)) {
      return;
    }
    graphics_->SetBlackout(gameState->GetIntencityRatio(x_, y_));
    graphics_->Draw(window, gameState, x_, y_);
    DrawHealthBar(window);
  }

  void Die() {
    if (!is_dead_) {
      graphics_->ChangeState("die");
      is_dead_ = true;
    }
    if (graphics_->IsAnimationFinished()) {
      is_full_dead_ = true;
    }
    graphics_->ChangeState("die");
  }

  bool IsDead() {
    return is_full_dead_;
  }

 private:
  const int health_bar_width_ = 20;
  const int health_bar_height_ = 5;

  sf::RectangleShape health_bar_;

  float GetHealthRatio() { return health_ / max_health_; }

 protected:
  bool is_dead_, is_full_dead_;
  float max_health_;

  void DrawHealthBar(sf::RenderWindow& window) {
    float ratio = GetHealthRatio();
    health_bar_.setPosition(x_, y_);
    if (health_ <= 0) {
      health_bar_.setScale(0, 1);
    } else {
      health_bar_.setScale(2 * ratio, 1);
    }
    window.draw(health_bar_);
  }
};

#endif  // GAME_ON_SFML_SOURCES_MORTAL_H_
