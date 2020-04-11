/**
 * EasyButton.h
 * @author Evert Arias
 * @version 2.0.0
 * @license MIT
 */

#ifndef _EasyButton_h
#define _EasyButton_h

#include <Arduino.h>
#include "EasyButtonBase.h"

#define EASYBUTTON_READ_TYPE_INTERRUPT 0
#define EASYBUTTON_READ_TYPE_POLL 1

class EasyButton : public EasyButtonBase
{
	friend class EasyButtonTouch;

public:
	EasyButton(uint8_t pin, uint32_t debounce_time = 35, bool pullup_enable = true, bool active_low = true) : EasyButtonBase(active_low), _pin(pin), _db_time(debounce_time), _pu_enabled(pullup_enable), _read_type(EASYBUTTON_READ_TYPE_POLL)
	{
	}
	~EasyButton() {}

	// PUBLIC FUNCTIONS
	virtual void begin();					   // Initialize a button object and the pin it's connected to.
	bool read();							   // Returns the current debounced button state, true for pressed, false for released.
	void update();							   // Update button pressed time, only needed when using interrupts.
	void enableInterrupt(callback_t callback); // Call a callback function when the button is pressed or released.
	void disableInterrupt();
	bool supportsInterrupt(); // Returns true if the button pin is an external interrupt pin.

private:
	// PRIVATE VARIABLES
	uint8_t _pin;		// Arduino pin number where the Button is connected to.
	uint32_t _db_time;	// Debounce time (ms).
	bool _pu_enabled;	// Internal pullup resistor enabled.
	uint8_t _read_type; // Read type. Poll or Interrupt.

	virtual bool _readPin(); // Abstracts the pin value reading.
};

#endif