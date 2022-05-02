#ifndef GAME_ON_SFML_SOURCES_GAME_H_
#define GAME_ON_SFML_SOURCES_GAME_H_

#include "SFML/Graphics.hpp"
#include "cmath"
#include "dynamic_graphics.h"
#include "entity.h"
#include "map.h"
#include "memory"
#include "player.h"
#include "water_slime.h"

class GameLoop {
 public:
  GameLoop()
      : window_(sf::VideoMode(1000, 1000), "TheDarkestForest"),
        gameState(GameState::Instance()),
        player_(std::make_shared<Player>(0, 0, 10, 10, 0.07)),
        camera(),
        is_playing_(true) {
    gameState->SetPlayerPtr(player_);
    objects_.push_back(std::make_shared<Fire>());
    objects_.push_back(std::shared_ptr<Player>(player_));
    NewWave();
  }

  void Run() {
    bool is_pushed = false;
    sf::Clock timer;

    while (window_.isOpen() &&
           !std::dynamic_pointer_cast<Mortal>(objects_[0])->IsDead() &&
           !std::dynamic_pointer_cast<Mortal>(objects_[1])->IsDead()) {
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
      for (; iter != objects_.end();) {
        auto entity = *iter;
        if (!entity) {
          objects_.erase(iter);
        }
        if (is_playing_) {
          entity->Update(time);
          entity->Act(gameState);
        }
        if (std::dynamic_pointer_cast<Mortal>(entity)->IsDead() &&
            iter != objects_.begin() && iter != objects_.begin() + 1) {
          objects_.erase(iter);
        } else {
          entity->Draw(window_, gameState);
          ++iter;
        }
      }
      camera.setCenter(player_->x_, player_->y_);
      window_.setView(camera);
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        if (!is_pushed) {
          is_playing_ = !is_playing_;
        }
        is_pushed = true;
      } else {
        is_pushed = false;
      }
      Stop();
      window_.display();
    }
    while (window_.isOpen()) {
      sf::Event event;
      while (window_.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
          window_.close();
        }
        if (event.type == sf::Event::KeyPressed) {
          NewGame();
        }
      }
      window_.clear();
      Terminate();
      window_.display();
    }
  }

 private:
  sf::View camera;
  int amount_of_enemies_ = 3;
  GameState* gameState;
  std::vector<std::shared_ptr<Entity>> objects_;
  sf::RenderWindow window_;
  std::shared_ptr<Player> player_;
  bool is_playing_;

  void NewWave() {
    ++amount_of_enemies_;
    float radians_spacing = (2 * M_PI) / amount_of_enemies_;
    float cur_angle = 0;
    for (int i = 0; i < amount_of_enemies_; ++i) {
      float distance = 1000;
      objects_.push_back(std::make_shared<WaterSlime>(
          distance * cos(cur_angle), distance * sin(cur_angle), 10, 10, 0.04));
      // objects_.push_back(new WaterSlime(distance * cos(cur_angle), distance *
      // sin(cur_angle), 10, 10, 0.04));
      cur_angle += radians_spacing;
    }
  }

  void Stop() {
    if (!is_playing_) {
      sf::Font font;
      font.loadFromFile("../sources/fonts/EBGaramond-SemiBold.ttf");
      sf::Text title("PAUSE", font, 60);
      title.setPosition(
          camera.getCenter().x - title.getGlobalBounds().width / 2,
          camera.getCenter().y);
      window_.draw(title);
    }
  }

  void Terminate() {
    sf::Font font;
    font.loadFromFile("../sources/fonts/EBGaramond-SemiBold.ttf");
    sf::Text title("YOU DIED", font, 80);
    title.setFillColor(sf::Color::Red);
    sf::Text continue_text("press any key to begin a new game", font, 30);
    title.setPosition(camera.getCenter().x - title.getGlobalBounds().width / 2,
                      camera.getCenter().y);
    continue_text.setPosition(
        camera.getCenter().x - continue_text.getGlobalBounds().width / 2,
        camera.getCenter().y + 2 * title.getGlobalBounds().height);
    window_.draw(title);
    window_.draw(continue_text);
    window_.display();
  }

  void NewGame() {
    for (auto iter : objects_) {
      iter->~Entity();
    }
    amount_of_enemies_ = 3;
    objects_.clear();
    objects_.push_back(std::make_shared<Fire>());
    player_ = std::make_shared<Player>(0, 0, 10, 10, 0.07);
    gameState->SetPlayerPtr(player_);
    objects_.push_back(player_);
    camera.setCenter(0, 0);
    is_playing_ = true;
    Run();
  }
};

#endif  // GAME_ON_SFML_SOURCES_GAME_H_