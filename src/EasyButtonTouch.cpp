/**
 * EasyButtonTouch.cpp
 * @author Evert Arias, Gutierrez PS
 * @version 2.0.0
 * @license MIT
 */

#if defined(ESP32)
#include "EasyButtonTouch.h"

void EasyButtonTouch::begin()
{
	_current_state = _readPin();
	_time = millis();
	_last_state = _current_state;
	_changed = false;
	_last_change = _time;
}

bool EasyButtonTouch::_readPin()
{
	return touchRead(_pin) < _touch_threshold;
}

#endif