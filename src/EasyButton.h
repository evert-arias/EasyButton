/**
 * EasyButton.h
 * @author Evert Arias
 * @version 1.0.0
 * @license MIT
 */

#ifndef _EasyButton_h
#define _EasyButton_h

#include <Arduino.h>

class EasyButton
{
public:
	EasyButton(uint8_t pin, uint32_t dbTime = 35, bool puEnable = true, bool invert = true) : _pin(pin), _db_time(dbTime), _pu_enabled(puEnable), _invert(invert) {}
	~EasyButton() {};
	// PUBLIC FUNCTIONS
	void begin();																// Initialize a button object and the pin it's connected to.	
	bool read();																// Returns the current debounced button state, true for pressed, false for released.
	void onPressed(void(*callback)());											// Call a callback function when the button has been pressed and released.
	void onPressedFor(uint32_t duration, void(*callback)());					// Call a callback function when the button has been held for at least the given number of milliseconds.
	void onSequence(uint8_t sequences, uint32_t duration, void(*callback)());   // Call a callback function when the given sequence has matched. 
	bool isPressed();				// Returns true if the button state was pressed at the last read.
	bool isReleased();				// Returns true if the button state was released at the last read.	
	bool wasPressed();				// Returns true if the button state at the last read was pressed.
	bool wasReleased();				// Returns true if the button state at the last read was released.
	bool pressedFor(uint32_t duration);		// Returns true if the button state at the last read was pressed, and has been in that state for at least the given number of milliseconds.
	bool releasedFor(uint32_t duration);	// Returns true if the button state at the last read was released, and has been in that state for at least the given number of milliseconds.
private:
	// PRIVATE VARIABLES
	uint32_t _short_press_count;		// Short press counter.
	uint32_t _first_press_time;			// Time when button was pressed for first time.
	uint8_t _press_sequences;			// The number of sequences to count.
	uint32_t _press_sequence_duration;  // Time limit of the sequence.
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
	void(*mPressedCallback)();			// Callback functionn for pressed events.
	void(*mPressedForCallback)();		// Callback function for pressedFor events.
	void(*mPressedSequenceCallback)();	// Callback function for pressedSequence events.
};

#endif

