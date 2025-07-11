#pragma once
#include "../include/Utils.h"
#include <deque>
#include <raylib.h>

class Snake {
public:
  std::deque<Vector2> body;
  Vector2 direction;
  bool addSegment;

  Snake();

  void Draw(int offsetX, int offsetY, int cellSize);
  void Update(int cellCountX, int cellCountY);
  void Reset();
};
