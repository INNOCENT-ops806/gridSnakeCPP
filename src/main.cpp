#include "../include/Config.h"
#include "../include/Game.h"
#include "../lib/SplashLib/include/Splash.h"
#include <raylib.h>

int main() {
  int const screenwidth = 1366;
  int const screenheight = 760;

  InitWindow(screenwidth, screenheight, "Retro Snake Game");
  SetTargetFPS(60);

  if (!IsWindowFullscreen()) {
    ToggleFullscreen();
  }

  bool splashComplete = false;

  Splash *splash = new Splash();
  Game *game = nullptr;

  while (!WindowShouldClose()) {
    if (!splashComplete) {
      if (splash->isComplete()) {
        splashComplete = true;
        delete splash;
        splash = nullptr;
        game = new Game();
      }
    } else {
      game->Update();
    }
    BeginDrawing();

    ClearBackground(BLACK);
    if (!splashComplete) {
      splash->draw();
    } else {
      game->Draw();
    }

    EndDrawing();
  }
  if (game != nullptr) {
    delete game;
  }
  if (splash != nullptr) {
    delete splash;
  }
  CloseWindow();
  return 0;
}
