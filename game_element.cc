#include "game_element.h"

#include "cpputils/graphics/image.h"

void GameElement::Helper(graphics::Image &background, std::string &character,
                         int x_, int y_) {
  graphics::Image drawing;
  drawing.Load(character);
  for (int i = 0; i < drawing.GetWidth(); i++) {
    for (int j = 0; j < drawing.GetHeight(); j++) {
      background.SetColor(i + x_, j + y_, drawing.GetColor(i, j));
    }
  }
}
bool GameElement::IsOutOfBounds(const graphics::Image &background) {
  if (x_ < 0 || y_ < 0 || x_ > background.GetWidth() ||
      y_ > background.GetHeight()) {
    return true;
  } else {
    return false;
  }
}
