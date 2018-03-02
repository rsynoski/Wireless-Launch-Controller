/*
 * Arm.cpp
 *
 *  Created on: Feb 25, 2018
 *      Author: Robert
 */

#include "Arm.h"



Arm::Arm(uint8_t swtch, uint8_t led) {
	this->led = led;
	pinMode(led, OUTPUT);
	key = new Switch(swtch);

}

void Arm::poll() {
	key->poll();
		digitalWrite(led, key->on() ? HIGH : LOW);
}

bool Arm::isArmed() {
	return key->on();
}

Arm::~Arm() {
	delete key;
}

