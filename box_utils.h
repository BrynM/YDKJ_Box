// box_utils.h
#ifndef __box_utils_h__
#define __box_utils_h__

  #define BOX_DEBUG 1
  #define BOX_SERIAL_TIMEOUT 3500
  #define BOX_WEBSITE "https://github.com/BrynM/YDKJ_Box"
  #define FUNC_ANNOUNCE_PREFIX "@"
  #define FUNC_ANNOUNCE_SUFFIX " # "
  #define MAX_BOX_PINS 30

  void board_debug_info();
  void serial_timestamp();
  void serial_timestamp(char *funcName);
  void serial_timestamp(char *className, char *funcName);
  int pin_activate(int pin, int ioMode);
  int value_is_between(int value, int lowerBound, int upperBound);
  int value_is_near(int val, int near);
  int value_is_near(int val, int near, int variance);
  void wait_for_serial();

  #define FUNC_MSG(f) \
    ( \
      (serial_timestamp(f)), \
      (void)0 \
    )

  #define CLASS_MSG(c, f) \
    ( \
      (serial_timestamp(c, f)), \
      (void)0 \
    )

  #if defined (BOX_DEBUG) && BOX_DEBUG > 1
    #define DEBUGGING 1
    #define NOISY_DEBUGGING 1
  #elif defined (BOX_DEBUG) && BOX_DEBUG > 0
    #define DEBUGGING 1
  #endif
#endif

