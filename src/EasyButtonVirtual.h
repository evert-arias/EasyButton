/**
 * EasyButtonVirtual.h
 * @author Evert Arias, Jose Gabriel Companioni Benitez
 * @version 2.0.0
 * @license MIT
 */

#ifndef _EasyButtonVirtual_h
#define _EasyButtonVirtual_h

#include <Arduino.h>
#include "EasyButtonBase.h"

class EasyButtonVirtual : public EasyButtonBase
{
private:
    bool &_button_abstraction;

public:
    EasyButtonVirtual(bool &button_abstraction, bool active_low = true) : EasyButtonBase(active_low), _button_abstraction(button_abstraction) {}

    // PUBLIC FUNCTIONS
    void begin(); // Initialize a button object and the pin it's connected to.
    bool read();  // Returns the current debounced button state, true for pressed, false for released.
};

#endif