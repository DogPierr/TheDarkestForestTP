#ifndef GAME_ON_SFML_STATIC_GRAPHICS_H
#define GAME_ON_SFML_STATIC_GRAPHICS_H

#include "SFML/Graphics.hpp"

class Graphics {
 public:
  sf::Texture texture_;
  sf::Sprite sprite_;
  Graphics() = default;

  Graphics(const std::string& image) {
    texture_.loadFromFile(image);
    sprite_.setTexture(texture_);
  }

  Graphics(const sf::Color& color) {
    sprite_.setColor(color);
  }

  void Draw(sf::RenderWindow& window, float x, float y) {
    sprite_.setPosition(x, y);
    window.draw(sprite_);
  }
};

#endif  // GAME_ON_SFML_STATIC_GRAPHICS_H
