/*
 * RotoryKnob.h
 *
 *  Created on: Feb 28, 2018
 *      Author: Robert
 */

#ifndef ROTORYKNOB_H_
#define ROTORYKNOB_H_



#include "arduino.h"
#include "avdweb_switch.h"
#include "DirectionalEncoder.h"

class RotoryKnob {
private:
	DirectionalEncoder *encoder;
	Switch *pushSwitch;

public:
	RotoryKnob(uint8_t pinA, uint8_t pinB, uint8_t pushSwitch);
	virtual ~RotoryKnob();
	void poll();
};

#endif /* ROTORYKNOB_H_ */
