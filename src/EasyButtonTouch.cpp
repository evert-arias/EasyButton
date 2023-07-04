/**
 * EasyButtonTouch.cpp
 * @author Evert Arias, Gutierrez PS, Felix A. Epp
 * @version 2.0.3
 * @license MIT
 */

#if defined(ESP32)
#include "EasyButtonTouch.h"
#if defined(SOC_TOUCH_SENSOR_SUPPORTED) || (defined(SOC_TOUCH_SENSOR_NUM) && SOC_TOUCH_SENSOR_NUM > 1)

void EasyButtonTouch::setThreshold(int threshold)
{
	_touch_threshold = threshold;
}

void EasyButtonTouch::begin(int threshold)
{
	_touch_threshold = threshold;
	begin();
}

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
	ADCFilter.Filter(touchRead(_pin));
	return ADCFilter.Current() < _touch_threshold;
}
#endif
#endif