#include "game.h"

void Game::Start() { game_screen.ShowUntilClosed(); }

void Game::LaunchProjectiles() {
  for (int k = 0; k < Opponent_character.size(); k++) {
    if (Opponent_character[k]->LaunchProjectile() != nullptr) {
      std::unique_ptr<OpponentProjectile> fresh_proj =
          std::make_unique<OpponentProjectile>(Opponent_character[k]->GetX(),
                                               Opponent_character[k]->GetY());
      o_projectile.push_back(std::move(fresh_proj));
    }
  }
}

void Game::RemoveInactive() {
  for (int k = 0; k < Opponent_character.size(); k++) {
    if (Opponent_character[k]->GetIsActive() == false) {
      Opponent_character.erase(Opponent_character.begin());
      k = k - 1;
    }
  }

  for (int k = 0; k < o_projectile.size(); k++) {
    if (o_projectile[k]->GetIsActive() == false) {
      o_projectile.erase(o_projectile.begin());
      k = k - 1;
    }
  }

  for (int k = 0; k < p_projectile.size(); k++) {
    if (p_projectile[k]->GetIsActive() == false) {
      p_projectile.erase(p_projectile.begin());
      k = k - 1;
    }
  }
}
