#include <Arduino.h>


class Sequence
{
private:

    bool _is_enabled;
    uint8_t _press_sequences;			// The number of sequences to count.
    uint32_t _press_sequence_duration;  // Time limit of the sequence.
    uint32_t _first_press_time;         // Time when button was pressed for first time.
    uint32_t _short_press_count;		// Short press counter.

public:
    Sequence(uint8_t sequences, uint32_t duration):_press_sequences(sequences), 
    _press_sequence_duration(duration)
    {
        _short_press_count = 0;
        _is_enabled = false;
    }

    Sequence(){}

    Sequence operator=(const Sequence& sequence);

    bool newPress(uint32_t read_started_ms);

    void reset();

    void enable(){_is_enabled = true;}

    void disable(){_is_enabled = false;}
};