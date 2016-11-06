// https://github.com/aron-bordin/PNG-Arduino-Framework

const int switchPin = 4;
const int ledPin =  2;
const int oneThroughFourPin = A5;

int keyboardBlocked = 3;
int keyboardBlockedState = LOW;
int oneThroughFourVal = 0;
int serialTimeout = 3500;

class ButtonGroup {
  int pin;
  int lastVal;
  int currVal;
};

class Button {
  int value;
  ButtonGroup group;
};

void setup() {
  Serial.begin(9600);
  wait_for_serial();

  pinMode(switchPin, INPUT);
  pinMode(oneThroughFourPin, INPUT);

  pinMode(ledPin, OUTPUT);
}

void loop() {
  check_keyboard_blocked();
  get_one_through_four_value();
}

int get_one_through_four_value() {
  int oneThroughFourCurr = analogRead(oneThroughFourPin);

  if(oneThroughFourCurr != oneThroughFourVal) {
    Serial.print("New One-Through-Four value. Was: ");
    Serial.print(oneThroughFourVal);
    oneThroughFourVal = oneThroughFourCurr;
    Serial.print(" Is: ");
    Serial.println(oneThroughFourVal);
  }

  
}

int check_keyboard_blocked() {
  int kbSwitchState = digitalRead(switchPin);

  if (kbSwitchState == keyboardBlockedState) {
    digitalWrite(ledPin, HIGH);
    if(keyboardBlocked != kbSwitchState) {
      Serial.println("keyboard block enabled");
    }
  } else {
    digitalWrite(ledPin, LOW);
    if(keyboardBlocked != kbSwitchState) {
      Serial.println("keyboard block disabled");
    }
  }

  keyboardBlocked = kbSwitchState;

  return keyboardBlocked;
}

void wait_for_serial() {
  int serialBreak = 0;
  int startMilliS = millis();
  
  while (!Serial && !serialBreak) {
    if((millis() - startMilliS) >= serialTimeout) {
      serialBreak = 1;
    }
  }
}


