typedef struct keystroke {
  int value;
  int variance;
  char keystroke[1];
} keystroke;

class LadderButton {
  int pin;

  public:
      LadderButton (int onPin);
      keystroke keys[6];
      int match_value (char *intoVar);
};


