#ifndef GAME_ON_SFML_SOURCES_ENTITY_H_
#define GAME_ON_SFML_SOURCES_ENTITY_H_

#include "SFML/Graphics.hpp"
#include "dynamic_graphics.h"
#include "game_state.h"
#include "string"

class Entity {
public:
  float x_, y_;
  DynamicGraphics *graphics_;

  Entity() = default;

  virtual void Draw(sf::RenderWindow &window, GameState *gameState) {
    graphics_->Draw(window, gameState, x_, y_);
  };

  virtual void Act(GameState *gameState) {}

  virtual void Update(float time) = 0;
};

#endif // GAME_ON_SFML_SOURCES_ENTITY_H_
