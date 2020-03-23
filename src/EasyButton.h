/**
 * EasyButton.h
 * @author Evert Arias
 * @version 1.1.0
 * @license MIT
 */

#ifndef _EasyButton_h
#define _EasyButton_h

#include <Arduino.h>
#include "Sequence.h"

#ifdef ESP8266
#define EASYBUTTON_FUNCTIONAL_SUPPORT 1
#endif

#ifdef EASYBUTTON_FUNCTIONAL_SUPPORT
#include <functional>
#include "FunctionalInterrupt.h"
#endif

#define INTERRUPT 0
#define POLL 1

#define MAX_SEQUENCES 5

class EasyButton
{
	friend class EasyButtonTouch;
public:
#ifdef EASYBUTTON_FUNCTIONAL_SUPPORT
	typedef std::function<void()> callback_t;
#else
	typedef void(*callback_t)();
#endif
	EasyButton(uint8_t pin, uint32_t debounce_time = 35, bool pullup_enable = true, bool invert = true) : _pin(pin), _db_time(debounce_time), _invert(invert), _pu_enabled(pullup_enable) {}
	~EasyButton() {}
	// PUBLIC FUNCTIONS
	virtual void begin();														// Initialize a button object and the pin it's connected to.
	bool read(int read_type = POLL);											// Returns the current debounced button state, true for pressed, false for released.
	void update();																// Update button pressed time, only needed when using interrupts
	void onPressed(callback_t callback);										// Call a callback function when the button has been pressed and released.
	void onPressedFor(uint32_t duration, callback_t callback);					// Call a callback function when the button has been held for at least the given number of milliseconds.
	void onSequence(uint8_t sequences, uint32_t duration, callback_t callback);	// Call a callback function when the given sequence has matched. 
	void enableInterrupt(callback_t callback);									// Call a callback function when the button is pressed or released
	void disableInterrupt();
	bool supportsInterrupt();		// Returns true if the button pin is an external interrupt pin
	bool isPressed();				// Returns true if the button state was pressed at the last read.
	bool isReleased();				// Returns true if the button state was released at the last read.	
	bool wasPressed();				// Returns true if the button state at the last read was pressed.
	bool wasReleased();				// Returns true if the button state at the last read was released.
	bool pressedFor(uint32_t duration);		// Returns true if the button state at the last read was pressed, and has been in that state for at least the given number of milliseconds.
	bool releasedFor(uint32_t duration);	// Returns true if the button state at the last read was released, and has been in that state for at least the given number of milliseconds.
private:
	// PRIVATE VARIABLES
	Sequence _sequences[MAX_SEQUENCES];
	uint16_t _sequences_count;
	callback_t _pressed_sequence_callbacks[MAX_SEQUENCES];

	uint32_t _held_threshold;			// Held threshold.
	bool _was_btn_held;			        // Indicate if button was held.
	bool _held_callback_called;			// Indicate if button long press has been notified.
	uint8_t _pin;						// Arduino pin number where the Button is connected to.
	uint32_t _db_time;					// Debounce time (ms).
	bool _invert;						// Inverts button logic. If true, low = pressed else high = pressed.
	bool _pu_enabled;					// Internal pullup resistor enabled.
	bool _current_state;				// Current button state, true = pressed.      
	bool _last_state;					// Previous button state, true = pressed.
	bool _changed;						// Has the state change since last read.
	uint32_t _time;						// Time of current state.
	uint32_t _last_change;				// Time of last state change.
	// CALLBACKS
	callback_t _pressed_callback;				// Callback function for pressed events.
	callback_t _pressed_for_callback;			// Callback function for pressedFor events.

	virtual bool _readPin();			// Abstracts the pin value reading.
	void _checkPressedTime();			// Verify if pressed_for_callback should be called
};

#endif