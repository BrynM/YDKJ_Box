#include "Arduino.h"
#include <Keyboard.h>
#include "box_utils.h"
#include "kb_block.h"
#include "Keystroke.h"
#include "LadderButton.h"

int keyboardLibBegun = 0;
int ladderButtonCount = 0;

LadderButton::LadderButton() {
  init_members(LADDERBUTTON_EMPTY_PIN, LADDERBUTTON_DEFAULT_PIN_COOLDOWN_MS);
}
LadderButton::LadderButton(char *lbName) {
  init_members(lbName, LADDERBUTTON_EMPTY_PIN, LADDERBUTTON_DEFAULT_PIN_COOLDOWN_MS);
}
LadderButton::LadderButton(int onPin) {
  init_members(onPin, LADDERBUTTON_DEFAULT_PIN_COOLDOWN_MS);
}
LadderButton::LadderButton(char *lbName, int onPin) {
  init_members(lbName, onPin, LADDERBUTTON_DEFAULT_PIN_COOLDOWN_MS);
}
LadderButton::LadderButton(int onPin, int withCooldownMsPin) {
  init_members(onPin, withCooldownMsPin);
}
LadderButton::LadderButton(char *lbName, int onPin, int withCooldownMsPin) {
  init_members(lbName, onPin, withCooldownMsPin);
}

bool LadderButton::activate() {
  if(!pin_activate(analogPin, INPUT)) {
    pin_active(false);

    return false;
  }

  pin_active(true);

  return true;
}

bool LadderButton::add_key(Keystroke key) {
return false;
}

void  LadderButton::generate_instance_name(char *intoVar) {
  itoa(ladderButtonCount, intoVar, 10);
  strcat(intoVar, " LadderButton");
}

bool LadderButton::init_members(int onPin, int withCooldownMsPin) {
  keyCount = 0;
  lastPinCheck = millis();
  pinValue = 0;

  char dummyBuff[LADDERBUTTON_NAME_SIZE];

  return init_members(onPin, withCooldownMsPin, dummyBuff);
}
bool LadderButton::init_members(char *lbName, int onPin, int withCooldownMsPin) {
  keyCount = 0;
  lastPinCheck = millis();
  pinValue = 0;

  if(strlen(lbName) != 0) {
    strcpy(instanceName, lbName);
  } else {
    generate_instance_name(instanceName);
  }

  ladderButtonIndex = ladderButtonCount;
  ladderButtonCount++;

  if(set_analog_pin(onPin) && set_cooldown_ms_pin(withCooldownMsPin)) {
    #ifdef DEBUGGING
      CLASS_MSG(instanceName, __func__);
      Serial.println("Finished initialization.");
    #endif

    return true;
  }

  #ifdef DEBUGGING
    CLASS_MSG(instanceName, __func__);
    Serial.println("FAILED initialization.");
  #endif

  return false;
}

bool LadderButton::pin_active() {
  return pinActive;
}
bool LadderButton::pin_active(bool setTo) {
  if(setTo) {
    pinActive = true;
  } else {
    pinActive = false;
  }

  #ifdef DEBUGGING
    CLASS_MSG(instanceName, __func__);
    Serial.print("Set pin ");
    Serial.print(analogPin);
    Serial.print(" active state to ");
    Serial.println(pinActive);
  #endif

  return pinActive;
}

bool LadderButton::read_key() {
  char dummyBuff;
  return read_key(dummyBuff);
}
bool LadderButton::read_key(char *intoVar) {
  int currValue = read_pin_raw();
}

