#include "boxutils.h"
#include "LadderButton.h"

const int oneThroughFourPin = A5;
int oneThroughFourVal = 0;
char lastOneThruFourKey[1];

void setup() {
  Serial.begin(9600);
  wait_for_serial();

  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_SWITCH, INPUT);

  pinMode(oneThroughFourPin, INPUT);

  lastOneThruFourKey[0] = '\0';
}

void loop() {
  check_keyboard_blocked();
  char keystrokeOneThroughFour[1];
  keystrokeOneThroughFour[0] = '\0';
  read_one_through_four(keystrokeOneThroughFour);
}

int read_one_through_four(char *intoVar) {
  int value = get_one_through_four_value();
  char key[1];
  key[0] = '\0';

  if(value_is_between(value, 1000, 1100)) {
    // no keystroke - idle resistance
    return 0;
  } else if(value_is_between(value, 0, 50)) {
    key[0] = '1';
  } else if(value_is_between(value, 100, 150)) {
    key[0] = '2';
  } else if(value_is_between(value, 300, 350)) {
    key[0] = '3';
  } else if(value_is_between(value, 450, 500)) {
    key[0] = '4';
  } else {
    Serial.print("oddball one through four value: ");
    Serial.println(value);
  }

  if(lastOneThruFourKey[0] != key[0]) {
    Serial.print("one through four pressed - key: ");
    Serial.print(key);
    Serial.print(" val: ");
    Serial.println(value);
  
    intoVar = key;
    return 1;
  }

  return 0;
}

int get_one_through_four_value() {
  int oneThroughFourCurr = analogRead(oneThroughFourPin);

  if(!value_is_near(oneThroughFourCurr, oneThroughFourVal)) {
    // only print if changed
    Serial.print("New One-Through-Four value. Was: ");
    Serial.print(oneThroughFourVal);
    oneThroughFourVal = oneThroughFourCurr;
    Serial.print(" Is: ");
    Serial.println(oneThroughFourVal);
  }

  return oneThroughFourVal;
}


