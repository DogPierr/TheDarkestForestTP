#ifndef GAME_ON_SFML_STATIC_GRAPHICS_H
#define GAME_ON_SFML_STATIC_GRAPHICS_H

#include "SFML/Graphics.hpp"
#include "game_state.h"

class Graphics {
 public:
  Graphics() = default;

  Graphics(const std::string& image) {
    texture_.loadFromFile(image);
    sprite_.setTexture(texture_);
  }

  Graphics(const sf::Color& color) {
    sprite_.setColor(color);
  }

  void SetScale(float number) {
    sprite_.setScale(number, number);
  }

  void SetBlackout(float ratio) {
    if (ratio < 1) {
      sprite_.setColor(sf::Color(255 * (1 - ratio), 255 * (1 - ratio), 255 * (1 - ratio)));
      return;
    }
    sprite_.setColor(sf::Color(0, 0, 0));
  }

  virtual void Draw(sf::RenderWindow& window, GameState* gameState, float x, float y) {
    sprite_.setPosition(x, y);
    window.draw(sprite_);
  }

 protected:
  sf::Texture texture_;
  sf::Sprite sprite_;
};

#endif  // GAME_ON_SFML_STATIC_GRAPHICS_H
