#include "../include/Config.h"
#include "../include/Game.h"
#include "../lib/SplashLib/include/Splash.h"

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

  while (!WindowShouldClose() && !IsKeyPressed(KEY_Q)) {
    if (!splashComplete) {
      if (splash->isComplete()) {
        splashComplete = true;
        delete splash;
        splash = nullptr;
        game = new Game();
      }
    } else {
      if (game->menu.IsComplete() == false) {
        game->menu.Update();
      } else {
        game->Update();
      }
    }

    BeginDrawing();
    ClearBackground(BLACK);

    if (!splashComplete) {
      splash->draw();
    } else if (game->menu.IsComplete() == false) {
      game->menu.Draw();
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
