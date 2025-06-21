#include "../include/Game.h"
#include "../include/Config.h"
#include "../include/GameOverScreen.h"
#include "../include/Snake.h"
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

Game::Game() : snake(), food(snake.body), gameOverScreen() {
  InitAudioDevice();
  eatSound = LoadSound(".Sounds/sharp-pop-328170.mp3");
  wallSound = LoadSound("./Sounds/game-over-arcade-6435.mp3");
  currentState = PLAYING;
  score = 0;
  allowMove = false;
}

Game::~Game() {
  UnloadSound(eatSound);
  UnloadSound(wallSound);
  CloseAudioDevice();
}

void Game::Draw() {

  ClearBackground(Mygreen);
  DrawRectangleLinesEx(
      {5, 5, (float)GetScreenWidth() - 75,
       (float)GetScreenHeight() - (float)(GetScreenWidth() * 0.05)},
      5, BLACK);
  if (currentState == PLAYING) {
    food.Draw();
    snake.Draw();
    DrawText(TextFormat("Score: %i", score), GetScreenWidth() - 150, 10, 30,
             GREEN);
  } else if (currentState == GAME_OVER) {
    gameOverScreen.Draw();
  }
}

void Game::Update() {
  if (currentState == PLAYING) {
    if (eventTriggered(0.2)) {
      allowMove = true;
      snake.Update();
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
    CheckCollisionWithEdges();
    CheckCollisionWithTail();
  } else if (currentState == GAME_OVER) {
    if (gameOverScreen.ShouldRestart()) {
      Reset();
    }
  }
  if (currentState == PLAYING) {
    DrawText("STATE: PLAYING", 10, 10, 20, BLUE);
  } else {
    DrawText("STATE: GAME OVER", 10, 10, 20, RED);
  }
}
void Game::CheckCollisionWithFood() {
  if (Vector2Equals(snake.body[0], food.position)) {
    food.position = food.generateRandomPosition(snake.body);
    snake.addSegment = true;
    score++;
    PlaySound(eatSound);
  }
}

void Game::CheckCollisionWithEdges() {
  if (snake.body[0].x == cellCount || snake.body[0].x == -1) {
    GameOver();
  }
  if (snake.body[0].y == cellCount || snake.body[0].y == -1) {
    GameOver();
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
}

void Game::Reset() {
  snake.Reset();
  food.position = food.generateRandomPosition(snake.body);
  score = 0;
  currentState = PLAYING;
  allowMove = false;
}
