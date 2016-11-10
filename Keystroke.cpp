#include "Arduino.h"
#include "box_utils.h"
#include "kb_block.h"
#include "Keystroke.h"

Keystroke::Keystroke() {
  value = -1;
  key = '\0';
  variance = -1;
}
Keystroke::Keystroke(int targetValue, char sendKey) {
  value = targetValue;
  key = sendKey;
  set_variance(DEFAULT_KEYSTROKE_VARIANCE);
}
Keystroke::Keystroke(int targetValue, char sendKey, int withVariance) {
  value = targetValue;
  key = sendKey;
  set_variance(withVariance);
}

int Keystroke::set_key(char newKey) {
  return set_key((uint8_t)atoi(newKey));
}
int Keystroke::set_key(int newKey) {
  return set_key((uint8_t)newKey);
}
int Keystroke::set_key(uint8_t newKey) {
  key = newKey;
  return 1;
}

int Keystroke::set_value(int newValue) {
  if(newValue > -1) {
    value = newValue;
    return 1;
  }

  return 0;
}

int Keystroke::set_variance(int newVariance) {
  if(newVariance > -1) {
    variance = newVariance;
    return 1;
  }

  variance = 0;

  return 0;
}

