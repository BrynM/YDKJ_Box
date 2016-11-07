// https://github.com/aron-bordin/PNG-Arduino-Framework

const int switchPin = 3;
const int ledPin =  2;
const int oneThroughFourPin = A5;

int keyboardBlocked = 3;
int keyboardBlockedState = LOW;
int oneThroughFourVal = 0;
int serialTimeout = 3500;

void setup() {
  Serial.begin(9600);
  wait_for_serial();

  pinMode(switchPin, INPUT);
  pinMode(oneThroughFourPin, INPUT);

  pinMode(ledPin, OUTPUT);
}

int value_is_between(int value, int lowerBound, int upperBound) {
  Serial.print("checking value ");
  Serial.print(value);
  Serial.print(" is between ");
  Serial.print(lowerBound);
  Serial.print(" and ");
  Serial.println(upperBound);
  return (int) (value >= lowerBound && value <= upperBound);
}

void loop() {
  check_keyboard_blocked();
  char keystrokeOneThroughFour[1];
  read_one_through_four(keystrokeOneThroughFour);
}

int read_one_through_four(char *intoVar) {
  int value = get_one_through_four_value();
  char key[1];
  key[0] = '\0';

  if(value_is_between(value, 1000, 1100)) {
    // no keystroke - idle resistance
    return 0;
  } else if(value_is_between(value, 0, 50)) {
    key[0] = '1';
  } else if(value_is_between(value, 100, 150)) {
    key[0] = '2';
  } else if(value_is_between(value, 300, 350)) {
    key[0] = '3';
  } else if(value_is_between(value, 450, 500)) {
    key[0] = '4';
  } else {
    Serial.print("oddball one through four value: ");
    Serial.println(value);
    return 0;
  }

  Serial.print("one through four pressed - key: ");
  Serial.println(key);

  intoVar = key;
  return 1;
}

int get_one_through_four_value() {
  int oneThroughFourCurr = analogRead(oneThroughFourPin);

  if(oneThroughFourCurr != oneThroughFourVal) {
    // only print if changed
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


