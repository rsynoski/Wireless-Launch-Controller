/*
 * Fire.cpp
 *
 *  Created on: Feb 25, 2018
 *      Author: Robert
 */

#include "Fire.h"
#include "streaming.h"
#include "Arm.h"
#include "Controllers.h"

extern Arm armingSwitch;
extern Controllers controllers;

Fire::Fire(uint8_t swtch) {
	button = new Switch(swtch);
//	button = new Switch(swtch, INPUT_PULLUP, LOW, 1000);
}

Fire::~Fire() {
	delete button;
}

void Fire::poll() {
	button->poll();
	if (button->pushed()) {
		if (armingSwitch.isArmed()) {
			controllers.firePress();
			Serial << "Fire pressed" << endl;
		}
	}
	if (button->released()) {
		if (armingSwitch.isArmed()) {
			controllers.fireRelease();
			Serial << "Fire released" << endl;
			controllers.clearControllers();
		}
	}


}
