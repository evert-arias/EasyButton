#include"EasyButtonBase.h"


void EasyButtonBase::onPressed(EasyButtonBase::callback_t callback)
{
	_pressed_callback = callback;
}

void EasyButtonBase::onPressedFor(uint32_t duration, EasyButtonBase::callback_t callback)
{
	_held_threshold = duration;
	_pressed_for_callback = callback;
}

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