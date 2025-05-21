#include <iostream>
#include <raylib.h>
#include <deque>
using namespace std;

Color green = {173, 204, 96, 255};
Color purple = {123, 50, 250, 235};

int cellSize = 30;
int cellCount = 25;

class Snake{

public:
  deque<Vector2> body = {Vector2{6,9}, Vector2{5,9}, Vector2{4,9}};
  void Draw(){
    for(unsigned int i = 0; i < body.size(); i++){
      float x = body[i].x;
      float y = body[i].y;
      Rectangle segment = Rectangle{x * cellSize, y * cellSize, (float)cellSize, float(cellSize)};
      DrawRectangleRounded(segment, 0.5, 6, purple);

    }
  }
};

class Food{

public:
  Vector2 position;

  Food(){
    position = GenerateRandomPos();

  };

  void Draw(){
    DrawRectangle(position.x * cellSize,position.y * cellSize,cellSize,cellSize,purple);
  }

  Vector2 GenerateRandomPos(){
    float x = GetRandomValue(0,cellCount -1);
    float y = GetRandomValue(0,cellSize -1);

    return Vector2{x,y};
  }

};

int main() {

  cout << "Starting the game" << endl;

  InitWindow(cellSize * cellCount,cellSize * cellCount, "Retro Snake");
  SetTargetFPS(60);
  Food food = Food();
  Snake snake = Snake();

  while (WindowShouldClose() == false) {
    BeginDrawing();
    ClearBackground(green);
    food.Draw();
    snake.Draw();
    EndDrawing();
  } 

  CloseWindow(); 
  return 0;
}

