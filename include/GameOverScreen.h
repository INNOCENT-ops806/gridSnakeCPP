#pragma once
#include <raylib.h>

class GameOverScreen {
public:
  GameOverScreen();

  void Draw();

  bool ShouldRestart();
};
