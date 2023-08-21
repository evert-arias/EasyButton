/**
 * EasyButtonTouch.h
 * @author Evert Arias, Gutierrez PS, Felix A. Epp
 * @version 2.0.3
 * @license MIT
 */

#if !defined(_EasyButtonTouch_h) and defined(ESP32)
#define _EasyButtonTouch_h
#include <include/soc/soc_caps.h>
#if defined(SOC_TOUCH_SENSOR_SUPPORTED) || (defined(SOC_TOUCH_SENSOR_NUM) && SOC_TOUCH_SENSOR_NUM > 1)

#include <Arduino.h>
#include <Filter.h>
#include "EasyButton.h"

class EasyButtonTouch : public EasyButton
{
public:
	EasyButtonTouch(uint8_t pin, uint32_t debounce_time = 35, uint16_t threshold = 50) : EasyButton(pin, debounce_time, false, false), _touch_threshold(threshold), ADCFilter(5, threshold) {}
	void begin();
	void begin(int threshold);
	void setThreshold(int threshold);

private:
	uint16_t _touch_threshold; // If touchRead() is below the threshold, the button is considered pressed.
	ExponentialFilter<long> ADCFilter;

	bool _readPin();
};
#endif
#endif