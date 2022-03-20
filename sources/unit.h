#ifndef GAME_ON_SFML_SOURCES_OBJECT_H_
#define GAME_ON_SFML_SOURCES_OBJECT_H_

#include "SFML/Graphics.hpp"
#include "dynamic_graphics.h"
#include "mortal.h"

class Unit : public Mortal {
 public:
  bool is_attacking_;
  int damage_;

  float speed_;

  Unit() = default;

  virtual void Update(float time) = 0;

};

#endif //GAME_ON_SFML_SOURCES_OBJECT_H_
