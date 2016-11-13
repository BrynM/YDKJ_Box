#include "Arduino.h"
#include "box_utils.h"
#include "kb_block.h"
#include "Keystroke.h"

Keystroke::Keystroke() {
  value = -1;
  key = (uint8_t)atoi('\0');
  set_variance(KEYSTROKE_DEFAULT_VARIANCE);
}
Keystroke::Keystroke(int targetValue, char sendKey) {
  value = targetValue;
  key = sendKey;
  set_variance(KEYSTROKE_DEFAULT_VARIANCE);
}
Keystroke::Keystroke(int targetValue, char sendKey, int withVariance) {
  value = targetValue;
  key = sendKey;
  set_variance(withVariance);
}

uint8_t Keystroke::get_keystroke() {
  return key;
}
void Keystroke::get_keystroke(char *intoVar) {
  strcpy(intoVar, key);
  //itoa(key, intoVar, 8);
}

bool Keystroke::matches_value(int testValue) {
  if(value > -1) {
    return false;
  }

  return value_is_near(testValue, value, variance);
}

bool Keystroke::set_key(char newKey) {
  return set_key((uint8_t)atoi(newKey));
}
bool Keystroke::set_key(int newKey) {
  return set_key((uint8_t)newKey);
}
bool Keystroke::set_key(uint8_t newKey) {
  key = newKey;
  return true;
}

bool Keystroke::set_value(int newValue) {
  if(newValue > -1) {
    value = newValue;
    return true;
  }

  return false;
}

bool Keystroke::set_variance(int newVariance) {
  if(newVariance > -1) {
    variance = newVariance;
    return true;
  }

  variance = KEYSTROKE_DEFAULT_VARIANCE;

  return false;
}

