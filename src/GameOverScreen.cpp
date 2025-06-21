#include "../include/GameOverScreen.h"
#include "../include/Config.h"
#include <raylib.h>
GameOverScreen::GameOverScreen() {}
void GameOverScreen::Draw() {
  int currentScreenWidth = GetScreenWidth();
  int currentScreenHeight = GetScreenHeight();

  ClearBackground(DARKPURPLE);

  const char *gameOverText = "GAME OVER";
  int fontSize = 100;
  int textWidth = MeasureText(gameOverText, fontSize);
  int textHeight = fontSize;

  DrawText(gameOverText,
           (float)currentScreenWidth * 1.695 / 2 - (float)textWidth / 2,
           currentScreenHeight / 3 - textHeight / 2, fontSize, Tsoding);

  const char *restartText = "Press R to Restart";
  int restartFontSize = 30;
  int restartTextWidth = MeasureText(restartText, restartFontSize);
  DrawText(restartText,
           (float)currentScreenWidth * 1.695 / 2 - (float)restartTextWidth / 2,
           currentScreenHeight / 2 + textHeight / 2, restartFontSize, Mypurple);
}

bool GameOverScreen::ShouldRestart() { return IsKeyPressed(KEY_R); }
