// box_utils.h
#ifndef __box_utils__
#define __box_utils__

  #define BOX_DEBUG 1
  #define BOX_SERIAL_TIMEOUT 3500
  #define MAX_BOX_PINS 30

  void board_debug_info();
  int value_is_between(int value, int lowerBound, int upperBound);
  int value_is_near(int val, int near);
  int value_is_near(int val, int near, int variance);
  int use_pin(int pin, int ioMode);
  void wait_for_serial();

  #if defined (BOX_DEBUG) && BOX_DEBUG > 0
    #define DEBUGGING 1
  #endif
#endif

