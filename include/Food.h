#pragma once
#include <deque>
#include <raylib.h>
#include <vector>

class Snake;
class Food {
public:
  Vector2 position;
  Food(std::deque<Vector2> snakeBody);

  void Draw(int offsetX, int offsetY, int cellSize);
  Vector2 GenerateRandomCell();
  Vector2 generateRandomPosition(std::deque<Vector2> snakeBody, int maxCellX,
                                 int maxCellY);
};
