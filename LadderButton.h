// LadderButton.h
#ifndef __LadderButton_h__
#define __LadderButton_h__

  #include "Keystroke.h"

  #define LADDERBUTTON_DEFAULT_KEY_COOLDOWN_MS 50
  #define LADDERBUTTON_DEFAULT_PIN_COOLDOWN_MS 50
  #define LADDERBUTTON_EMPTY_PIN -1
  // LADDERBUTTON_MAX_KEYS 9 is 8 buttons/keys plus idle
  #define LADDERBUTTON_MAX_KEYS 9
  #define LADDERBUTTON_NAME_SIZE 36

  class LadderButton {
    int analogPin;
    int cooldownMsKey;
    int cooldownMsPin;
    char instanceName[LADDERBUTTON_NAME_SIZE];
    int keyCount;
    Keystroke keys[LADDERBUTTON_MAX_KEYS];
    int ladderButtonIndex;
    int lastKeyCheck;
    int lastPinCheck;
    bool pinActive;
    int pinValue;

    void generate_instance_name(char *intoVar);
    bool init_members(int onPin, int withCooldownMsPin);
    bool init_members(char *lbName, int onPin, int withCooldownMsPin);
    bool pin_active(bool setTo);

    public:
        LadderButton::LadderButton();
        LadderButton::LadderButton(char *lbName);
        LadderButton::LadderButton(int onPin);
        LadderButton::LadderButton(char *lbName, int onPin);
        LadderButton::LadderButton(int onPin, int withCooldownMsPin);
        LadderButton::LadderButton(int onPin, int withCooldownMsPin, int withCooldownMsKey);
        LadderButton::LadderButton(char *lbName, int onPin, int withCooldownMsPin);
        LadderButton::LadderButton(char *lbName, int onPin, int withCooldownMsPin, int withCooldownMsKey);
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
        bool set_cooldown_ms_pin(int newCoolMs);
        bool set_cooldown_ms_key(int newCoolMs);
        bool setup();
  };

#endif

