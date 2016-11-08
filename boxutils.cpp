#include "Arduino.h"
#include "boxutils.h"

int keyboardBlocked = 3;
int keyboardBlockedState = LOW;

int check_keyboard_blocked() {
  int kbSwitchState = digitalRead(PIN_SWITCH);

  if (kbSwitchState == keyboardBlockedState) {
    digitalWrite(PIN_LED, HIGH);
    if(keyboardBlocked != kbSwitchState) {
      Serial.println("keyboard block enabled");
    }
  } else {
    digitalWrite(PIN_LED, LOW);
    if(keyboardBlocked != kbSwitchState) {
      Serial.println("keyboard block disabled");
    }
  }

  keyboardBlocked = kbSwitchState;

  return keyboardBlocked;
}

int value_is_between(int value, int lowerBound, int upperBound) {
  return (value >= lowerBound && value <= upperBound);
}

int value_is_near(int val, int near) {
  return value_is_near(val, near, 10);
}
int value_is_near(int val, int near, int variance) {
  return (val >= (near - variance) && val <= (near+variance));
}

void wait_for_serial() {
  int serialBreak = 0;
  int startMilliS = millis();
  
  while (!Serial && !serialBreak) {
    if((millis() - startMilliS) >= SERIAL_TIMEOUT) {
      serialBreak = 1;
    }
  }
}


