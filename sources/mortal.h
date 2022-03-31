#ifndef GAME_ON_SFML_SOURCES_MORTAL_H_
#define GAME_ON_SFML_SOURCES_MORTAL_H_

#include "SFML/Graphics.hpp"
#include "entity.h"

class Mortal : public Entity {
 public:
  float health_;
  float max_health_;
  bool is_dead_, is_full_dead_;

  Mortal(): health_bar_(sf::Vector2f(health_bar_width_, health_bar_height_)) {
    health_bar_.setFillColor(sf::Color::Green);
  }

  void Draw(sf::RenderWindow& window) {
    float ratio = GetHealthRatio();
    health_bar_.setPosition(x_, y_);
    if (health_ <= 0) {
      health_bar_.setScale(0, 1);
    }
    else {
      health_bar_.setScale(2 * ratio, 1);
    }
    window.draw(health_bar_);
    graphics_->Draw(window, x_, y_);
  }

  void Die() {
    if (!is_dead_) {
      graphics_->current_frame_ = 0;
      is_dead_ = true;
    }
    if (static_cast<int>(graphics_->current_frame_) == 9) {
      is_full_dead_ = true;
    }
    graphics_->state_ = "die";
  }

 private:
  const int health_bar_width_ = 20;
  const int health_bar_height_ = 5;

  sf::RectangleShape health_bar_;

  float GetHealthRatio() {
    return health_ / max_health_;
  }

};

#endif //GAME_ON_SFML_SOURCES_MORTAL_H_
