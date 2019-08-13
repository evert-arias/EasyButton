/*
  Name:    MultipleButtons.ino
  Created:  8/11/2019 11:45:52 AM
  Author: José Gabriel Companioni Benítez (https://github.com/elC0mpa)
  Description: Example to demostrate how to use interrupts with the library in order to improve performance 
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
  button.onSequence(3, 5000, buttonSequence);
}

void loop() {
  // put your main code here, to run repeatedly:
}
