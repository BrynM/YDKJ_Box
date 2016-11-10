// LadderButton.h
#ifndef __LadderButton_h__
#define __LadderButton_h__

  #include "Keystroke.h"

  #define LADDERBUTTON_DEFAULT_COOLDOWN_MS 50
  #define LADDERBUTTON_EMPTY_PIN -1
  // LADDERBUTTON_MAX_KEYS 9 is 8 buttons/keys plus idle
  #define LADDERBUTTON_MAX_KEYS 9
  #define LADDERBUTTON_NAME_SIZE 36

  class LadderButton {
    int analogPin;
    char instanceName[LADDERBUTTON_NAME_SIZE];
    int keyCount;
    Keystroke keys[LADDERBUTTON_MAX_KEYS];
    int ladderButtonIndex;
    bool pinActive;
    int pinValue;
    int lastPinCheck;
    int cooldownMs;

    void generate_instance_name(char *intoVar);
    bool init_members(int onPin, int withCooldownMs);
    bool init_members(char *lbName, int onPin, int withCooldownMs);
    bool pin_active(bool setTo);

    public:
        LadderButton::LadderButton();
        LadderButton::LadderButton(char *lbName);
        LadderButton::LadderButton(int onPin);
        LadderButton::LadderButton(char *lbName, int onPin);
        LadderButton::LadderButton(int onPin, int withCooldownMs);
        LadderButton::LadderButton(char *lbName, int onPin, int withCooldownMs);
        bool activate();
        bool add_key(Keystroke key);
        bool pin_active();
        bool read_key(char *intoVar);
        int read_pin_raw();
        int read_pin();
        bool send_key(char key);
        bool send_key(int key);
        bool send_key(uint8_t key);
        bool set_analog_pin(int newAnalogPin);
        bool set_cooldown_ms(int newCoolMs);
        bool setup();
  };

#endif

