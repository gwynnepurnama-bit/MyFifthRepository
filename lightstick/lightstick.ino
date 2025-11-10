const int buttonPin = 2, rledPin = 9, bledPin = 10, gledPin = 11;
int buttonState = 0, currentMode = 0;
bool buttonPressed = false, blinkON = true;
unsigned long pressingTime = 0, blinkTimer = 0;
const int longPressInterval = 2000, blinkInterval = 500;
int rlightColor = 0, blightColor = 0, glightColor = 0, lightNum = 0;
int rcurrentColor = 0, bcurrentColor = 0, gcurrentColor = 0;
const int fadeAmount = 2;
int fadeDirection = 1;
int fadeValue = 0;  // used for breathing effect
unsigned long fadeTimer = 0;
const int fadeSpeed = 15; // smaller = slower breathing

void setup() {
  pinMode(rledPin, OUTPUT);
  pinMode(bledPin, OUTPUT);
  pinMode(gledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  checkButton();
  updateLEDColor();
  setRGBLedColor(rcurrentColor, bcurrentColor, gcurrentColor);
}

void checkButton() {
  buttonState = digitalRead(buttonPin);
  if (buttonState == LOW && !buttonPressed) {
    pressingTime = millis();
    buttonPressed = true;
  }
  if (buttonState == HIGH && buttonPressed) {
    unsigned long currentTime = millis();
    if (currentTime - pressingTime < longPressInterval) {
      changeLedColor();
      Serial.println("Short Press → Change Color");
    } else {
      changeMode();
      Serial.print("Long Press → Change Mode: ");
      Serial.println(currentMode);
    }
    buttonPressed = false;
  }
}

void changeMode() {
  currentMode = (currentMode + 1) % 3; // cycles 0 → 1 → 2 → 0

  if (currentMode == 1) {
    blinkTimer = 0;
    blinkON = true;
    Serial.println("Mode: Blink");
  } 
  else if (currentMode == 2) {
    fadeDirection = 1;
    fadeValue = 0;
    fadeTimer = millis();
    Serial.println("Mode: Breathing");
  } 
  else {
    Serial.println("Mode: Constant Light");
  }
}

void changeLedColor() {
  // Increase the light number
  lightNum = (lightNum + 1) % 5;

  // Set the RGB Light Color accordingly
  if (lightNum == 0) {
    // white
    rlightColor = 0;
    blightColor = 0;
    glightColor = 0;
  } else if (lightNum == 1) {
    // red
    rlightColor = 0;
    blightColor = 255;
    glightColor = 255;
  } else if (lightNum == 2) {
    // green
    rlightColor = 255;
    blightColor = 0;
    glightColor = 255;
  } else if (lightNum == 3) {
    // blue
    rlightColor = 255;
    blightColor = 255;
    glightColor = 0;
  } else if (lightNum == 4) {
    // yellow
    rlightColor = 0;
    blightColor = 0;
    glightColor = 255;
  }
}

void updateLEDColor() {
  if (currentMode == 0) {
    // Constant Light Mode
    rcurrentColor = rlightColor;
    bcurrentColor = blightColor; 
    gcurrentColor = glightColor;
  }

  else if (currentMode == 1) {
    // Blink Mode
    unsigned long currentTime = millis();
    if (currentTime - blinkTimer > blinkInterval) {
      blinkON = !blinkON;
      blinkTimer = currentTime;
    }

    if (blinkON) {
      rcurrentColor = rlightColor;
      bcurrentColor = blightColor; 
      gcurrentColor = glightColor;
    } else {
      rcurrentColor = 255;
      bcurrentColor = 255; 
      gcurrentColor = 255;
    }
  }

  else if (currentMode == 2) {
    // Breathing Light Mode
    unsigned long currentTime = millis();
    if (currentTime - fadeTimer > fadeSpeed) {
      fadeTimer = currentTime;
      fadeValue += fadeAmount * fadeDirection;

      if (fadeValue <= 0 || fadeValue >= 255) {
        fadeDirection = -fadeDirection; // reverse direction at limits
      }
    }

    rcurrentColor = map(fadeValue, 0, 255, 255, rlightColor);
    bcurrentColor = map(fadeValue, 0, 255, 255, blightColor);
    gcurrentColor = map(fadeValue, 0, 255, 255, glightColor);
  }
}

void setRGBLedColor(int r, int b, int g) {
  analogWrite(rledPin, r);
  analogWrite(bledPin, b);
  analogWrite(gledPin, g);
} 