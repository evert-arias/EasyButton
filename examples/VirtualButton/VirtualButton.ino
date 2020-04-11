/*
  Name:    EasyButtonVirtual.ino
  Created:  4/11/2020 1:22:52 AM
  Author: José Gabriel Companioni Benítez (https://github.com/elC0mpa)
  Description: Example to demostrate how to use the virtual button feature. This allows the user to use a variable as if it were a button. Really useful when 
  the buttons are connected through port expanders like PCF8574.
*/

#include <Arduino.h>
#include <EasyButtonVirtual.h>

/* 
  The following is just to simulate changes in the button state,
  it is not useful when using the library in a real case. 
 */
unsigned long previous_millis = 0;
unsigned int interval = 1000;

#define BAUDRATE 115200

// Global variable that simulates the button's value.
bool button = true;

// Instance of the button.
EasyButtonVirtual vButton(button);

// Callback function to be called when the button is pressed.
void buttonPressed()
{
  Serial.println("Button pressed");
  interval = 2500;
}

// Callback function to be called when the button is pressed.
void buttonPressedForTwoSeconds()
{
  Serial.println("Button pressed for two seconds");
}

void setup()
{
  // Initialize Serial for debuging purposes.
  Serial.begin(BAUDRATE);

  Serial.println();
  Serial.println(">>> EasyButton virtual button example <<<");

  // Initialize the button.
  vButton.begin();

  // Callback function to be called when the button is pressed.
  vButton.onPressed(buttonPressed);

  // Add the callback function to be called when the button is pressed for at least the given time.
  vButton.onPressedFor(2000, buttonPressedForTwoSeconds);
}

void loop()
{
  // Continuously read the status of the button.
  vButton.read();

  /* 
    The following is just to simulate changes in the button state,
    it is not useful when using the library in a real case. 
  */
  unsigned long current_millis = millis();
  if (current_millis - previous_millis >= interval)
  {
    previous_millis = current_millis;
    button = !button;
  }
}