int LadderButton::read_pin_raw() {
  if(analogPin < 0) {
    #ifdef DEBUGGING
      CLASS_MSG(instanceName, __func__);
      Serial.print("Pin ");
      Serial.print(analogPin);
      Serial.print(" is invalid (too low).");
    #endif

    return -1;
  }

  if(!pin_active()) {
    #ifdef NOISY_DEBUGGING
      CLASS_MSG(instanceName, __func__);
      Serial.print("Pin ");
      Serial.print(analogPin);
      Serial.print(" is not active (");
      Serial.print(pinActive);
      Serial.println(").");
    #endif

    return -1;
  }

  int elapsed = millis() - lastPinCheck;

  if(elapsed < cooldownMsPin) {
    #ifdef NOISY_DEBUGGING
      CLASS_MSG(instanceName, __func__);
      Serial.print("Pin ");
      Serial.print(analogPin);
      Serial.print(" is still cooling down (");
      Serial.print(elapsed);
      Serial.print(" < ");
      Serial.print(cooldownMsPin);
      Serial.println(").");
    #endif

    return pinValue;
  }

  int pinCurr = analogRead(analogPin);

  if(!value_is_near(pinCurr, pinValue)) {
    #ifdef DEBUGGING
      CLASS_MSG(instanceName, __func__);
      Serial.print("Reading pin ");
      Serial.print(analogPin);
      Serial.print(" Was: ");
      Serial.print(pinValue);
    #endif

    pinValue = pinCurr;
  
    #ifdef DEBUGGING
      Serial.print(" Is: ");
      Serial.println(pinValue);
    #endif
  #ifdef NOISY_DEBUGGING
  } else {
    CLASS_MSG(instanceName, __func__);
    Serial.print("Pin ");
    Serial.print(analogPin);
    Serial.print(" has not changed value (");
    Serial.print(pinValue);
    Serial.println(").");
  #endif
  }

  lastPinCheck = millis();

  return pinValue;
}

bool LadderButton::send_key(char key) {
  if(check_keyboard_block()) {
    #ifdef DEBUGGING
      CLASS_MSG(instanceName, __func__);
      Serial.print("Keyboard blocked. Cannot sent keystroke \"");
      Serial.print(key);
      Serial.print("\" for pin ");
      Serial.println(analogPin);
    #endif

    return false;
  }

  #ifdef DEBUGGING
    CLASS_MSG(instanceName, __func__);
    Serial.print("Sending keystroke \"");
    Serial.print(key);
    Serial.print("\" for pin ");
    Serial.println(analogPin);
  #endif

  Keyboard.write(key);

  return true;
}
bool LadderButton::send_key(int key) {
  return send_key((uint8_t)key);
}
bool LadderButton::send_key(uint8_t key) {
  if(check_keyboard_block()) {
    #ifdef DEBUGGING
      CLASS_MSG(instanceName, __func__);
      Serial.print("Keyboard blocked. Cannot sent key \"");
      char buff[3];
      itoa(buff, key, 10);
      Serial.print(buff);
      Serial.print("\" (");
      Serial.print(key);
      Serial.print(") for pin ");
      Serial.println(analogPin);
    #endif

    return false;
  }

  #ifdef DEBUGGING
    CLASS_MSG(instanceName, __func__);
    Serial.print("Sending \"");
    char buff[3];
    itoa(buff, key, 10);
    Serial.print(buff);
    Serial.print("\" (");
    Serial.print(key);
    Serial.print(") to keyboard from pin ");
    Serial.println(analogPin);
  #endif

  Keyboard.write(key);

  return true;
}

bool LadderButton::set_analog_pin(int newAnalogPin) {
  if(newAnalogPin > -1) {
    if(newAnalogPin == analogPin) {
      #ifdef DEBUGGING
        CLASS_MSG(instanceName, __func__);
        Serial.print("Analog pin ");
        Serial.print(analogPin);
        Serial.println(" unchanged.");
      #endif

      return false;
    }

    analogPin = newAnalogPin;

    #ifdef DEBUGGING
      CLASS_MSG(instanceName, __func__);
      Serial.print("Analog pin set to ");
      Serial.println(analogPin);
    #endif

    return true;
  } 

  analogPin = LADDERBUTTON_EMPTY_PIN;

  if(newAnalogPin == LADDERBUTTON_EMPTY_PIN) {
    // desired an emptying of the pin
    return true;
  }

  return false;
}

