#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <memory>
#include "cpputils/graphics/image_event.h"
#include "game_element.h"
#include "opponent.h"
#include "player.h"

class Game : public graphics::AnimationEventListener,
             public graphics::MouseEventListener {
 public:
  Game() : Game(800, 600) {}
  Game(const int &width, const int &height) {
    game_screen.Initialize(width, height);
  }

  void CreateOpponents() {
    std::unique_ptr<Opponent> gura_a =
        std::make_unique<Opponent>(game_screen.GetWidth() * 0.5, 0);
    Opponent_character.push_back(std::move(gura_a));
  }

  void Init() {
    game_screen.AddMouseEventListener(*this);
    game_screen.AddAnimationEventListener(*this);

    CreateOpponents();
    player_.SetX(400);
    player_.SetY(400);
  }

  void Start();

  Player &GetPlayer() { return player_; }
  graphics::Image &GetGameScreen() { return game_screen; }
  std::vector<std::unique_ptr<Opponent>> &GetOpponents() {
    return Opponent_character;
  }
  std::vector<std::unique_ptr<OpponentProjectile>> &GetOpponentProjectiles() {
    return o_projectile;
  }
  std::vector<std::unique_ptr<PlayerProjectile>> &GetPlayerProjectiles() {
    return p_projectile;
  }

  void MoveGameElements() {
    for (int i = 0; i < Opponent_character.size(); i++) {
      if (Opponent_character[i]->GetIsActive()) {
        Opponent_character[i]->Move(game_screen);
      }
    }
    for (int j = 0; j < o_projectile.size(); j++) {
      if (o_projectile[j]->GetIsActive()) {
        o_projectile[j]->Move(game_screen);
      }
    }
    for (int k = 0; k < p_projectile.size(); k++) {
      if (p_projectile[k]->GetIsActive()) {
        p_projectile[k]->Move(game_screen);
      }
    }
  }

  void FilterIntersections() {
    for (int i = 0; i < Opponent_character.size(); i++) {
      if (Opponent_character[i]->IntersectsWith(&player_)) {
        Opponent_character[i]->SetIsActive(false);
        player_.SetIsActive(false);
        has_lost_ = true;
      }
    }
    for (int j = 0; j < o_projectile.size(); j++) {
      if (o_projectile[j]->IntersectsWith(&player_)) {
        o_projectile[j]->SetIsActive(false);
        player_.SetIsActive(false);
        has_lost_ = true;
      }
    }
    for (int k = 0; k < p_projectile.size(); k++) {
      for (int l = 0; l < Opponent_character.size(); l++) {
        if (p_projectile[k]->IntersectsWith(Opponent_character[l].get())) {
          p_projectile[k]->SetIsActive(false);
          Opponent_character[l]->SetIsActive(false);
          if (player_.GetIsActive() == true) {
            player_score = player_score + 1;
          }
        }
      }
    }
  }
  int GetScore() const { return player_score; }
  bool HasLost() const { return has_lost_; }

  void UpdateScreen() {
    std::string score = "Score: ";
    score += std::to_string(GetScore());
    game_screen.DrawRectangle(0, 0, game_screen.GetWidth(),
                              game_screen.GetHeight(), 255, 255, 255);
    game_screen.DrawText(0, 0, score, 20, 0, 0, 0);
    if (has_lost_ == true) {
      game_screen.DrawText(game_screen.GetWidth() * 0.5,
                           game_screen.GetHeight() * 0.25, "game over", 20, 225,
                           0, 0);
    }

    for (int i = 0; i < Opponent_character.size(); i++) {
      if (Opponent_character[i]->GetIsActive()) {
        Opponent_character[i]->Draw(game_screen);
      }
    }
    for (int j = 0; j < o_projectile.size(); j++) {
      if (o_projectile[j]->GetIsActive()) {
        o_projectile[j]->Draw(game_screen);
      }
    }
    for (int k = 0; k < p_projectile.size(); k++) {
      if (p_projectile[k]->GetIsActive()) {
        p_projectile[k]->Draw(game_screen);
      }
    }
    if (player_.GetIsActive()) {
      player_.Draw(game_screen);
    }
  }

  void OnAnimationStep() override {
    if (Opponent_character.size() == 0) {
      CreateOpponents();
    }
    MoveGameElements();
    LaunchProjectiles();
    FilterIntersections();
    RemoveInactive();
    UpdateScreen();
    game_screen.Flush();
  }

  void OnMouseEvent(const graphics::MouseEvent &event) override {
    if (event.GetX() > 0 && event.GetX() < game_screen.GetWidth() &&
        event.GetY() > 0 && event.GetY() < game_screen.GetHeight()) {
      player_.SetX(event.GetX() - (player_.GetWidth() * 0.5));
      player_.SetY(event.GetY() - (player_.GetHeight() * 0.5));
    }
    if (event.GetMouseAction() == graphics::MouseAction::kPressed ||
        event.GetMouseAction() == graphics::MouseAction::kDragged) {
      std::unique_ptr<PlayerProjectile> fresh_proj_b =
          std::make_unique<PlayerProjectile>(player_.GetX(), player_.GetY());
      p_projectile.push_back(std::move(fresh_proj_b));
    }
  }
  void LaunchProjectiles();
  void RemoveInactive();

 private:
  int player_score = 0;
  bool has_lost_ = false;
  Player player_;
  graphics::Image game_screen;
  std::vector<std::unique_ptr<Opponent>> Opponent_character;
  std::vector<std::unique_ptr<OpponentProjectile>> o_projectile;
  std::vector<std::unique_ptr<PlayerProjectile>> p_projectile;
};

#endif
