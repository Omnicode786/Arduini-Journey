// Define the pin where the LED is connected
const int ledPin = 2; // Built-in LED on most ESP32 boards

void setup() {
  // Set the LED pin as an output
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // Turn the LED on
  digitalWrite(ledPin, HIGH);
  delay(400); // Wait for 1 second (1000 ms)

  // Turn the LED off
  digitalWrite(ledPin, LOW);
  delay(400); // Wait for 1 second
}
