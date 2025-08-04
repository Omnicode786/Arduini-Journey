#include <ESP32Servo.h>

const int trigPin = 5;
const int echoPin = 18;
Servo myservo;

void setup() {
  Serial.begin(115200);
  myservo.attach(19); // Change to your servo pin
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  for (int angle = 0; angle <= 180; angle++) {
    myservo.write(angle);
    delay(10);

    long duration, distance;
    digitalWrite(trigPin, LOW); delayMicroseconds(2);
    digitalWrite(trigPin, HIGH); delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    duration = pulseIn(echoPin, HIGH, 30000); // 30ms timeout (~5 meters)
    distance = duration * 0.034 / 2;

    if (distance > 0 && distance < 200) {
      Serial.print(angle);
      Serial.print(",");
      Serial.println(distance);
    }
  }
}
