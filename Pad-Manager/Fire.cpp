/*
 * Fire.cpp
 *
 *  Created on: Feb 25, 2018
 *      Author: Robert
 */

#include "Fire.h"
#include "streaming.h"

Fire::Fire(uint8_t swtch) {
	button = new Switch(swtch);
}

Fire::~Fire() {
	delete button;
}

void Fire::poll() {
	button->poll();
		if (button->pushed()) {
		Serial << "Fire pressed" << endl;
		}
		if (button->released()) {
			Serial << "Fire released" << endl;
		}


}
