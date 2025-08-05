#include "../include/Menu.h"
#include "../include/Config.h"
#include <raylib.h>
#include <raymath.h>

Menu::Menu() : m_isComplete(false), m_selectedIndex(0) {
  m_options.push_back("New Game");
  m_options.push_back("Press [esc] or [Q] to Quit");
  m_options.push_back("[H] - To pause | resume game");
}

Vector2 Menu::GetTextPosition(const char *text, int fontSize, int screenWidth,
                              int screenHeight, int totalMenuHeight,
                              int optionIndex) {
  Vector2 textSize = MeasureTextEx(GetFontDefault(), text, fontSize, 0);
  float x = (screenWidth - textSize.x) / 2;
  float startY = (float)(screenHeight - totalMenuHeight) / 2;
  float y = startY + (optionIndex * (textSize.y + screenHeight * 0.02));
  return {x, y};
}

void Menu::Update() {
  if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) {
    m_selectedIndex--;
    if (m_selectedIndex < 0) {
      m_selectedIndex = static_cast<int>(m_options.size()) - 1;
    }
  } else if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) {
    m_selectedIndex++;
    if (m_selectedIndex >= static_cast<int>(m_options.size())) {
      m_selectedIndex = 0;
    }
  }

  if (IsKeyPressed(KEY_ENTER)) {
    m_isComplete = true;
  }
}

void Menu::Draw() {
  int currentScreenWidth = GetScreenWidth();
  int currentScreenHeight = GetScreenHeight();

  ClearBackground(BLACK);

  int menuFontSize = currentScreenWidth * 0.035;
  if (menuFontSize < 20)
    menuFontSize = 20;
  if (menuFontSize > 100)
    menuFontSize = 100;

  float lineHeight = MeasureTextEx(GetFontDefault(), "M", menuFontSize, 0).y;
  float totalMenuHeight = (lineHeight * m_options.size()) +
                          (currentScreenHeight * 0.02 * (m_options.size() - 1));

  for (size_t i = 0; i < m_options.size(); ++i) {
    Color textColor =
        (i == static_cast<size_t>(m_selectedIndex)) ? MAGENTA : RAYWHITE;
    const char *optionText = m_options[i].c_str();

    Vector2 textPos =
        GetTextPosition(optionText, menuFontSize, currentScreenWidth,
                        currentScreenHeight, totalMenuHeight, i);

    DrawText(optionText, textPos.x, textPos.y, menuFontSize, textColor);
  }
}

bool Menu::IsComplete() const { return m_isComplete; }

int Menu::GetSelectedOption() const { return m_selectedIndex; }
