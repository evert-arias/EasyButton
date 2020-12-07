/*
  Name:    Interrupts.ino
  Created:  8/11/2019 11:45:52 AM
  Author: José Gabriel Companioni Benítez (https://github.com/elC0mpa)
  Description: Example to demostrate how to use interrupts in order to improve performance
*/

#include <Arduino.h>
#include <EasyButton.h>

// Arduino pin where the buttons are connected to.
#define BUTTON_PIN 2

#define BAUDRATE 115200

// Instance of the button.
EasyButton button(BUTTON_PIN);

void buttonPressed()
{
  Serial.println("Button pressed");
}

void sequenceEllapsed()
{
  Serial.println("Double click");
}

void buttonISR()
{
  button.read();
}

void setup()
{

  // Initialize Serial for debuging purposes.
  Serial.begin(BAUDRATE);

  Serial.println();
  Serial.println(">>> EasyButton interrupts example <<<");

  // Initialize the button.
  button.begin();

  button.onPressed(buttonPressed);

  button.onSequence(2, 1500, sequenceEllapsed);

  if (button.supportsInterrupt())
  {
    button.enableInterrupt(buttonISR);
    Serial.println("Button will be used through interrupts");
  }
}

void loop()
{
  // put your main code here, to run repeatedly:
}
