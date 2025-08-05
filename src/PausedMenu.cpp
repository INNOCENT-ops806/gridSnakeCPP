#include "../include/Config.h"
#include "../include/PauseMenu.h"
#include <raylib.h>
#include <raymath.h>

PausedMenu::PausedMenu() {}
void PausedMenu::Draw() {
  DrawText("Paused", GetScreenWidth() / 2 - GetScreenHeight() / 2,
           GetScreenHeight() / 4, GetScreenHeight() / 4, GREEN);
}
