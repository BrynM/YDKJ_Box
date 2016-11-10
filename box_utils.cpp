#include "Arduino.h"
#include "box_utils.h"
#include "box_boards.h"

int used_box_pins[MAX_BOX_PINS];

void board_debug_info() {
  #ifdef DEBUGGING
    Serial.print("########################################\n");
    Serial.print("#\n");
    Serial.print("# You Don't Know Jack in a Box\n");
    Serial.print("#\n");
    Serial.print("########################################\n");
    Serial.print("# ");
    Serial.print(BOX_WEBSITE);
    Serial.println();
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
    Serial.print("########################################\n\n");
  #endif
}

void serial_timestamp() {
  #ifdef DEBUGGING
    Serial.print(FUNC_ANNOUNCE_PREFIX);
    Serial.print(millis());
    Serial.print(FUNC_ANNOUNCE_SUFFIX);
  #endif
}

void serial_timestamp(char *funcName) {
  #ifdef DEBUGGING
    Serial.print(FUNC_ANNOUNCE_PREFIX);
    Serial.print(millis());
    Serial.print("ms # ");
    Serial.print(funcName);
    Serial.print("()");
    Serial.print(FUNC_ANNOUNCE_SUFFIX);
  #endif
}

void serial_timestamp(char *className, char *funcName) {
  #ifdef DEBUGGING
    Serial.print(FUNC_ANNOUNCE_PREFIX);
    Serial.print(millis());
    Serial.print("ms # ");
    Serial.print(className);
    Serial.print("::");
    Serial.print(funcName);
    Serial.print("()");
    Serial.print(FUNC_ANNOUNCE_SUFFIX);
  #endif
}


int pin_activate(int pin, int ioMode) {
  int lastIter = 0;

  for(int i = 0; i < MAX_BOX_PINS; i++) {
    if(used_box_pins[i] == '\0') {
      lastIter = i;
      break;
    }

    if(used_box_pins[i] == pin) {
      #ifdef DEBUGGING
        FUNC_MSG(__func__);
        Serial.print("Failed pin ");
        Serial.print(pin);
        Serial.print(" slot ");
        Serial.println(i);
      #endif

      return 0;
    }
  }

  used_box_pins[lastIter] = pin;
  pinMode(pin, ioMode);

  #ifdef DEBUGGING
    FUNC_MSG(__func__);
    Serial.print("Reserved pin ");
    Serial.print(pin);
    Serial.print(" slot ");
    Serial.print(lastIter);
    Serial.print(" (");
    Serial.print(MAX_BOX_PINS - (lastIter + 1));
    Serial.println(" remain)");
  #endif

  return 1;
}

int value_is_between(int value, int lowerBound, int upperBound) {
  return (value > lowerBound && value < upperBound);
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

