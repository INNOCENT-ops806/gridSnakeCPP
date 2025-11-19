#include "../include/Snake.h"
#include "../include/Config.h"
#include <raylib.h>
#include <raymath.h>

Snake::Snake() {
  body = {Vector2{6, 9}, Vector2{5, 9}, Vector2{4, 9}};
  direction = Vector2{1, 0};
  addSegment = false;
}

void Snake::Draw(int offsetX, int offsetY, int cellSize) {
  for (unsigned int i = 0; i < body.size(); i++) {
    float x = body[i].x;
    float y = body[i].y;
    Rectangle segment = {offsetX + x * cellSize, offsetY + y * cellSize,
                         (float)cellSize, (float)cellSize};
    DrawRectangleRounded(segment, 0.5, 6, MAROON);
  }
}

void Snake::Update(int cellCountX, int cellCountY) {
  if (!addSegment) {
    body.pop_back();
  }
  addSegment = false;
  Vector2 newHeadPosition = body[0];
  newHeadPosition.x += direction.x;
  newHeadPosition.y += direction.y;

  if (newHeadPosition.x >= cellCountX) {
    newHeadPosition.x = 0;
  } else if (newHeadPosition.x < 0) {
    newHeadPosition.x = cellCountX - 1;
  }
  if (newHeadPosition.y >= cellCountY) {
    newHeadPosition.y = 0;
  } else if (newHeadPosition.y < 0) {
    newHeadPosition.y = cellCountY - 1;
  }
  body.push_front(newHeadPosition);
}

void Snake::Reset() {
  body = {Vector2{6, 9}, Vector2{5, 9}, Vector2{4, 9}};
  direction = Vector2{1, 0};
  addSegment = false;
}
