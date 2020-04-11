/**
 * Sequence.h
 * @author Evert Arias, Jose Gabriel Companioni Benitez
 * @version 2.0.0
 * @license MIT
 */

#ifndef _EasyButtonSequence_h
#define _EasyButtonSequence_h

#include <Arduino.h>

class Sequence
{
private:
    bool _is_enabled;
    uint8_t _press_sequences;          // The number of sequences to count.
    uint32_t _press_sequence_duration; // Time limit of the sequence.
    uint32_t _first_press_time;        // Time when button was pressed for first time.
    uint32_t _short_press_count;       // Short press counter.

public:
    Sequence(uint8_t sequences, uint32_t duration) : _is_enabled(false),
                                                     _press_sequences(sequences),
                                                     _press_sequence_duration(duration),
                                                     _first_press_time(0),
                                                     _short_press_count(0)
    {
    }

    Sequence() : Sequence(0, 0) {}

    bool newPress(uint32_t read_started_ms);

    void reset();

    void enable() { _is_enabled = true; }

    void disable() { _is_enabled = false; }
};

#endif