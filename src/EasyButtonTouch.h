/**
 * EasyButtonTouch.h
 * @author Evert Arias, Gutierrez PS
 * @version 2.0.0
 * @license MIT
 */

#if !defined(_EasyButtonTouch_h) and defined(ESP32)
#define _EasyButtonTouch_h

#include <Arduino.h>
#include "EasyButton.h"

class EasyButtonTouch : public EasyButton
{
public:
	EasyButtonTouch(uint8_t pin, uint32_t debounce_time = 35, uint16_t threshold = 50) : EasyButton(pin, debounce_time, false, false), _touch_threshold(threshold) {}
	void begin();

private:
	uint16_t _touch_threshold; // If touchRead() is below the threshold, the button is considered pressed.

	bool _readPin();
};

#endif