#include "Arduino.h"
#include "box_utils.h"
#include "kb_block.h"

int keyboardBlocked = 3;
int keyboardBlockedState = LOW;

int check_keyboard_block() {
  return keyboardBlocked;
}

void loop_keyboard_block() {
  if(KEYBOARD_BLOCK_LOOP_THROTTLE > 1 && millis() % KEYBOARD_BLOCK_LOOP_THROTTLE == 0) {
    int kbSwitchState = digitalRead(KEYBOARD_BLOCK_PIN_SWITCH);
  
    if (kbSwitchState == keyboardBlockedState) {
      digitalWrite(KEYBOARD_BLOCK_PIN_LED, HIGH);

      #ifdef DEBUGGING
        if(keyboardBlocked != kbSwitchState) {
          FUNC_MSG(__func__);
          Serial.println("enabled");
        }
      #endif
    } else {
      digitalWrite(KEYBOARD_BLOCK_PIN_LED, LOW);

      #ifdef DEBUGGING
        if(keyboardBlocked != kbSwitchState) {
          FUNC_MSG(__func__);
          Serial.println("disabled");
        }
      #endif
    }
  
    keyboardBlocked = kbSwitchState;
  }
}

void setup_keyboard_block() {
  use_pin(KEYBOARD_BLOCK_PIN_LED, OUTPUT);
  use_pin(KEYBOARD_BLOCK_PIN_SWITCH, INPUT);
}

