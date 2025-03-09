#define LEDPin 7

#define ButtonPin 8
#define LEDPin1 12


  bool push = false;

void setup() {
  // put your setup code here, to run once:
  pinMode(ButtonPin, INPUT);
  pinMode(LEDPin, OUTPUT);



}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(ButtonPin)== HIGH){
    if (!push){
    digitalWrite(LEDPin, HIGH);
    digitalWrite(LEDPin1, LOW);

    push = true;
    delay(200);
    }

     else{
    digitalWrite(LEDPin, LOW);
    digitalWrite(LEDPin1, HIGH);


    
    push = false;
    delay(200);

  }
   while (digitalRead(ButtonPin) == HIGH);
  }
 


}
