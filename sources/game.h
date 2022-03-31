#ifndef GAME_ON_SFML_SOURCES_GAME_H_
#define GAME_ON_SFML_SOURCES_GAME_H_

#include "SFML/Graphics.hpp"
#include "entity.h"
#include "dynamic_graphics.h"
#include "map.h"
#include "player.h"
#include "water_slime.h"

class GameLoop {
 public:
  GameLoop()
      : window_(sf::VideoMode(1000, 1000), "plswork"),
        player_(new Player(0, 0, 10, 10, 0.1)),
        fire_(new Fire),
        water_slimes_() {}

  void Run() {
    sf::View camera;
    sf::Clock timer;
    water_slimes_.push_back(new WaterSlime(800, 0, 10, 10, 0.05));
    water_slimes_.push_back(new WaterSlime(0, 800, 10, 10, 0.05));
    water_slimes_.push_back(new WaterSlime(800, 800, 10, 10, 0.05));

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
      fire_->DrawBackground(window_);
      for (auto slime : water_slimes_) {
        slime->SetTarget(fire_);
        if (slime->IsInRadius(player_)) {
          slime->SetTarget(player_);
        }
        slime->Update(time);
        slime->Draw(window_);
        player_->Attack(slime);
      }
      player_->Update(time);
      player_->Draw(window_);
      for (auto slime : water_slimes_) {
        slime->Draw(window_);
      }
      fire_->DrawFrame(window_);
      if (!fire_->IsInRadius(player_)) {
        player_->DrawBackground(window_);
        for (auto slime : water_slimes_) {
          slime->SetTarget(fire_);
          if (slime->IsInRadius(player_)) {
            slime->SetTarget(player_);
          }
          slime->Update(time);
          slime->Draw(window_);
          player_->Attack(slime);
        }
        player_->DrawFrame(window_);
        player_->Draw(window_);
      }
      fire_->Update(time);
      fire_->Draw(window_);
      camera.setCenter(player_->x_, player_->y_);
      window_.setView(camera);
      window_.display();
    }
  }

  void Terminate() {}

 private:
  sf::RenderWindow window_;
  std::vector<WaterSlime*> water_slimes_;
  Player* player_;
  Fire* fire_;
};

#endif  // GAME_ON_SFML_SOURCES_GAME_H_