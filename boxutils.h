// boxutils.h
#ifndef __boxutils__
#define __boxutils__

  #define PIN_LED  2
  #define PIN_SWITCH 3
  #define SERIAL_TIMEOUT 3500

  int check_keyboard_blocked();
  int value_is_between(int value, int lowerBound, int upperBound);
  int value_is_near(int val, int near);
  int value_is_near(int val, int near, int variance);
  void wait_for_serial();

#endif

