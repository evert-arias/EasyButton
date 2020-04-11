/*
  Name:    MultipleSequence.ino
  Created:  03/23/2020 12:45:23 AM
  Author: José Gabriel Companioni Benítez (https://github.com/elC0mpa)
  Description: Example to demostrate how to work with multiple sequences 
*/

#include <Arduino.h>
#include <EasyButton.h>

// Arduino pin where the button is connected to.
#define BUTTON_PIN 2

#define BAUDRATE 115200

void sequenceEllapsed()
{
  Serial.println("Double click");
}

void otherSequence()
{
  Serial.println("Other sequence");
}

// Instance of the button.
EasyButton button(BUTTON_PIN);

void setup()
{
  // Initialize Serial for debuging purposes.
  Serial.begin(BAUDRATE);

  Serial.println();
  Serial.println(">>> EasyButton multiple onSequence example <<<");

  // Initialize the button.
  button.begin();

  button.onSequence(2, 1500, sequenceEllapsed);

  button.onSequence(3, 2500, otherSequence);
}

void loop()
{
  // Continuously read the status of the button.
  button.read();
}
