#include <iostream>
#include <raylib.h>
using namespace std;

Color green = {173, 204, 96, 255};
Color darkGreen = {123, 50, 250, 235};

int cellSize = 30;
int cellCount = 25;
class Food{
public:
  Vector2 position;

  Food(){
    position = GenerateRandomPos();

  };

  void draw(){
    DrawRectangle(position.x * cellSize,position.y * cellSize,cellSize,cellSize,darkGreen);
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

  while (WindowShouldClose() == false) {
    BeginDrawing();
    ClearBackground(green);
    food.draw();
    EndDrawing();
  } 

  CloseWindow(); 
  return 0;
}

