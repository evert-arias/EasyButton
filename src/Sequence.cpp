#include "Sequence.h"

Sequence Sequence::operator=(const Sequence& sequence)
{
    _press_sequence_duration = sequence._press_sequence_duration;
    _first_press_time = sequence._first_press_time;
    _press_sequences = sequence._press_sequences;
    _short_press_count = sequence._short_press_count;
	_is_enabled = sequence._is_enabled;
}

bool Sequence::newPress(uint32_t read_started_ms)
{
	if(_is_enabled)
	{
		if (_short_press_count == 0)
			_first_press_time = read_started_ms;

		_short_press_count++;

		if (_short_press_count == _press_sequences && _press_sequence_duration >= (read_started_ms - _first_press_time))
		{ //true-> pressed_sequence
			reset();			
			return true;
		}

		else if (_press_sequence_duration <= (read_started_ms - _first_press_time))
		{ // true-> sequence timeout
			reset();
			return false;
		}
	}
	return false;
}

void Sequence::reset()
{
	_short_press_count = 0;
	_first_press_time = 0;
}