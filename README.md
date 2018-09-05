# EasyButton

[![Join the chat at https://gitter.im/easy-button/chat](https://badges.gitter.im/Join%20Chat.svg)](https://gitter.im/thingsboard/chat?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)
[![Build Status](https://travis-ci.org/thingsboard/thingsboard.svg?branch=master)](https://travis-ci.org/thingsboard/thingsboard)
[![License](https://img.shields.io/badge/license-MIT%20License-blue.svg)](http://doge.mit-license.org)

Arduino library to debounce buttons, detect presses, releases, long presses and sequences

![](img.gif)

## How to install

Install the library using one of the following options

- [Arduino Library Manager](https://www.arduino.cc/en/Guide/Libraries)
- [Clone this repository into your libraries directory](https://help.github.com/articles/cloning-a-repository/)
- [Use it locally cloning this repository into your project's directory](https://help.github.com/articles/cloning-a-repository/)

## How to use

##### Include the library

``` c++
include <EasyButton.h>
```

##### Create an instance of the Button

Create an instance of `EasyButton` class for each button that you want to use, and pass the pin number as an argument. 

```c++
EasyButton button(BUTTON_PIN);
```

The class constructor takes the following additional arguments:

`dbTime` : Debounce time in milliseconds.

`puEnable` : Use or not the internal pullup resistor. Enabled by default.

`invert` : Inverts button's logic. If true, `low = pressed` else `high = pressed`.

```c++
EasyButton(uint8_t pin, uint32_t dbTime = 35, uint8_t puEnable = true, uint8_t invert = true)
```

##### Initialize the Button object

```c++
button.begin();
```

##### Continuously read the status of the Button

```c++
void loop() {
	button.read(); // Continuously read the status of the button. 
}
```

##### Available methods in the library

- onPressed

  Triggers a callback function when the Button has been pressed and released. The callback function will be called each time the Button is pressed.

  ```c++
  // Single pressed
  button.onPressed(onPressedCallback);
  ```

- onPressedFor

- Triggers a callback function when the Button has been pressed and hold

  Detect when the Button has been pressed for at least the given duration time. If is pressed and hold for at least the given duration, the callback function will be triggered. This method takes two parameters as arguments. The first argument is the duration in milliseconds and the second is the callback function to be called.

  ```c++
  // Pressed for a duration
  button.onPressedFor(2000, onPressedCallback);
  ```

- onSequence


