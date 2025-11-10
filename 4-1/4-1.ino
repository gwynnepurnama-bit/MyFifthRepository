const int buttonPin = 2;   // button module signal pin
const int ledPin = 3;      // LED pin
int buttonState = 0;       // variable to read button state

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP); // use internal pull-up resistor
}

void loop() {
  buttonState = digitalRead(buttonPin); // read button state

  if (buttonState == LOW) {  // button pressed (LOW when using pull-up)
    digitalWrite(ledPin, HIGH); // turn LED ON
  } else {
    digitalWrite(ledPin, LOW);  // turn LED OFF
  }
}

