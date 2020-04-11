/*
  Name:		Sequence.ino
  Created:	9/5/2018 10:49:52 AM
  Author:	Evert Arias
  Description: Example to demostrate how to use the library to detect a sequence of presses on a button.
*/

#include <EasyButton.h>

// Arduino pin where the button is connected to.
#define BUTTON_PIN 2

#define BAUDRATE 115200

// Instance of the button.
EasyButton button(BUTTON_PIN);

// Callback function to be called when the button is pressed.
void onSequenceMatched()
{
  Serial.println("Button pressed");
}

void setup()
{
  // Initialize Serial for debuging purposes.
  Serial.begin(BAUDRATE);

  Serial.println();
  Serial.println(">>> EasyButton sequence example <<<");

  // Initialize the button.
  button.begin();
  // Add the callback function to be called when the given sequence of presses is matched.
  button.onSequence(5 /* number of presses */, 2000 /* timeout */, onSequenceMatched /* callback */);
}

void loop()
{
  // Continuously read the status of the button.
  button.read();
}
