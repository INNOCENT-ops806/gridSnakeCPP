#include "../include/Game.h"
#include "../include/Config.h"
#include "../include/GameOverScreen.h"
#include "../include/Menu.h"
#include "../include/Snake.h"
#include <deque>
#include <raylib.h>
#include <raymath.h>

static double lastUpdateTime = 0;
bool eventTriggered(double interval) {
  double currentTime = GetTime();
  if (currentTime - lastUpdateTime >= interval) {
    lastUpdateTime = currentTime;
    return true;
  }
  return false;
}

Game::Game()
    : snake(), food(snake.body), gameOverScreen(), menu(), pausedMenu() {
  InitAudioDevice();
  eatSound = LoadSound("Sounds/sharp-pop-328170.mp3");
  wallSound = LoadSound("Sounds/game-over-arcade-6435.mp3");
  gameMusic = LoadMusicStream("Sounds/game-music-loop.mp3");

  SetMusicVolume(gameMusic, 0.1f);
  PlayMusicStream(gameMusic);

  currentState = PLAYING;
  score = 0;
  allowMove = false;
  cellSize = 30;

  cellCountX = GetScreenWidth() / cellSize;
  cellCountY = GetScreenHeight() / cellSize;

  if (cellCountX < 1)
    cellCountX = 1;
  if (cellCountY < 1)
    cellCountY = 1;

  int gAreaWidthPixels = cellCountX * cellSize;
  int gAreaHeightPixels = cellCountY * cellSize;

  offsetX = (GetScreenWidth() - gAreaWidthPixels) / 2;
  offsetY = (GetScreenHeight() - gAreaHeightPixels) / 2;

  snake.Reset();
  food.position =
      food.generateRandomPosition(snake.body, cellCountX, cellCountY);
}

Game::~Game() {
  UnloadSound(eatSound);
  UnloadSound(wallSound);
  UnloadMusicStream(gameMusic);
  CloseAudioDevice();
}

void Game::Draw() {
  ClearBackground(BLACK);
  if (currentState == PLAYING) {
    DrawRectangleLinesEx({(float)offsetX, (float)offsetY,
                          (float)(cellCountX * cellSize),
                          (float)(cellCountY * cellSize)},
                         GetScreenWidth() * 0.003, GRAY);
    snake.Draw(offsetX, offsetY, cellSize);
    food.Draw(offsetX, offsetY, cellSize);
    DrawText(TextFormat("Score: %i", score),
             GetScreenWidth() - GetScreenWidth() * 0.12,
             GetScreenHeight() - GetScreenHeight() * 0.10, 30, GREEN);
  } else if (currentState == GAME_OVER) {
    gameOverScreen.Draw();
  } else if (currentState == PAUSED) {
    pausedMenu.Draw();
  }
}

void Game::Update() {
  UpdateMusicStream(gameMusic);

  if (IsKeyPressed(KEY_H)) {
    if (currentState == PLAYING) {
      currentState = PAUSED;
    } else if (currentState == PAUSED) {
      currentState = PLAYING;
    }
  }

  if (currentState == PLAYING) {
    if (eventTriggered(snakeSpeed)) {
      allowMove = true;
      snake.Update(cellCountX, cellCountY);
    }
    if (IsKeyPressed(KEY_UP) && snake.direction.y != 1 && allowMove) {
      snake.direction = Vector2{0, -1};
      allowMove = false;
    }
    if (IsKeyPressed(KEY_DOWN) && snake.direction.y != -1 && allowMove) {
      snake.direction = Vector2{0, 1};
      allowMove = false;
    }
    if (IsKeyPressed(KEY_LEFT) && snake.direction.x != 1 && allowMove) {
      snake.direction = Vector2{-1, 0};
      allowMove = false;
    }
    if (IsKeyPressed(KEY_RIGHT) && snake.direction.x != -1 && allowMove) {
      snake.direction = Vector2{1, 0};
      allowMove = false;
    }

    CheckCollisionWithFood();
    CheckCollisionWithTail();
  } else if (currentState == GAME_OVER) {
    if (gameOverScreen.ShouldRestart()) {
      Reset();
    }
  }
}

void Game::CheckCollisionWithFood() {
  if (Vector2Equals(snake.body[0], food.position)) {
    food.position =
        food.generateRandomPosition(snake.body, cellCountX, cellCountY);
    PlaySound(eatSound);
    snake.addSegment = true;
    score += 10;
    if (snakeSpeed > snakeSpeedLimit) {
      snakeSpeed -= 0.015;
    } else {
      snakeSpeed -= 0;
    }
  }
}

void Game::CheckCollisionWithTail() {
  std::deque<Vector2> headlessBody = snake.body;
  headlessBody.pop_front();
  if (ElementInDeque(snake.body[0], headlessBody)) {
    GameOver();
  }
}

void Game::GameOver() {
  currentState = GAME_OVER;
  PlaySound(wallSound);
  StopMusicStream(gameMusic);
}

void Game::Reset() {
  snake.Reset();
  food.position =
      food.generateRandomPosition(snake.body, cellCountX, cellCountY);
  score = 0;
  currentState = PLAYING;
  allowMove = false;
  SetMusicVolume(gameMusic, 0.1f);
  PlayMusicStream(gameMusic);
}
