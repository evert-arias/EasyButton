/*
  Name:    EasyButtonVirtual.ino
  Created:  4/11/2020 1:22:52 AM
  Author: José Gabriel Companioni Benítez (https://github.com/elC0mpa)
  Description: Example to demostrate how to use the virtual button feature. This allows the user to use a variable as if it were a button. Really useful when 
  the buttons are connected through port expanders like PCF8574.
*/

#include <Arduino.h>
#include <EasyButtonVirtual.h>

// Global variable that simulates the button's value.
bool button = true;

EasyButtonVirtual button_abstraction(button);

unsigned long previous_millis = 0;
unsigned int interval = 1000; // interval at which to blink (milliseconds)

void buttonPressed()
{
  Serial.println("Button Pressed");
  interval = 2500;
}

void buttonPressedForTwoSeconds()
{
  Serial.println("Button pressed for two seconds");
}

void setup()
{
  // put your setup code here, to run once:
  button_abstraction.begin();
  button_abstraction.onPressed(buttonPressed);
  button_abstraction.onPressedFor(2000, buttonPressedForTwoSeconds);
}

void loop()
{
  // put your main code here, to run repeatedly:
  button_abstraction.read();

  unsigned long current_millis = millis();
  if (current_millis - previous_millis >= interval)
  {
    // save the last time you blinked the LED
    previous_millis = current_millis;
    button = !button;
  }
}
