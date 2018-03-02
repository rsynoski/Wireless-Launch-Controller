/*
 * Selector.h
 *
 *  Created on: Feb 24, 2018
 *      Author: Robert
 */

#ifndef SELECTOR_H_
#define SELECTOR_H_
#include "arduino.h"
#include "avdweb_switch.h"
#include "Metro.h"

#define NO_CONT 20.0
#define SHORTED 0.3

class Selector {

private:
	byte togglePort;
	Switch *toggle;
	int selLED;
	int contLED;
	Metro blink{250};

public:
//	Selector();
	Selector(byte a, int b, int c);
	virtual ~Selector();
	bool getToggle() ;
	void poll();
	bool isSelected();
	void showContinuity(char value[]);
};

#endif /* SELECTOR_H_ */
