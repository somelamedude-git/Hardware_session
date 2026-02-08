const int buttonPin = 2;
volatile bool pressed = false;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(2), buttonPressed, FALLING);
}

void loop() {
  if (pressed) {
    Serial.println("BUTTON!");
    pressed = false;
  }
}

void buttonPressed() {
  pressed = true;
}
