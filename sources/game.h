#ifndef GAME_ON_SFML_SOURCES_GAME_H_
#define GAME_ON_SFML_SOURCES_GAME_H_

#include "SFML/Graphics.hpp"
#include "dynamic_graphics.h"
#include "entity.h"
#include "map.h"
#include "player.h"
#include "water_slime.h"

class GameLoop {
 public:
  GameLoop()
      : window_(sf::VideoMode(1000, 1000), "plswork"),
        gameState(new GameState), player_(new Player(0, 0, 10, 10, 0.1)) {
    objects_.push_back(new Fire);
    objects_.push_back(player_);
    objects_.push_back(new WaterSlime(800, 0, 10, 10, 0.05));
    objects_.push_back(new WaterSlime(0, 800, 10, 10, 0.05));
    objects_.push_back(new WaterSlime(800, 800, 10, 10, 0.05));

  }

  void Run() {
    sf::View camera;
    sf::Clock timer;

    while (window_.isOpen()) {
      float time = timer.getElapsedTime().asSeconds();
      timer.restart();
      sf::Event event;
      while (window_.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
          window_.close();
        }
      }
      window_.clear();
      for (Entity* entity : objects_) {
        entity->Draw(window_, gameState);
        entity->Update(time);
        entity->Act(gameState);
      }
      camera.setCenter(player_->x_, player_->y_);
      window_.setView(camera);
      window_.display();
    }
  }

  void Terminate() {}

 private:
  GameState* gameState;
  std::vector<Entity*> objects_;
  sf::RenderWindow window_;
  std::vector<WaterSlime*> water_slimes_;
  Player* player_;
  Fire* fire_;
};

#endif  // GAME_ON_SFML_SOURCES_GAME_H_