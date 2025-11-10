const int buttonPin = 2;   // button module signal pin
const int ledPin = 3;      // LED pin
int buttonState = 0;       // variable to store button state

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP); // use internal pull-up resistor
}

void loop() {
  buttonState = digitalRead(buttonPin); // read button state

  if (buttonState == LOW) {    // button pressed
    digitalWrite(ledPin, LOW); // turn LED OFF
  } else {
    digitalWrite(ledPin, HIGH); // turn LED ON
  }
}
