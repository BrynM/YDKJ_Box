#include "Arduino.h"
#include "box_utils.h"
#include "box_boards.h"

int used_box_pins[MAX_BOX_PINS];

void board_debug_info() {
  #ifdef DEBUGGING
    Serial.print("###################################\n");
    Serial.print("#\n");
    Serial.print("# You Don't Know Jack in a Box\n");
    Serial.print("#\n");
    Serial.print("###################################\n");
    Serial.print("# Compiled for ");
    Serial.print(__BOX_BOARD__);
    Serial.println();
    Serial.print("# ");
    Serial.print(__DATE__);
    Serial.print(" ");
    Serial.print(__TIME__);
    Serial.println();
    Serial.print("# libc ");
    Serial.print(__AVR_LIBC_DATE_STRING__);
    Serial.print(" ");
    Serial.print(__AVR_LIBC_VERSION_STRING__);
    Serial.println();
    Serial.print("###################################\n\n");
  #endif
}

int use_pin(int pin, int ioMode) {
  int lastIter = 0;

  for(int i = 0; i < MAX_BOX_PINS; i++) {
    if(used_box_pins[i] == '\0') {
      lastIter = i;
      break;
    }

    if(used_box_pins[i] == pin) {
      #ifdef DEBUGGING
        Serial.print(__func__);
        Serial.print("() failed pin ");
        Serial.print(pin);
        Serial.print(" in slot ");
        Serial.println(i);
      #endif

      return 0;
    }
  }

  used_box_pins[lastIter] = pin;
  pinMode(pin, ioMode);

  #ifdef DEBUGGING
    Serial.print(__func__);
    Serial.print("() reserved pin ");
    Serial.print(pin);
    Serial.print(" in slot ");
    Serial.print(lastIter);
    Serial.print(" (");
    Serial.print(MAX_BOX_PINS - (lastIter + 1));
    Serial.println(" remain)");
  #endif

  return 1;
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
    if((millis() - startMilliS) >= BOX_SERIAL_TIMEOUT) {
      serialBreak = 1;
    }
  }
}

