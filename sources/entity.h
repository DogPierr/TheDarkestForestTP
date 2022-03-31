#ifndef GAME_ON_SFML_SOURCES_ENTITY_H_
#define GAME_ON_SFML_SOURCES_ENTITY_H_

#include "string"
#include "SFML/Graphics.hpp"
#include "dynamic_graphics.h"

class Entity {
 public:
  float x_, y_;
  DynamicGraphics* graphics_;

  Entity() = default;

  void Draw(sf::RenderWindow& window) { graphics_->Draw(window, x_, y_); };

  virtual void Update(float time) = 0;
};

#endif  // GAME_ON_SFML_SOURCES_ENTITY_H_
