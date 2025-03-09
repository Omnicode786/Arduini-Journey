#define LEDPin 9

#define potPin A0


void setup(){
  pinMode(LEDPin, OUTPUT);
}

void loop(){
  int reading = map(analogRead(potPin),0,1023,0,255);
  analogWrite(LEDPin, reading);
  delay(5);
}