/*
 * Fire.h
 *
 *  Created on: Feb 25, 2018
 *      Author: Robert
 */

#ifndef FIRE_H_
#define FIRE_H_

#include "arduino.h"
#include "avdweb_switch.h"


class Fire {
	private:
	Switch *button;
public:
	Fire(uint8_t swtch);
	virtual ~Fire();

	void poll();


};

#endif /* FIRE_H_ */
