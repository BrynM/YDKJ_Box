// LadderButton.h
#ifndef __LadderButton__
#define __LadderButton__

  typedef struct keystroke {
    int value;
    int variance;
    char key;
  } keystroke;

  /*
   * LadderButton
   */

  class LadderButton {
    int analogPin;

    int fire_key(char key);
    int fire_key(uint8_t key);
  
    public:
        LadderButton (int onPin);
        keystroke keys[6];
        int add_key (keystroke);
        int match_value (char *intoVar);
        void setup();
  };

  /*
   * Keystroke
   */

  #define DEFAULT_KEYSTROKE_VARIANCE 30

  class Keystroke {
    char key;
    int value;
    int lastValue;
    int variance;
    
    public:
      Keystroke(int targetValue, char sendKey);
      int set_variance(int newVariance);
  };
  
#endif

