#ifndef _EasyVar_h
#define _EasyVar_h
#endif

#include <Arduino.h>
#include "EasyButtonBase.h"

class EasyVar: public EasyButtonBase
{
private:
    bool _button_abstraction;
public:
    EasyVar(bool& button_abstraction, bool active_low = true): EasyButtonBase(active_low), _button_abstraction(button_abstraction){}

    // PUBLIC FUNCTIONS
	void begin();														// Initialize a button object and the pin it's connected to.
	bool read();														// Returns the current debounced button state, true for pressed, false for released.
};

