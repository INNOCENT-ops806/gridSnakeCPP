#include "../include/Snake.h"
#include "../include/Config.h"
#include <raylib.h>
#include <raymath.h>

Snake::Snake() {
  body = {Vector2{6, 9}, Vector2{5, 9}, Vector2{4, 9}};
  direction = Vector2{1, 0};
  addSegment = false;
}

void Snake::Draw() {
  for (unsigned int i = 0; i < body.size(); i++) {
    float x = body[i].x;
    float y = body[i].y;
    Rectangle segment = {offset + x * cellSize, offset + y * cellSize,
                         (float)cellSize, (float)cellSize};
    DrawRectangleRounded(segment, 0.5, 6, MAROON);
  }
}

void Snake::Update() {
  body.push_front(Vector2Add(body[0], direction));
  if (addSegment == true) {
    addSegment = false;
  } else {
    body.pop_back();
  }
}

void Snake::Reset() {
  body = {Vector2{6, 9}, Vector2{5, 9}, Vector2{4, 9}};
  direction = Vector2{1, 0};
  addSegment = false;
}
