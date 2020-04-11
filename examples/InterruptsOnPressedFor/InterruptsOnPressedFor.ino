/*
  Name:    InterruptsOnPressedFor.ino
  Created:  8/17/2019 10:16:52 AM
  Author: José Gabriel Companioni Benítez (https://github.com/elC0mpa)
  Description: Example to demostrate how to use onPressedFor functionality when using interrupts
*/

#include <Arduino.h>
#include <EasyButton.h>

/* 
  Arduino pin where the buttons are connected to.
  Should be a pin that supports external interrupts. 
 */
#define BUTTON_PIN 2

#define BAUDRATE 115200

// Instance of the button.
EasyButton button(BUTTON_PIN);

void buttonPressedTwoSeconds()
{
  Serial.println("Button pressed for two seconds");
}

void buttonISR()
{
  // When button is being used through external interrupts, parameter INTERRUPT must be passed to read() function.
  button.read();
}

void setup()
{
  // Initialize Serial for debuging purposes.
  Serial.begin(BAUDRATE);

  Serial.println();
  Serial.println(">>> EasyButton onPressedFor interrupt example <<<");

  // Initialize the button.
  button.begin();

  button.onPressedFor(2000, buttonPressedTwoSeconds);

  if (button.supportsInterrupt())
  {
    button.enableInterrupt(buttonISR);
    Serial.println("Button will be used through interrupts");
  }
}

void loop()
{
  /*
    update() function must be called repeatedly only if onPressedFor 
    functionality is being used and interrupt is enabled.
  */
  button.update();
}
