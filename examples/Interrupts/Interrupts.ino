/*
  Name:    MultipleButtons.ino
  Created:  8/11/2019 11:45:52 AM
  Author: José Gabriel Companioni Benítez (elC0mpa)
  Description: Example to demostrate how to use the library with more than one button
*/

#include <Arduino.h>
#include <EasyButton.h>

#define BUTTON_PIN 2
#define BAUDRATE 9600

EasyButton button(BUTTON_PIN);


void buttonPressed()
{
  Serial.println("Button is pressed");
}

void buttonPressedTwoSeconds()
{
  Serial.println("Button pressed for two seconds");
}

void buttonSequence()
{
  Serial.println("Sequence");
}

void buttonPressedReleased()
{
  button.read();
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(BAUDRATE);
  button.begin();
  if (button.supportsInterrupt())
  {
    Serial.println("Button will be used through external interrupts");
    button.enableInterrupt(buttonPressedReleased);
  }
  
  button.onPressed(buttonPressed);
  button.onPressedFor(2000, buttonPressedTwoSeconds);
  button.onSequence(3, 5000, buttonSequence);
}

void loop() {
  // put your main code here, to run repeatedly:
}
