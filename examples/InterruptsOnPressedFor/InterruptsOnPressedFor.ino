/*
  Name:    InterruptsOnPressedFor.ino
  Created:  8/17/2019 10:16:52 AM
  Author: José Gabriel Companioni Benítez (https://github.com/elC0mpa)
  Description: Example to demostrate how to use onPressedFor functionality when using interrupts 
*/

#include <Arduino.h>
#include <EasyButton.h>

#define BUTTON_PIN 2  //Should be a pin that supports external interrupts
#define BAUDRATE 9600

EasyButton button(BUTTON_PIN);

void buttonPressedTwoSeconds()
{
  Serial.println("Button Pressed for two seconds");
}

void buttonISR()
{
  //When button is being used through external interrupts, parameter INTERRUPT must be passed to read() function
  button.read(INTERRUPT); 
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(BAUDRATE);
  button.begin();
  button.onPressedFor(2000, buttonPressedTwoSeconds);
  if (button.supportsInterrupt())
  {
    button.enableInterrupt(buttonISR);
    Serial.println("EasyButton onPressedFor Interrupt example");
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  // update() function must be called repeatedly only if onPressedFor functionality is being used and interrupt is enabled
  button.update();
}
