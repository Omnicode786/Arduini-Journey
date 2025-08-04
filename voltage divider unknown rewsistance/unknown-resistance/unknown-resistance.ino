#include <LiquidCrystal.h>

// New working LCD pin mapping: RS, E, D4, D5, D6, D7
LiquidCrystal lcd(23, 22, 21, 19, 18, 5);

#define ANALOG_PIN 36      // GPIO36 (ADC1_0)
const float Vin = 3.3;     // Input voltage to voltage divider (ESP32 max ADC voltage)
const float R1 = 10000.0;  // Known resistor (10k ohm)

void setup() {
  delay(1000);  // Allow LCD to stabilize
  Serial.begin(115200);
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("ESP32 Ohmmeter");
  delay(2000);
}

void loop() {
  int adcVal = analogRead(ANALOG_PIN);  // Read ADC value from A0/GPIO36
  float Vout = (adcVal / 4095.0) * Vin;

  float R2 = 0;
  if (Vout > 0 && Vout < Vin) {
    R2 = (R1 * Vout) / (Vin - Vout);  // Voltage divider formula
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Resistance:");

  lcd.setCursor(0, 1);
  if (R2 >= 1000.0) {
    lcd.print(R2 / 1000.0, 2);
    lcd.print(" kOhm");
  } else {
    lcd.print(R2, 1);
    lcd.print(" Ohm");
  }

  Serial.print("ADC: "); Serial.print(adcVal);
  Serial.print("  Vout: "); Serial.print(Vout, 3);
  Serial.print("  R2: "); Serial.println(R2, 2);

  delay(1000);
}
