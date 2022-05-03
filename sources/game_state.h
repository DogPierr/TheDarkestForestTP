#pragma once

#include <cmath>
#include <iostream>
#include <utility>

void GameState::SetPlayerPtr(std::shared_ptr<Player> player_ptr) {
  player_ptr_ = std::move(player_ptr);
}

float GameState::GetPlayerDamage() {
  float copy = player_take_damage_;
  player_take_damage_ = 0;
  return copy;
}

std::tuple<bool, float, float> GameState::SetSlimeTarget(
    float x, float y, float damage) {
  float player_radius = CalculateRadius(player_ptr_->x_, player_ptr_->y_, x, y);
  float fire_radius = CalculateRadius(0, 0, x, y);
  bool is_attacking = fire_radius < 50 || player_radius < 50;
  if (player_radius < 100) {
    if (player_radius < 50) {
      if (is_attacking)
        player_take_damage_ += damage;
      return {true, player_ptr_->x_, player_ptr_->y_};
    }
    return {false, player_ptr_->x_, player_ptr_->y_};
  }
  if (fire_radius < 50) {
    if (is_attacking)
      fire_take_damage_ += damage / 5;
    return {true, 0, 0};
  }
  return {false, 0, 0};
}

float GameState::SlimeDamage(float x, float y) {
  if (!player_ptr_->is_attacking_) {
    return 0;
  }
  std::vector<float> radius_vector(2);
  radius_vector[0] = x - player_ptr_->x_;
  radius_vector[1] = y - player_ptr_->y_;
  float distance = CalculateRadius(player_ptr_->x_, player_ptr_->y_, x, y);

  float cos = (player_ptr_->line_of_sight_[0] * radius_vector[0] +
               player_ptr_->line_of_sight_[1] * radius_vector[1]) /
              distance;

  if (cos >= 0 && distance <= 50 && player_ptr_->is_attacking_ && player_ptr_->IsAnimationFinished()) {
    return player_ptr_->damage_;
  }
  return 0;
}

float GameState::GetFireDamage() {
  float copy = fire_take_damage_;
  fire_take_damage_ = 0;
  return copy;
}

bool GameState::IsVisible(float x, float y) {
  return CalculateRadius(x, y, 0, 0) < fire_radius_ * 0.7 ||
         (IsPlayerOutside() &&
          CalculateRadius(x, y, player_ptr_->x_, player_ptr_->y_) < 50);
}

bool GameState::IsPlayerOutside() {
  return CalculateRadius(player_ptr_->x_, player_ptr_->y_, 0, 0) > fire_radius_;
}

float GameState::GetIntencityRatio(float x, float y) {
  return sqrt(x * x + y * y) / (0.7 * fire_radius_);
}

GameState* GameState::Instance() {
  if (game_state_ptr_ == nullptr) {
    game_state_ptr_ = new GameState;
  }
  return game_state_ptr_;
}

float GameState::CalculateRadius(float x1, float y1, float x2, float y2) {
  return std::sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

GameState* GameState::game_state_ptr_ = nullptr;
