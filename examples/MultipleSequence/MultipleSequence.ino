/*
  Name:    MultipleSequence.ino
  Created:  03/23/2020 12:45:23 AM
  Author: José Gabriel Companioni Benítez (https://github.com/elC0mpa)
  Description: Example to demostrate how to work with multiple sequences 
*/

#include <Arduino.h>
#include <EasyButton.h>

#define BUTTON_PIN 16
#define BAUDRATE 19200

void sequenceEllapsed()
{
  Serial.println("Double click");
}

void otherSequence()
{
  Serial.println("Other sequence");
}

EasyButton button(BUTTON_PIN);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(BAUDRATE);
  button.begin();
  button.onSequence(2, 1500, sequenceEllapsed);
  button.onSequence(3, 2500, otherSequence);
  Serial.println("Multiple onSequence example");
}

void loop() {
  // put your main code here, to run repeatedly:
  button.read();
}
