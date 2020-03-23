/**
 * EasyButton.cpp
 * @author Evert Arias
 * @version 1.1.0
 * @license MIT
 */

#include "EasyButton.h"

void EasyButton::begin()
{
	pinMode(_pin, _pu_enabled ? INPUT_PULLUP : INPUT);
	_current_state = _readPin();
	if (_invert) _current_state = !_current_state;
	_time = millis();
	_last_state = _current_state;
	_changed = false;
	_last_change = _time;
}

void EasyButton::onPressed(EasyButton::callback_t callback)
{
	_pressed_callback = callback;
}

void EasyButton::onPressedFor(uint32_t duration, EasyButton::callback_t callback)
{
	_held_threshold = duration;
	_pressed_for_callback = callback;
}

void EasyButton::onSequence(uint8_t sequences, uint32_t duration, EasyButton::callback_t callback)
{
	if(_sequences_count < 5)
	{
		Sequence sequence(sequences, duration);
		sequence.enable();
		_sequences[_sequences_count] = sequence;
		_pressed_sequence_callbacks[_sequences_count++] = callback;
	}
}

bool EasyButton::isPressed()
{
	return _current_state;
}

bool EasyButton::isReleased()
{
	return !_current_state;
}

bool EasyButton::wasPressed()
{
	return _current_state && _changed;
}

bool EasyButton::wasReleased()
{
	return !_current_state && _changed;
}

bool EasyButton::pressedFor(uint32_t duration)
{
	return _current_state && _time - _last_change >= duration;
}

bool EasyButton::releasedFor(uint32_t duration)
{
	return !_current_state && _time - _last_change >= duration;
}

bool EasyButton::read(int read_type)
{
	uint32_t read_started_ms = millis();

	bool pinVal = _readPin();

	if (_invert)
		pinVal = !pinVal;

	if (read_started_ms - _last_change < _db_time)
	{ 	//true -> debounce time has not ellapsed
		_changed = false;
	}
	else
	{	//true -> debounce time ellapsed 
		_last_state = _current_state;				// save last state.
		_current_state = pinVal;					// assign new state as current state from pin's value.
		_changed = (_current_state != _last_state); // report state change if current state vary from last state.
		// if state has changed since last read.
		if (_changed)
		{ // state change
			// save current millis as last change time.
			_last_change = read_started_ms;
		}
	}

	if (wasReleased())
	{
		if (!_was_btn_held)
		{
			if (_pressed_callback)
				_pressed_callback();

			for (size_t i = 0; i < MAX_SEQUENCES; i++)
			{
				if(_sequences[i].newPress(read_started_ms))
				{
					callback_t function = _pressed_sequence_callbacks[i];
					function();
				}
			}
		}
		// button was not held.
		else
		{
			_was_btn_held = false;
		}
		// since button released, reset _pressed_for_callbackCalled value.
		_held_callback_called = false;
	}
	else if(isPressed() && read_type == POLL)
		_checkPressedTime();
	

	_time = read_started_ms;

	return _current_state;
}

bool EasyButton::_readPin()
{
	return digitalRead(_pin);
}

bool EasyButton::supportsInterrupt()
{
	return (digitalPinToInterrupt(_pin) != NOT_AN_INTERRUPT);
}

void EasyButton::enableInterrupt(EasyButton::callback_t callback)
{
	attachInterrupt(digitalPinToInterrupt(_pin), callback, CHANGE);
}

void EasyButton::disableInterrupt()
{
	detachInterrupt(digitalPinToInterrupt(_pin));
}

void EasyButton::update()
{
	if (!_was_btn_held)
		_checkPressedTime();
}

void EasyButton::_checkPressedTime()
{
	uint32_t read_started_ms = millis();
	if (_current_state && read_started_ms - _last_change >= _held_threshold && _pressed_for_callback)
	{
		// button has been pressed for at least the given time
		_was_btn_held = true;

		// reset short presses counters.
		for(Sequence seq:_sequences)
			{
				seq.reset();
			}
		
		// call the callback function for a long press event if it exist and if it has not been called yet.
		if (_pressed_for_callback && !_held_callback_called)
		{
			_held_callback_called = true; // set as called.
			_pressed_for_callback();
		}
	}
}