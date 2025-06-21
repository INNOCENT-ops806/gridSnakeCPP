#include "../include/Utils.h"
#include <raymath.h>

bool ElementInDeque(Vector2 element, std::deque<Vector2> deque) {
  for (unsigned int i = 0; i < deque.size(); i++) {
    if (Vector2Equals(deque[i], element)) {
      return true;
    }
  }
  return false;
}
