#ifndef GAME_ON_SFML_SOURCES_STATICOBJECT_H_
#define GAME_ON_SFML_SOURCES_STATICOBJECT_H_

#include "SFML/Graphics.hpp"
#include "entity.h"
#include "game_state.h"

class StaticObject: public Entity {
  void Update(float time) override {}

  void Draw(sf::RenderWindow& window, GameState* gameState) override {
  }
};

#endif //GAME_ON_SFML_SOURCES_STATICOBJECT_H_
