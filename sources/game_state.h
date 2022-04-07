#pragma once

#include <iostream>
#include <cmath>

class GameState {
 public:
  void GetPlayerData(float player_x, float player_y, bool is_player_attacking, bool is_finished,
                     const std::vector<float>& players_line_of_sight) {
    player_x_ = player_x;
    player_y_ = player_y;
    is_player_attacking_ = is_player_attacking;
    is_players_animation_finished_ = is_finished;
    player_line_of_sight_ = players_line_of_sight;
  }

  float GetPlayerDamage() {
      float copy = player_damage_;
      player_damage_ = 0;
      return copy;
  }

  std::tuple<bool, float, float> SetSlimeTarget(float x, float y, bool is_animation_finished) {
    float player_radius = CalculateRadius(player_x_, player_y_, x, y);
    float fire_radius = CalculateRadius(0, 0, x, y);
    bool is_attacking = fire_radius < 50 || player_radius < 50;
    if (player_radius < fire_radius) {
      if (player_radius < 50) {
        if (is_attacking && is_animation_finished) player_damage_ += 5;
        return {true, player_x_, player_y_};
      }
      return {false, player_x_, player_y_};
    }
    if (fire_radius < 50) {
      if (is_attacking && is_animation_finished) fire_damage_ += 1;
      return {true, 0, 0};
    }
    return {false, 0, 0};
  }

  float SlimeDamage(float x, float y) {
    if (!is_player_attacking_) {
      return 0;
    }
    std::vector<float> radius_vector(2);
    radius_vector[0] = x - player_x_;
    radius_vector[1] = y - player_y_;
    float distance = CalculateRadius(player_x_, player_y_, x, y);

    float cos = (player_line_of_sight_[0] * radius_vector[0] +
                 player_line_of_sight_[1] * radius_vector[1]) /
                distance;
    if (is_player_attacking_  && is_players_animation_finished_ && cos >= 0 && distance <= 50) {
      is_players_animation_finished_ = false;
      return 10;
    }
    return 0;
  }

  float GetFireDamage() {
    float copy = fire_damage_;
    fire_damage_ = 0;
    return copy;
  }

  bool IsVisible(float x, float y) {
    return CalculateRadius(x, y, 0, 0) < fire_radius_ * 0.7 ||
           (is_player_outside_ &&
            CalculateRadius(x, y, player_x_, player_y_) < 100);
  }

  bool IsPlayerOutside() {
    return CalculateRadius(player_y_, player_x_, 0, 0) > fire_radius_;
  };

 private:
  float CalculateRadius(float x1, float y1, float x2, float y2) {
    return std::sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
  }

  float player_x_ = 0, player_y_ = 0;
  std::vector<float> player_line_of_sight_;
  bool is_player_outside_ = false;
  bool is_player_attacking_ = false;
  bool is_players_animation_finished_ = false;
  float fire_radius_ = 500;
  float player_damage_ = 0;
  float fire_damage_ = 0;
};
