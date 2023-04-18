# pulseGenerator
v2.0

Arduino/Teensy-based multichannel programmable pulse generator.

## Features
* Multi-channel digital pulse generator
* Triggered by 1) TTL input, 2) push button, 3) calling function in MATLAB
* Four modes 1) programmable pulse, 2) toggle, 3) as input, 4) togglePulse
* Each channel is independent
* STOP button to turn off all channels

## Installation
* Install Arduino IDE
* Install Teensyduino
* In Arduino IDE, Sketch > Include Library > Add .Zip Library, select pulseGen.zip

## Main board (stand alone)
* Teensy 3.5, 33 digital I/O
* Instead of using world-stopping delay(), make a Channel instance for each channel and set mode (pulse; toggle; asinput; togglePulse)
* Example user sketch: `myPulses.ino`
* Constructor
	* e.g. `Channel ch1(1);` before `setup()`
	* In/out pins are hard coded in library
* Public methods
	* mode
		* "pulse"; "toggle"; "asinput"; "togglePulse"
		* e.g. `ch1.mode = "pulse";` in `setup()`
		* "pulse": Input triggers pulse train
		* "toggle": Input flips output state
	    * "asinput": Input = output
		* "togglePulse": Input triggers pulse train, next input stops it
	* setPulseParam(pulseWidth, interval, nPulse)
		* Parameters for "pulse" mode
		* `pulseWidth` and `interval` are in [ms]
		* e.g. `ch1.setPulseParam(50,100,10);` in `setup()`
    * setTogglePulseParam(pulseWidth, interval)
		* Parameters for "togglePulse" mode
		* in [ms]
	* interrupt
		* start the function
		* e.g. `ch1.interrupt();` in `loop()`

## MATLAB trigger
* It is implemented in tickleTimer
* `connectArduino` generates an Arduino instance
	* In case of failure, check COM port number in the device manager e.g. `COM3`, and execute `arduino('COM3','Nano3')` in the Command Window, which uploads server code in the Arduino.
* `trgPulse(myArduino,outpin)` generates 1x 100 ms pulse in the specified pin. e.g. `trgPulse(myArduino,'D2')`
* `onPin(myArduino,outpin)` makes specified pin HIGH
* `offPin(myArduino,outpin)` makes specified pin LOW

## Technical notes
* Calculation of time is performed by using millis(), which returns current time in ms
* interrupt() gets state from setState() and output in outpin
* interrupt() is repeated forever in loop()
* "toggle" mode ignores input chattering for 500 ms (`chatTime`), meaning input pulse should be shorter than this, otherwise it will lead to blinking
* "asinput" mode ignores input chattering for 500 ms (`chatTime`)
* Output pins on Teensy are [34, 35, 36, 37, 38] for channel 1-5 respectively.
* Trigger pins on Teensy are [24, 25, 26, 27, 28] for channel 1-5 respectively.
* Output pins on Arduino (MATLAB) are [D2, D3, D4, D5, D6] for channel 1-5 respectively.


## Development notes of MATLAB trigger
* Problems
	* Teensy is not supported by MATLAB Arduino Support Package
	* Program embedded by Arduino IDE and MATLAB-Arduino communication cannot coexist
	* MATLAB is not ideal platform to program Arduino loops (for me at least)
	* Not ideal to run continuous loop in MATLAB
* Solution
	* MATLAB can easily handle digital output of Arduino
	* Get another Arduino just to send trigger output to pulse generator input
