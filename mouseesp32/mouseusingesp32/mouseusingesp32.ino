#include <BleMouse.h>

BleMouse bleMouse("ESP32 Mouse", "ESP32", 100);

const int xPin = 34;
const int yPin = 35;
const int buttonPin = 27;

unsigned long lastClickTime = 0;
bool buttonPressed = false;
bool waitingForSecondClick = false;
bool scrolling = false;
int scrollThreshold = 700;

void setup() {
  Serial.begin(115200);
  pinMode(buttonPin, INPUT_PULLUP);
  bleMouse.begin();
}

void loop() {
  if (!bleMouse.isConnected()) return;

  int xVal = analogRead(xPin);
  int yVal = analogRead(yPin);
  bool buttonState = digitalRead(buttonPin) == LOW;

  static unsigned long pressStart = 0;
  static bool wasHeld = false;

  // Button press detection
  if (buttonState && !buttonPressed) {
    buttonPressed = true;
    pressStart = millis();
    wasHeld = false;
  }

  // Button release logic
  if (!buttonState && buttonPressed) {
    buttonPressed = false;
    unsigned long pressDuration = millis() - pressStart;

    if (pressDuration < 500 && !wasHeld) {
      if (waitingForSecondClick && millis() - lastClickTime < 400) {
        Serial.println("Right Click");
        bleMouse.click(MOUSE_RIGHT);
        waitingForSecondClick = false;
      } else {
        lastClickTime = millis();
        waitingForSecondClick = true;
      }
    }
  }

  // Execute left click if second click didn't happen in time
  if (waitingForSecondClick && millis() - lastClickTime > 400) {
    Serial.println("Left Click");
    bleMouse.click(MOUSE_LEFT);
    waitingForSecondClick = false;
  }

  // Scroll when button is held and joystick moved
  if (buttonState && millis() - pressStart > 600) {
    wasHeld = true;

    int scrollY = map(yVal, 0, 4095, 5, -5);  // Invert for natural scroll
    int scrollX = map(xVal, 0, 4095, -5, 5);    // Optional: horizontal scroll

    if (abs(scrollY) > 2) {
      Serial.print("Vertical Scroll: ");
      Serial.println(scrollY);
      bleMouse.move(0, 0, scrollY);  // 🟢 correct usage
    }

    delay(100);  // Smooth scroll
    return;
  }

  // Normal mouse movement
  int moveX = map(xVal, 0, 4095, -9, 9);
  int moveY = map(yVal, 0, 4095, -9, 9);
  if (abs(moveX) > 1 || abs(moveY) > 1) {
    bleMouse.move(moveX, moveY);
  }

  delay(8);
}
