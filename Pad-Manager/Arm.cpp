/*
 * Arm.cpp
 *
 *  Created on: Feb 25, 2018
 *      Author: Robert
 */

#include "Arm.h"
#include "Controllers.h"

extern Controllers controllers;


Arm::Arm(uint8_t swtch, uint8_t led) {
	this->led = led;
	pinMode(led, OUTPUT);
	key = new Switch(swtch);

}

void Arm::poll() {
	key->poll();
	if (key->switched()) {
		if (!key->on()) {
			controllers.clearControllers();
		}
	}

		digitalWrite(led, isArmed() ? HIGH : LOW);
}

bool Arm::isArmed() {
#ifdef DEBUG
	return key->on();
#else
	bool on = key->on();
	if (!on) {
		powerUp = false;
		on = false;
	} else {
		if (powerUp) {
		on = false;
		}
	}
	return on;
#endif
}

Arm::~Arm() {
	delete key;
}

