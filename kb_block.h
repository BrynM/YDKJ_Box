// kb_block.h
#ifndef __kb_block__
#define __kb_block__

  #define KEYBOARD_BLOCK_PIN_LED  2
  #define KEYBOARD_BLOCK_PIN_SWITCH 3
  #define KEYBOARD_BLOCK_LOOP_THROTTLE 100

  int check_keyboard_block();
  void loop_keyboard_block();
  void setup_keyboard_block();

#endif

