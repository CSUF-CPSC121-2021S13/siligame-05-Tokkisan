#include "player.h"

void Player::Draw(graphics::Image &background) {
  std::string variable = "ina_takodachi.bmp";
  Helper(background, variable, x_, y_);
}

void Player::Move(const graphics::Image &background) {}

void PlayerProjectile::Draw(graphics::Image &background) {
  std::string variable = "ink.bmp";
  Helper(background, variable, x_, y_);
}

void PlayerProjectile::Move(const graphics::Image &background) {
  if (!IsOutOfBounds(background)) {
    SetY(GetY() - 1);
  } else {
    is_active = false;
  }
}