bool LadderButton::set_cooldown_ms_pin(int newCoolMs) {
  if(newCoolMs > -1) {
    if(newCoolMs == cooldownMsPin) {
      #ifdef DEBUGGING
        CLASS_MSG(instanceName, __func__);
        Serial.print("Pin cooldown ");
        Serial.print(analogPin);
        Serial.print(" unchanged ");
        Serial.println(cooldownMsPin);
      #endif
      return false;
    }

    cooldownMsPin = newCoolMs;

    return true;
  }

  cooldownMsPin = LADDERBUTTON_DEFAULT_PIN_COOLDOWN_MS;

  #ifdef DEBUGGING
    CLASS_MSG(instanceName, __func__);
    Serial.print("Pin cooldown ");
    Serial.print(analogPin);
    Serial.print(" fell back to default cooldown milliseconds ");
    Serial.println(cooldownMsPin);
  #endif

  return false;
}

bool LadderButton::set_cooldown_ms_key(int newCoolMs) {
  if(newCoolMs > -1) {
    if(newCoolMs == cooldownMsKey) {
      #ifdef DEBUGGING
        CLASS_MSG(instanceName, __func__);
        Serial.print("Key cooldown ");
        Serial.print(analogPin);
        Serial.print(" unchanged ");
        Serial.println(cooldownMsKey);
      #endif
      return false;
    }

    cooldownMsKey = newCoolMs;

    return true;
  }

  cooldownMsKey = LADDERBUTTON_DEFAULT_KEY_COOLDOWN_MS;

  #ifdef DEBUGGING
    CLASS_MSG(instanceName, __func__);
    Serial.print("Key cooldown ");
    Serial.print(analogPin);
    Serial.print(" fell back to default cooldown milliseconds ");
    Serial.println(cooldownMsKey);
  #endif

  return false;
}

bool LadderButton::setup() {
  if(!activate()) {
    #ifdef DEBUGGING
      CLASS_MSG(instanceName, __func__);
      Serial.print("Failed to activate analog pin ");
      Serial.println(analogPin);
    #endif

    return false;
  }

  if(!keyboardLibBegun) {
    keyboardLibBegun = 1;
    Keyboard.begin();

    #ifdef DEBUGGING
      CLASS_MSG(instanceName, __func__);
      Serial.println("Started global HID Keyboard.");
    #endif
  }

  return true;
}

/*

also: http://www.usb.org/developers/hidpage/Hut1_12v2.pdf

key hex dec
-----------
KEY_LEFT_CTRL 0x80  128
KEY_LEFT_SHIFT  0x81  129
KEY_LEFT_ALT  0x82  130
KEY_LEFT_GUI  0x83  131
KEY_RIGHT_CTRL  0x84  132
KEY_RIGHT_SHIFT 0x85  133
KEY_RIGHT_ALT 0x86  134
KEY_RIGHT_GUI 0x87  135
KEY_UP_ARROW  0xDA  218
KEY_DOWN_ARROW  0xD9  217
KEY_LEFT_ARROW  0xD8  216
KEY_RIGHT_ARROW 0xD7  215
KEY_BACKSPACE 0xB2  178
KEY_TAB 0xB3  179
KEY_RETURN  0xB0  176
KEY_ESC 0xB1  177
KEY_INSERT  0xD1  209
KEY_DELETE  0xD4  212
KEY_PAGE_UP 0xD3  211
KEY_PAGE_DOWN 0xD6  214
KEY_HOME  0xD2  210
KEY_END 0xD5  213
KEY_CAPS_LOCK 0xC1  193
KEY_F1  0xC2  194
KEY_F2  0xC3  195
KEY_F3  0xC4  196
KEY_F4  0xC5  197
KEY_F5  0xC6  198
KEY_F6  0xC7  199
KEY_F7  0xC8  200
KEY_F8  0xC9  201
KEY_F9  0xCA  202
KEY_F10 0xCB  203
KEY_F11 0xCC  204
KEY_F12 0xCD  205
*/

