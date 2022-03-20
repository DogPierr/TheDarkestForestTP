#ifndef GAMEPROJECTTP_SOURCES_ENTITY_H_
#define GAMEPROJECTTP_SOURCES_ENTITY_H_

#include "SFML/Graphics.hpp"
#include "dynamic_graphics.h"

class Entity {
 public:
  float x_, y_, h_, w_;
  DynamicGraphics graphics_;

  Entity() = default;

  void Draw(sf::RenderWindow& window) { graphics_.Draw(window, x_, y_); };

  virtual void Update(float time) = 0;
};

#endif  // GAMEPROJECTTP_SOURCES_ENTITY_H_
