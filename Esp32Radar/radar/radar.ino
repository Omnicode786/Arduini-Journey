#include <ESP32Servo.h>

#define TRIG_PIN 18
#define ECHO_PIN 19
Servo radarServo;

void setup() {
  Serial.begin(115200);
  radarServo.attach(2); // Change to your servo pin
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

void loop() {
  for (int angle = 0; angle <= 180; angle++) {
    radarServo.write(angle);
    delay(20); // Let servo reach position

    long duration, distance;

    // Trigger the sensor
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    // Read echo
    duration = pulseIn(ECHO_PIN, HIGH, 30000); // Timeout after 30ms
    distance = duration * 0.034 / 2;

    if (distance >= 10 && distance <= 100) {
      Serial.print(angle);
      Serial.print(",");
      Serial.println(distance);
    } else {
      // Still send angle so UI updates, but with 0 distance
      Serial.print(angle);
      Serial.println(",0");
    }
  }
}
