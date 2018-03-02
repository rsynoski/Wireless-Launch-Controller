/*
 * Arm.h
 *
 *  Created on: Feb 25, 2018
 *      Author: Robert
 */

#ifndef ARM_H_
#define ARM_H_

#include "arduino.h"
#include "avdweb_switch.h"



class Arm {
private:
	Switch *key;
	int led;
public:
	Arm(uint8_t swtch, uint8_t led);
	void poll();
	bool isArmed();

	virtual ~Arm();
};

#endif /* ARM_H_ */
