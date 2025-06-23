#pragma once
#include <raylib.h>
#include <string>
#include <vector>

class Menu {
public:
  Menu();
  void Update();
  void Draw();
  bool IsComplete() const;
  int GetSelectedOption() const;

private:
  bool m_isComplete;
  int m_selectedIndex;
  std::vector<std::string> m_options;
  Vector2 GetTextPosition(const char *text, int fontSize, int screenWidth,
                          int screenHeight, int totalMenuHeight,
                          int optionIndex);
};
