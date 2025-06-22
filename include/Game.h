#pragma once
#include "Food.h"
#include "GameOverScreen.h"
#include "Snake.h"
#include <deque>
#include <raylib.h>

bool eventTriggered(double interval);
enum GameState {
  PLAYING,
  GAME_OVER,
  // PAUSED
  // MENU
};

class Game {
public:
  Snake snake;
  Food food;
  bool running;
  int score;
  Sound eatSound;
  Sound wallSound;
  Music gameMusic;

  Game();
  ~Game();

  void Draw();
  void Update();

  void CheckCollisionWithFood();
  void CheckCollisionWithTail();
  void GameOver();
  void Reset();
  GameState currentState;
  GameOverScreen gameOverScreen;
  bool allowMove;
};
