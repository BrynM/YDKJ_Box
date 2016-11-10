#include "Arduino.h"
#include "box_utils.h"
#include "kb_block.h"

int keyboardBlocked = 3;
int keyboardBlockedState = LOW;

int check_keyboard_block() {
  return (keyboardBlocked > 0);
}

void loop_keyboard_block() {
  if(KEYBOARD_BLOCK_LOOP_THROTTLE > 1 && millis() % KEYBOARD_BLOCK_LOOP_THROTTLE == 0) {
    int kbSwitchState = digitalRead(KEYBOARD_BLOCK_PIN_SWITCH);
  
    if (kbSwitchState == keyboardBlockedState) {
      digitalWrite(KEYBOARD_BLOCK_PIN_LED, HIGH);

      #ifdef DEBUGGING
        if(keyboardBlocked != kbSwitchState) {
          FUNC_MSG(__func__);
          Serial.println("Enabled");
        }
      #endif
    } else {
      digitalWrite(KEYBOARD_BLOCK_PIN_LED, LOW);

      #ifdef DEBUGGING
        if(keyboardBlocked != kbSwitchState) {
          FUNC_MSG(__func__);
          Serial.println("Disabled");
        }
      #endif
    }
  
    keyboardBlocked = kbSwitchState;
  }
}

void setup_keyboard_block() {
  #ifdef DEBUGGING
    FUNC_MSG(__func__);
    Serial.print("Setting up keyboard block switch on pin ");
    Serial.print(KEYBOARD_BLOCK_PIN_SWITCH);
    Serial.print(" with LED on pin ");
    Serial.println(KEYBOARD_BLOCK_PIN_LED);
  #endif

  pin_activate(KEYBOARD_BLOCK_PIN_LED, OUTPUT);
  pin_activate(KEYBOARD_BLOCK_PIN_SWITCH, INPUT);
  // get the first loop in
  loop_keyboard_block();
}

