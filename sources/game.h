#ifndef GAME_ON_SFML_SOURCES_GAME_H_
#define GAME_ON_SFML_SOURCES_GAME_H_

#include "SFML/Graphics.hpp"
#include "dynamic_graphics.h"
#include "entity.h"
#include "map.h"
#include "player.h"
#include "water_slime.h"
#include "cmath"

class GameLoop {
 public:
  GameLoop()
      : window_(sf::VideoMode(1000, 1000), "TheDarkestForest"),
        gameState(new GameState), player_(new Player(0, 0, 10, 10, 0.07)) {
    objects_.push_back(new Fire);
    objects_.push_back(player_);
    NewWave();
  }

  void Run() {
    sf::View camera;
    sf::Clock timer;

    while (window_.isOpen()) {
      float time = timer.getElapsedTime().asSeconds();
      timer.restart();
      if (objects_.size() <= 2) {
        NewWave();
      }
      sf::Event event;
      while (window_.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
          window_.close();
        }
      }
      window_.clear();
      auto iter = objects_.begin();
      for (Entity *entity: objects_) {
        entity->Update(time);
        entity->Act(gameState);
        if (dynamic_cast<Mortal*>(entity)->IsDead()) {
          objects_.erase(iter);
        } else {
          entity->Draw(window_, gameState);
          ++iter;
        }
      }
      camera.setCenter(player_->x_, player_->y_);
      window_.setView(camera);
      window_.display();
    }
  }

  void NewWave() {
    ++amount_of_enemies_;
    float radians_spacing = (2 * M_PI) / amount_of_enemies_;
    float cur_angle = 0;
    for (int i = 0; i < amount_of_enemies_; ++i) {
      float distance = 200;
      objects_.push_back(new WaterSlime(distance * cos(cur_angle), distance * sin(cur_angle), 10, 10, 0.04));
      cur_angle += radians_spacing;
    }
  }

  void Terminate() {}

 private:
  int amount_of_enemies_ = 3;
  float max_spawn_distance_ = 1000;
  GameState *gameState;
  std::vector<Entity *> objects_;
  sf::RenderWindow window_;
  std::vector<WaterSlime *> water_slimes_;
  Player *player_;
  Fire *fire_;
  int GetRandomNumber(int min, int max) {
    srand(time(NULL));
    int num = min + rand() % (max - min + 1);
    return num;
  }

};

#endif  // GAME_ON_SFML_SOURCES_GAME_H_