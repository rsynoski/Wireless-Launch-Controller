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
#define SHORTED 0.2

class Selector {

private:
	int number;
	byte togglePort;
	Switch *toggle;
	int selLED;
	int contLED;
	Metro blink{250,1};
	int cnt; // remove

public:
//	Selector();
	Selector(int num, byte a, int b, int c);
	virtual ~Selector();
	bool getToggle() ;
	void poll();
	bool isSelected();
	void showContinuity();
	void showSelection();
	void clear();
};

#endif /* SELECTOR_H_ */
