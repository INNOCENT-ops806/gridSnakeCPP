
#ifndef __SPLASH_H__
#define __SPLASH_H__

#include <raylib.h>

struct Splash {

public:
  Splash();
  ~Splash();
  void draw();
  bool isComplete();

private:
  int currentFrame = 0;
  int framesCounter = 0;
  int framesSpeed = 8;
  float xPerc = 0.0f;
  bool done = false;

  Texture2D scarfy;
  Vector2 position;
  Rectangle frameRec;
};

#endif // !__SPLASH_H__
