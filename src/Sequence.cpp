/**
 * Sequence.h
 * @author Evert Arias, Jose Gabriel Companioni Benitez
 * @version 2.0.0
 * @license MIT
 */

#include "Sequence.h"

bool Sequence::newPress(uint32_t read_started_ms)
{
	if (_is_enabled)
	{
		if (_short_press_count == 0)
		{
			_first_press_time = read_started_ms;
		}

		_short_press_count++;

		if (_short_press_count == _press_sequences && _press_sequence_duration >= (read_started_ms - _first_press_time))
		{
			// Pressed sequence
			reset();
			return true;
		}
		else if (_press_sequence_duration <= (read_started_ms - _first_press_time))
		{
			// Sequence timeout
			_short_press_count = 1;
			_first_press_time = read_started_ms;
		}
	}
	return false;
}

void Sequence::reset()
{
	_short_press_count = 0;
	_first_press_time = 0;
}
