#include <Wire.h>
#include "SSD1306Wire.h"  // Include OLED display library
#include "pins_arduino.h"

SSD1306Wire display(0x3c, SDA_OLED, SCL_OLED);  // Initialize OLED display
String receivedText = "";  // Variable to store input from Serial Monitor

void setup() {
  Serial.begin(115200);
  while (!Serial) { delay(100); }

  Serial.println("Enter text to display on OLED:");

  // Turn on OLED power and reset the display
  pinMode(Vext, OUTPUT);
  digitalWrite(Vext, LOW);  // Power ON
  pinMode(RST_OLED, OUTPUT);
  digitalWrite(RST_OLED, HIGH);
  delay(1);
  digitalWrite(RST_OLED, LOW);
  delay(1);
  digitalWrite(RST_OLED, HIGH);
  delay(1);

  // Initialize OLED display
  display.init();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_16);  // Set font size
}

void loop() {
  // Check if new data is available in Serial Monitor
  while (Serial.available()) {
    char c = Serial.read();  // Read each character
    if (c == '\n') {  // If Enter key is pressed, update the display
      display.clear();
      display.setTextAlignment(TEXT_ALIGN_CENTER);
      display.drawString(64, 25, receivedText);  // Display text at center
      display.display();
      Serial.println("Displaying: " + receivedText);
      receivedText = "";  // Clear input buffer
    } else {
      receivedText += c;  // Append characters to string
    }
  }
}
