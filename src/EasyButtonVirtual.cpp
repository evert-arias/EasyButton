/**
 * EasyButtonVirtual.h
 * @author Evert Arias, Jose Gabriel Companioni Benitez
 * @version 2.0.0
 * @license MIT
 */

#include "EasyButtonVirtual.h"

void EasyButtonVirtual::begin()
{
	_current_state = _button_abstraction;
	if (_active_low)
	{
		_current_state = !_current_state;
	}
	_time = millis();
	_last_state = _current_state;
	_changed = false;
	_last_change = _time;
}

bool EasyButtonVirtual::read()
{
	uint32_t read_started_ms = millis();

	// Save last state.
	_last_state = _current_state;
	_current_state = _button_abstraction;

	if (_active_low)
	{
		_current_state = !_current_state;
	}

	// Report state change if current state vary from last state.
	_changed = (_current_state != _last_state);

	// If state has changed since last read.
	if (_changed)
	{
		// State change.
		// Save current millis as last change time.
		_last_change = read_started_ms;
	}

	if (wasReleased())
	{
		if (!_was_btn_held)
		{
			if (_pressed_callback)
			{
				_pressed_callback();
			}

#ifndef EASYBUTTON_DO_NOT_USE_SEQUENCES
			for (size_t i = 0; i < MAX_SEQUENCES; i++)
			{
				if (_sequences[i].newPress(read_started_ms))
				{
					callback_t function = _pressed_sequence_callbacks[i];
					function();
				}
			}
#endif
		}
		// Button was not held.
		else
		{
			_was_btn_held = false;
		}
		// Since button released, reset _pressed_for_callbackCalled value.
		_held_callback_called = false;
	}
	else if (isPressed())
	{
		_checkPressedTime();
	}

	_time = read_started_ms;

	return _current_state;
}