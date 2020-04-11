/*
  Name:		MultipleButtons.ino
  Created:	3/25/2019 11:45:52 AM
  Author:	Evert Arias
  Description: Example to demostrate how to use the library with more than one button
*/

#include <EasyButton.h>

// Arduino pin where the buttons are connected to
#define BUTTON_ONE_PIN 2
#define BUTTON_TWO_PIN 4

#define BAUDRATE 115200

// Button1
EasyButton button1(BUTTON_ONE_PIN);
// Button2
EasyButton button2(BUTTON_TWO_PIN);

// Callback function to be called when button1 is pressed
void onButton1Pressed()
{
  Serial.println("Button1 pressed");
}

// Callback function to be called when button2 is pressed
void onButton2Pressed()
{
  Serial.println("Button2 pressed");
}

void setup()
{
  // Initialize Serial for debuging purposes
  Serial.begin(BAUDRATE);

  Serial.println();
  Serial.println(">>> EasyButton multiple buttons example <<<");

  // Initialize the button1
  button1.begin();
  // Initialize the button2
  button2.begin();
  // Add the callback function to be called when the button1 is pressed.
  button1.onPressed(onButton1Pressed);
  // Add the callback function to be called when the button2 is pressed.
  button2.onPressed(onButton2Pressed);
}

void loop()
{
  // Continuously read the status of the buttons
  button1.read();
  button2.read();
}
