#pragma once
#include <deque>
#include <raylib.h>
#include <vector>

class Snake;
class Food {
public:
  Vector2 position;
  Food(std::deque<Vector2> snakeBody);

  void Draw();
  Vector2 GenerateRandomCell();
  Vector2 generateRandomPosition(std::deque<Vector2> snakeBody);
};
