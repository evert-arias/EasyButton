/*
  Name:    Interrupts.ino
  Created:  8/11/2019 11:45:52 AM
  Author: José Gabriel Companioni Benítez (https://github.com/elC0mpa)
  Description: Example to demostrate how to use interrupts in order to improve performance 
*/

#include <Arduino.h>
#include <EasyButton.h>

#define BUTTON_PIN 2
#define BAUDRATE 9600

EasyButton button(BUTTON_PIN);

void buttonPressed()
{
  Serial.println("Button Pressed");
}

void sequenceEllapsed()
{
  Serial.println("Double click");
}

void buttonISR()
{
  //When button is being used through external interrupts, parameter INTERRUPT must be passed to read() function
  button.read(INTERRUPT);
}

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(BAUDRATE);
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
