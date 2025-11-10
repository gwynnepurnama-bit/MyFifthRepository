// Improved: 4-mode LED controller with reliable debounce and clean timing
const int buttonPin = 2;   // button connected to D2 (use INPUT_PULLUP wiring)
const int ledPin    = 3;   // LED connected to D3 (through 220Ω resistor to anode), cathode -> GND

// Debounce variables
int reading = HIGH;
int lastReading = HIGH;
int buttonState = HIGH;          // stable state
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50;

// Mode: 0=steady, 1=slow, 2=medium, 3=fast
int mode = 0;

// Blinking control
bool ledState = true;
unsigned long previousMillis = 0;
const unsigned long intervals[] = {0, 1000, 500, 200}; // period (ms) for modes 1..3 (we'll toggle every interval/2)

void setup() {
  pinMode(buttonPin, INPUT_PULLUP); // button must connect to GND when pressed
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);       // start with steady ON
  ledState = true;
  previousMillis = millis();

  Serial.begin(9600); // optional - helps debug mode changes
  Serial.println("Ready");
}

void loop() {
  reading = digitalRead(buttonPin);

  // --- Debounce logic (standard pattern) ---
  if (reading != lastReading) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // if the reading has been stable longer than the debounce delay, take it as the actual state
    if (reading != buttonState) {
      buttonState = reading;
      if (buttonState == LOW) { // button pressed (using INPUT_PULLUP)
        // change mode on press (only once per press)
        mode = (mode + 1) % 4;
        // reset blink timing and set a known led state when switching modes
        previousMillis = millis();
        if (mode == 0) {
          ledState = true;         // steady ON
          digitalWrite(ledPin, HIGH);
        } else {
          // start blink with LED ON so toggles happen predictably
          ledState = true;
          digitalWrite(ledPin, HIGH);
        }
        Serial.print("Mode: ");
        Serial.println(mode);
      }
    }
  }

  lastReading = reading;

  // --- LED behavior based on mode ---
  unsigned long currentMillis = millis();

  if (mode == 0) {
    // steady ON
    if (!ledState) {
      ledState = true;
      digitalWrite(ledPin, HIGH);
    }
  } else {
    // blinking modes 1..3
    unsigned long period = intervals[mode]; // full period in ms (e.g., 1000)
    // toggle every period/2 to create that full "period"
    unsigned long halfPeriod = period / 2;
    if (halfPeriod == 0) halfPeriod = 1; // safety

    if (currentMillis - previousMillis >= halfPeriod) {
      previousMillis = currentMillis;
      ledState = !ledState;
      digitalWrite(ledPin, ledState ? HIGH : LOW);
    }
  }

  // small CPU relief (not necessary, but okay)
  delay(1);
}
