/**
 * EasyButtonBase.h
 * @author Evert Arias
 * @version 2.0.0
 * @license MIT
 */

#include "EasyButtonBase.h"

void EasyButtonBase::onPressed(EasyButtonBase::callback_t callback)
{
	_pressed_callback = callback;
}

void EasyButtonBase::onPressedFor(uint32_t duration, EasyButtonBase::callback_t callback)
{
	_held_threshold = duration;
	_pressed_for_callback = callback;
}

#ifndef EASYBUTTON_DO_NOT_USE_SEQUENCES
void EasyButtonBase::onSequence(uint8_t sequences, uint32_t duration, EasyButtonBase::callback_t callback)
{
	if (_sequences_count < 5)
	{
		Sequence sequence(sequences, duration);
		sequence.enable();
		_sequences[_sequences_count] = sequence;
		_pressed_sequence_callbacks[_sequences_count++] = callback;
	}
}
#endif

bool EasyButtonBase::isPressed()
{
	return _current_state;
}

bool EasyButtonBase::isReleased()
{
	return !_current_state;
}

bool EasyButtonBase::wasPressed()
{
	return _current_state && _changed;
}

bool EasyButtonBase::wasReleased()
{
	return !_current_state && _changed;
}

bool EasyButtonBase::pressedFor(uint32_t duration)
{
	return _current_state && _time - _last_change >= duration;
}

bool EasyButtonBase::releasedFor(uint32_t duration)
{
	return !_current_state && _time - _last_change >= duration;
}

void EasyButtonBase::_checkPressedTime()
{
	uint32_t read_started_ms = millis();
	if (_current_state && read_started_ms - _last_change >= _held_threshold && _pressed_for_callback)
	{
		// Button has been pressed for at least the given time.
		_was_btn_held = true;

#ifndef EASYBUTTON_DO_NOT_USE_SEQUENCES
		// Reset short presses counters.
		for (Sequence seq : _sequences)
		{
			seq.reset();
		}
#endif

		// Call the callback function for a long press event if it exist and if it has not been called yet.
		if (_pressed_for_callback && !_held_callback_called)
		{
			// Set as called.
			_held_callback_called = true;
			_pressed_for_callback();
		}
	}
}