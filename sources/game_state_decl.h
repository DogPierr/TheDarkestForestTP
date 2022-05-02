#ifndef THEDARKESTFOREST_GAME_STATE_DECL_H
#define THEDARKESTFOREST_GAME_STATE_DECL_H

#include "SFML/Graphics.hpp"

class Player;

class GameState {
 public:
  void SetPlayerPtr(std::shared_ptr<Player> player_ptr);

  float GetPlayerDamage();

  std::tuple<bool, float, float> SetSlimeTarget(float x, float y, float damage);

  float SlimeDamage(float x, float y);

  float GetFireDamage();

  bool IsVisible(float x, float y);

  bool IsPlayerOutside();

  float GetIntencityRatio(float x, float y);

  static GameState* Instance();

  GameState(const GameState&) = delete;
  GameState& operator=(const GameState&) = delete;

 private:
  GameState() = default;

  static GameState* game_state_ptr_;
  float CalculateRadius(float x1, float y1, float x2, float y2);

  std::shared_ptr<Player> player_ptr_;

  float fire_radius_ = 500;
  float player_take_damage_ = 0;
  float fire_take_damage_ = 0;
};

#endif  // THEDARKESTFOREST_GAME_STATE_DECL_H
