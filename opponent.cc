#include "opponent.h"

void Opponent::Draw(graphics::Image &background) {
  std::string variable = "gura_a.bmp";
  Helper(background, variable, x_, y_);
}

void Opponent::Move(const graphics::Image &background) {
  if (!IsOutOfBounds(background)) {
    SetX(GetX() + 1);
    SetY(GetY() + 1);
  } else {
    is_active = false;
  }
}

void OpponentProjectile::Draw(graphics::Image &background) {
  std::string variable = "trident.bmp";
  Helper(background, variable, x_, y_);
}

void OpponentProjectile::Move(const graphics::Image &background) {
  if (!IsOutOfBounds(background)) {
    SetX(GetX() + 1);
    SetY(GetY() + 1);
  } else {
    is_active = false;
  }
}

std::unique_ptr<OpponentProjectile> Opponent::LaunchProjectile() {
  counter_ += 1;
  if (counter_ % 5 == 0) {
    std::unique_ptr<OpponentProjectile> oppo_proj =
        std::make_unique<OpponentProjectile>(GetX(), GetY());
    return std::move(oppo_proj);
  } else {
    return nullptr;
  }
}
