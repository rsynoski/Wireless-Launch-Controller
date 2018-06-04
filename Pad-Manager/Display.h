/*
 * Display.h
 *
 *  Created on: Mar 20, 2018
 *      Author: Robert
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_

class Display {
private:
	bool blState = false;
public:
	Display();
	void poll();
	virtual ~Display();
	void backlightOn();
	void backlightOff();
	void toggleBacklight();
};

#endif /* DISPLAY_H_ */
