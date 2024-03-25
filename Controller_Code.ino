#include <Joystick.h>

Joystick_ Joystick;

const int buttonPins[] = {4, 5, 6, 7, 8, 9}; // Pins for buttons A to F
int horzPin = A2;  // Analog output of horizontal joystick pin
int vertPin = A3;  // Analog output of vertical joystick pin
int selPin = 3;  // Select button pin of joystick

void setup() {
  for (int i = 0; i < 6; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
  }

  pinMode(horzPin, INPUT);  // Set both analog pins as inputs
  pinMode(vertPin, INPUT);
  pinMode(selPin, INPUT_PULLUP);  // Set button select pin as input

  Joystick.begin();
}

void loop() {
  for (int i = 0; i < 6; i++) {
    int buttonState = digitalRead(buttonPins[i]) == LOW ? 1 : 0;
    Joystick.setButton(i, buttonState);
  }

  int horzValue = analogRead(horzPin);
  int vertValue = analogRead(vertPin);

  // Map joystick values to the range 0-255 for better sensitivity
  int horzMapped = map(horzValue, 0, 1023, 0, 1023);
  int vertMapped = map(vertValue, 0, 1023, 0, 1023);

  // Set joystick position with some deadzone to prevent small fluctuations
  if (abs(horzMapped - 128) > 10) {
    Joystick.setXAxis(horzMapped);
  } else {
    Joystick.setXAxis(128); // Centered position
  }

  if (abs(vertMapped - 128) > 10) {
    Joystick.setYAxis(vertMapped);
  } else {
    Joystick.setYAxis(128); // Centered position
  }

  // Check the select button
  int selectButtonState = digitalRead(selPin) == LOW ? 1 : 0;
  Joystick.setButton(6, selectButtonState);

  delay(20); // Add a small delay to prevent sending data too quickly
}
