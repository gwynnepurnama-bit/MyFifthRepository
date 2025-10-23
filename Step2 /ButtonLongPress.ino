
const int buttonPin = 2;

const int RledPin = 9;
const int GledPin = 10;
const int BledPin = 11;

int buttonState = 0;
bool buttonPressed = false;
unsigned long pressingTime = 0;
const int longPressInterval = 2000;

void setup() 
{
  // put your setup code here, to run once:
  pinMode(buttonPin, INPUT);
  pinMode(RledPin, OUTPUT);
  pinMode(GledPin, OUTPUT);
  pinMode(BledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() 
{
  // put your main code here, to run repeatedly:
  buttonState = digitalRead(buttonPin);

   
  if(buttonState == HIGH && !buttonPressed){
    pressingTime = millis();
    buttonPressed = true;
    Serial.println("short click");
  }
  if(buttonState == LOW && !buttonPressed){
   unsigned long currentTime = millis();
      if(currentTime - pressingTime < longPressInterval){


    }
    else{
      Serial.println("long press");
     }
    buttonPressed = false;
  }
}
