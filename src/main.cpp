#include "../include/Config.h"
#include "../include/Game.h"
#include "../lib/SplashLib/include/Splash.h"
#include <raylib.h>

int main() {
  int const screenwidth = 800;
  int const screenheight = 600;
  InitWindow(screenwidth, screenwidth, "Retro Snake Game");
  SetTargetFPS(60);

  if (!IsWindowFullscreen()) {
    ToggleFullscreen();
  }

  Splash *splash = new Splash();

  // Game game;

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);
    {
      if (!splash->isComplete()) {
        splash->draw();
      } else {
        // game.Draw();
        // game.Update();
      }
    }
    EndDrawing();
  } // this is the while loop
  delete splash;
  CloseWindow();
  return 0;
}
