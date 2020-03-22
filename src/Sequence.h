#include <Arduino.h>


class Sequence
{
private:

    uint32_t _press_sequence_duration;  // Time limit of the sequence.
    uint32_t _first_press_time;         // Time when button was pressed for first time.
    uint8_t _press_sequences;			// The number of sequences to count.
    uint32_t _short_press_count;		// Short press counter.


public:
    Sequence(uint8_t sequences, uint32_t duration):_press_sequences(sequences), 
    _press_sequence_duration(duration)
    {
        _short_press_count = 0;
    }

    Sequence::Sequence(){}

    Sequence operator=(const Sequence& sequence);

    void newPress(uint32_t read_started_ms);
};