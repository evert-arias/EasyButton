#include "EasyVar.h"

void EasyVar::begin()
{
	_current_state = _button_abstraction;
	if (_active_low)
		_current_state = !_current_state;
	_time = millis();
	_last_state = _current_state;
	_changed = false;
	_last_change = _time;
}

bool EasyVar::read()
{
	uint32_t read_started_ms = millis();

	bool pinVal = _readPin();

	if (_active_low)
		pinVal = !pinVal;

												//true -> debounce time ellapsed
    _last_state = _current_state;				// save last state.
    _current_state = pinVal;					// assign new state as current state from pin's value.
    _changed = (_current_state != _last_state); // report state change if current state vary from last state.
    // if state has changed since last read.
    if (_changed)
    { // state change
        // save current millis as last change time.
        _last_change = read_started_ms;
    }

	if (wasReleased())
	{
		if (!_was_btn_held)
		{
			if (_pressed_callback)
				_pressed_callback();

			for (size_t i = 0; i < MAX_SEQUENCES; i++)
			{
				if (_sequences[i].newPress(read_started_ms))
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
	else if (isPressed() && _read_type == EASYBUTTON_READ_TYPE_POLL)
		_checkPressedTime();

	_time = read_started_ms;

	return _current_state;
}