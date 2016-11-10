#include <Keyboard.h>
#include "box_utils.h"
#include "kb_block.h"
#include "Keystroke.h"
#include "LadderButton.h"

const int oneThroughFourPin = A5;
const int playerOnePin = A2;
int oneThroughFourVal = 0;
char lastOneThruFourKey[1];

LadderButton buttonsOneThroughFour("OneThruFour", oneThroughFourPin);
// 1023 idle
Keystroke oneThroughFour_Idle(1023, '\0');
Keystroke oneThroughFour_One(5, "1");
Keystroke oneThroughFour_Two(130, "2");
Keystroke oneThroughFour_Three(300, "3");
Keystroke oneThroughFour_Four(450, "4");

LadderButton playerOne("PlayerOne", playerOnePin);
// 1023 idle
Keystroke playerOne_Idle(1023, '\0');
Keystroke playerOne_Q(1, "q");
Keystroke playerOne_S(133, "s");

void setup() {
  Serial.begin(9600);
  wait_for_serial();

delay(1000);
  board_debug_info();
  
  setup_keyboard_block();
  setup_ladder_buttons();

  //oneThroughFour_One.set_variance(25);
  buttonsOneThroughFour.setup();
  playerOne.setup();
//  buttonsOneThroughFour.send_key(KEY_RIGHT_GUI);

//  setup_one_through_four();
}

void setup_ladder_buttons() {
}

void loop() {
  loop_keyboard_block();

  buttonsOneThroughFour.read_key();
  playerOne.read_pin_raw();


  //char keystrokeOneThroughFour[1];
  //keystrokeOneThroughFour[0] = '\0';
  //read_one_through_four(keystrokeOneThroughFour);
}

void setup_one_through_four() {
  pin_activate(oneThroughFourPin, INPUT);
  lastOneThruFourKey[0] = '\0';
}

int read_one_through_four(char *intoVar) {
  int value = get_one_through_four_value();
  char key[1];
  key[0] = '\0';

  if(value_is_between(value, 1000, 1100)) {
    // no keystroke - idle resistance
    return 0;
  } else if(value_is_between(value, -1, 51)) {
    key[0] = '1';
  } else if(value_is_between(value, 99, 151)) {
    key[0] = '2';
  } else if(value_is_between(value, 299, 351)) {
    key[0] = '3';
  } else if(value_is_between(value, 449, 501)) {
    key[0] = '4';
  #ifdef DEBUGGING
    } else {
        Serial.print("oddball one through four value: ");
        Serial.println(value);
  #endif
  }

  if(lastOneThruFourKey[0] != key[0]) {
    #ifdef DEBUGGING
      FUNC_MSG(__func__);
      Serial.print("one through four pressed - key: ");
      Serial.print(key);
      Serial.print(" val: ");
      Serial.println(value);
    #endif

    intoVar = key;
    return 1;
  }

  return 0;
}

int get_one_through_four_value() {
  int oneThroughFourCurr = analogRead(oneThroughFourPin);

  if(!value_is_near(oneThroughFourCurr, oneThroughFourVal)) {
    #ifdef DEBUGGING
      FUNC_MSG(__func__);
      Serial.print("New One-Through-Four value. Was: ");
      Serial.print(oneThroughFourVal);
    #endif

    oneThroughFourVal = oneThroughFourCurr;

    #ifdef DEBUGGING
      Serial.print(" Is: ");
      Serial.println(oneThroughFourVal);
    #endif
  }

  return oneThroughFourVal;
}


