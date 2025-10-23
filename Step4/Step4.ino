const int buttonPin = 2;

const int RledPin = 9;
const int GledPin = 10;
const int BledPin = 11;

int buttonState = 0;
bool buttonPressed = false;
unsigned long pressingTime = 0;
const int longPressInterval = 2000;

int lightNum= 0;

int RLightColor = 0;
int GLightColor = 0;
int BLightColor = 0;
int RCurrentColor =0;
int GCurrentColor = 0;
int BCurrentColor = 0;

int currentMode = 0;
unsigned long blinkTimer = 0;
const int blinkInterval = 500;
bool blinkOn= true;

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(RledPin, OUTPUT);
  pinMode(GledPin, OUTPUT);
  pinMode(BledPin, OUTPUT);
  Serial.begin(9600);
}

void setRGBLEDColor(int r, int g, int b) {
  analogWrite(RledPin, r);
  analogWrite(GledPin, g);
  analogWrite(BledPin, b);
}

void loop() 
{
  checkButton();
  updateLEDColor();
  //setRGBLEDColor(RLightColor, GLightColor, BLightColor);
  setRGBLEDColor(RCurrentColor, GCurrentColor, BCurrentColor);
}

void changeLEDColor() {
  lightNum = (lightNum + 1) % 5;

  switch (lightNum) {
    case 0:
      RLightColor = 255; GLightColor = 0; BLightColor = 0; // Red
      break;
    case 1:
      RLightColor = 0; GLightColor = 255; BLightColor = 0; // Green
      break;
    case 2:
      RLightColor = 0; GLightColor = 0; BLightColor = 255; // Blue
      break;
    case 3:
      RLightColor = 255; GLightColor = 255; BLightColor = 0; // Yellow
      break;
    case 4:
      RLightColor = 255; GLightColor = 0; BLightColor = 255; // Magenta
      break;
  }
}

void checkButton(){
  // put your main code here, to run repeatedly:
  buttonState = digitalRead(buttonPin);
   
  if(buttonState == HIGH && !buttonPressed){
    pressingTime = millis();
    buttonPressed = true;
  }
  if(buttonState == LOW && buttonPressed){
    unsigned long currentTime = millis();
    if(currentTime - pressingTime < longPressInterval){
      changeLEDColor();
      //Serial.println("short click");
    }
    else{
      changeMode();
      //Serial.println("long press");
    }
    buttonPressed = false;
  }
}

void changeMode(){
  currentMode = currentMode + 1;
  if(currentMode>= 3){
    currentMode = 0;
  }
  if(currentMode == 1){
    blinkTimer = 0;
    blinkOn = true;
  }
}

void updateLEDColor(){
  //  lightNum = lightNum + 1;
  // if(lightNum >= 5)
    // lightNum = 0;

  if(currentMode ==0){

    RCurrentColor = 0;
    GCurrentColor = 0;
    BCurrentColor = 0;
   }
   
    else if(currentMode ==1){

      unsigned long currentTime = millis();
      if(currentTime- blinkTimer > blinkInterval){
      blinkOn = !blinkOn;
      blinkTimer = currentTime;
      }
    
     if(blinkOn){

     RCurrentColor = RLightColor;
     GCurrentColor = GLightColor;
     BCurrentColor = BLightColor;
    }
     else{

     RCurrentColor = 255;
     GCurrentColor = 255;
     BCurrentColor = 255;
    }
  }
  else if (currentMode == 2){

    // RCurrentColor = RLightColor;
    // GCurrentColor = GLightColor;
    // BCurrentColor = BLightColor;
    // RLightColor = 0;
    // GLightColor = 0;
    // BLightColor = 255;
  }
}
