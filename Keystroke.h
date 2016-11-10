// LadderButton.h
#ifndef __Keystroke_h__
#define __Keystroke_h__

  /*
   * Keystroke
   */

  #define DEFAULT_KEYSTROKE_VARIANCE 30

  class Keystroke {
    char key;
    int value;
    int variance;
    
    public:
      Keystroke::Keystroke();
      Keystroke(int targetValue, char sendKey);
      Keystroke::Keystroke(int targetValue, char sendKey, int withVariance);
      int set_key(char newKey);
      int set_key(int newKey);
      int set_key(uint8_t newKey);
      int set_value(int newValue);
      int set_variance(int newVariance);
  };
 
#endif

