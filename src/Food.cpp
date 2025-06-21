#include "../include/Food.h"
#include "../include/Config.h"
#include "../include/Utils.h"
#include <deque>
#include <raylib.h>
#include <raymath.h>

Food::Food(std::deque<Vector2> snakeBody) {
  position = generateRandomPosition(snakeBody);
}

void Food::Draw() {
  DrawRectangle(offset + position.x * cellSize, offset + position.y * cellSize,
                cellSize, cellSize, Mypurple);
}

Vector2 Food::GenerateRandomCell() {
  float x = GetRandomValue(0, cellCount - 1);
  float y = GetRandomValue(0, cellCount - 1);
  return Vector2{x, y};
}

Vector2 Food::generateRandomPosition(std::deque<Vector2> snakeBody) {
  Vector2 newPosition = GenerateRandomCell();
  while (ElementInDeque(newPosition, snakeBody)) {
    newPosition = GenerateRandomCell();
  }
  return newPosition;
}
