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
  setRGBLEDColor(RLightColor, GLightColor, BLightColor);
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
      Serial.println("short click");
    }
    else{
      Serial.println("long press");
    }
    buttonPressed = false;
  }
}

void changeLEDColor(){
   lightNum = lightNum + 1;
  if(lightNum >= 5)
    lightNum = 0;

  if(lightNum ==0){

    RLightColor = 0;
    GLightColor = 0;
    BLightColor = 0;
  }

  if(lightNum ==1){

    RLightColor = 0;
    GLightColor = 255;
    BLightColor = 255;
  }
  if(lightNum ==2){

    RLightColor = 255;
    GLightColor = 0;
    BLightColor = 255;
  }
  if(lightNum ==3){

    RLightColor = 255;
    GLightColor = 255;
    BLightColor = 0;
  }
  if(lightNum ==4){

    RLightColor = 0;
    GLightColor = 0;
    BLightColor = 255;
  }
}
