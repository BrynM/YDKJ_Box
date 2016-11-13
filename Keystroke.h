// LadderButton.h
#ifndef __Keystroke_h__
#define __Keystroke_h__

  /*
   * Keystroke
   */

  #define KEYSTROKE_DEFAULT_VARIANCE 30

  class Keystroke {
    char key;
    int value;
    int variance;
    
    public:
      Keystroke::Keystroke();
      Keystroke(int targetValue, char sendKey);
      Keystroke::Keystroke(int targetValue, char sendKey, int withVariance);
      uint8_t get_keystroke();
      void get_keystroke(char *intoVar);
      bool matches_value(int value);
      bool set_key(char newKey);
      bool set_key(int newKey);
      bool set_key(uint8_t newKey);
      bool set_value(int newValue);
      bool set_variance(int newVariance);
  };
 
#endif

